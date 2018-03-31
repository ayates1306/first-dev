#include <iostream>
#include <cstdlib>
#include <chrono>
#include <pthread.h>

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>  
#include <thread>

using namespace std;

#define NUM_THREADS 5

// Group
// pattern has a group
// start_pattern, first ask group to kill other patterns on it?
// What about priorities on LEDs?
//
// Patterns represent some state
// Patterns should be independent
// But some patterns are grouped by function (eg, wifi, audio)
// so changing a grouped pattern should stop any currently
// running pattern on that group.
// Does that mean that the APIs are:
// add_pattern_to_group()
// start_pattern(group, pattern)
// As only 1 pattern can exist at one time on a group,
// we just maintain the current pattern inside the group and
// stop it next time start_pattern() is called.


// class to keep track of the on/off state and the time between them
// plus the number of repeats
class pattern {
public:
  pattern(int on, int off, int repeat, int delay, std::string cname);
  ~pattern();
  //private:
  int onTime;
  int offTime;
  bool onOffState;
  int repeatCount;
  int initCount;
  int afterFlashDelay;
  std::string name; 
  //  pthread_t thread_;
  void thread();
  void start();
  std::string GetName() const { return name; }
  pthread_t hand;
};

class group {
public:
  group() : current_pattern(nullptr) {};
  ~group();
  void start_pattern(pattern*);
private:
  pattern* current_pattern;
};

void group::start_pattern(pattern* pattern_) {
  if (current_pattern != nullptr) {
    current_pattern->pattern::~pattern();
  }

  current_pattern = pattern_;

  pattern_->start();
}

group::~group() {
  if (current_pattern != nullptr) {
    current_pattern->pattern::~pattern();
  }
}

pattern::~pattern()
{
  std::cout << "Destroy " << name << "\n";
  pthread_cancel(hand);
}

void pattern::thread()
{
  int wait;
  while(1) {
   repeatCount = initCount;
  while (repeatCount--)
    {
      cout << "I am '" << name << "' 0x";
      cout << std::hex << (long long)this << std::dec;
      cout << " count " << repeatCount << "\n";
      //cout << "This thing is " << (onOffState?"on":"off");
      //cout << " \n";
      wait = onOffState?onTime:offTime;
      onOffState = !onOffState;
      // we want to wait and then come back
      // this can be anything!
      // but this cannot.

      std::this_thread::sleep_for(std::chrono::milliseconds(wait));
    }
  std::cout << name<< " is sleeping before restarting\n";
   std::this_thread::sleep_for(std::chrono::milliseconds(afterFlashDelay));
  }
  std::cout << "End of pattern thread\n";
  //  while(1);
}


pattern::pattern(int on, int off, int repeat, int delay, std::string cname):
  onTime(on),
  offTime(off),
  initCount(repeat),
  afterFlashDelay(delay),
  name(cname)
{
  std::cout << "Create pattern named " << cname << "\n";
}

void pattern::start(void) {
  // start a thread, and remember the thread ID
  auto t = std::thread(&pattern::thread, this);

  hand = t.native_handle();

  t.detach(); //join();

  std::cout << "Thread presumably created\n";
}




static  pattern *plist[5];

int main () {
  int i, n=0, num=0;
  bool quit=false;
  group gp1, gp2;

   srand(time(NULL));

   while (!quit) {
     
   cout << "0: quit"<< std::endl;
   cout << "1: Create thread"<< std::endl;
   cout << "2: Delete last thread"<< std::endl;

   std::cin >> i;

   switch (i) {
   case 0: {
     quit = true;
   break;
   }
   case 1: {
     std::cout << "Main thread, create new pattern " << num << "\n";
     std::string name = "blah ";
     name = name + std::to_string(num);
     std::cout << "Create it called "<<name << std::endl;
     plist[n] = new pattern(250, 250, 2+n, 100, name);
     if ((n&1) == 0){
       gp1.start_pattern(plist[n]);
     } else {
       gp2.start_pattern(plist[n]);
     }
     ++n;
     ++num;
     if (n==5) {
       quit = true;
     }
   }
     break;
     //   case 2: {
     //     n--;
     //     std::cout << "Going to delete " << plist[n]->GetName() << std::endl;
     // delete plist[n];
     //   }
     //   break;
   default: {
   }
   break;
   }
   }
    
   //   pthread_exit(NULL);
   std::cout << "End of main program\n";
}
