#include <iostream>
#include <cstdlib>
#include <chrono>
#include <pthread.h>

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>  
#include <thread>
#include <vector>
#include <utility>

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
// add_pattern_to_group()  -- no need
// start_pattern(group, pattern)
// As only 1 pattern can exist at one time on a group,
// we just maintain the current pattern inside the group and
// stop it next time start_pattern() is called.

// So really, "group" should be named "function", ie, functional
// block for the app. A pattern is a representation of the state
// of the functional block.

// start_pattern(function, pattern) sounds more logical.

// Config options
// pattern type, etc etc
// pattern.group = G

// commands:
// On X start_pattern(1)
// On Y start_pattern(2)
// Handler looks up Group for pattern N
// then calls group[N].start_pattern()

// Next things to do:
// Stop pattern - IRL this would release any resources owned
// by the pattern (group), thus allowing other groups at a lower
// priority to drive such LEDs.
// stop_patterns(group)

class AppFunction;

// class to keep track of the on/off state and the time between them
// plus the number of repeats
// When the state changes, the pattern needs to notify its 'function',
// or owner, that the state has changed.
class pattern {
public:
  pattern(int on, int off, int repeat, int delay, std::string cname,
	  AppFunction *group);
  ~pattern();
  std::string GetName() const { return name; }
  void start();
  void stop();
private:
  int onTime;
  int offTime;
  bool onOffState;
  int repeatCount;
  int initCount;
  int afterFlashDelay;
  std::string name; 
  void thread();
  pthread_t hand;
private:
  class AppFunction *group_;
};

class AppFunction {
public:
  AppFunction() : current_pattern_(nullptr) {};
  ~AppFunction();
  void start_pattern(int);//pattern*);
  void stop_pattern(int);//pattern*);
  void set(bool on);
  void AddPattern(pattern*);
private:
  pattern* current_pattern_;
  std::vector<pattern*> pattern_list_;
};

void AppFunction::AddPattern(pattern* p)
{
  std::cout << "Add Pattern 0x" << std::hex << (long long)p;
  std::cout << std::dec << std::endl;
  pattern_list_.push_back(p);
}

// Stop any currently executing pattern on this Function
// and start a new one
void AppFunction::start_pattern(int n) {
  if (current_pattern_ != nullptr) {
    current_pattern_->stop();//pattern::~pattern();
  }

  current_pattern_ = pattern_list_[n];

  std::cout << "Start current pattern\n";
  std::cout << "Add Pattern 0x" << std::hex << (long long)current_pattern_;
  std::cout << std::dec << std::endl;
  current_pattern_->start();
}

void AppFunction::stop_pattern(int n) {
  // Free all patterns 
  if (current_pattern_ != nullptr) {
    //    current_pattern->pattern::~pattern();
      current_pattern_->stop();
  }

  current_pattern_ = nullptr;
}


AppFunction::~AppFunction() {
  for (std::vector<pattern*>::iterator it = pattern_list_.begin() ; 
       it != pattern_list_.end(); ++it) {
    //        (*it)->pattern::~pattern();
	delete (*it);
  }
    //  if (current_pattern_ != nullptr) {
    //    current_pattern_->pattern::~pattern();
    //  }
}

void AppFunction::set(bool en) {
  std::cout << "Group set 0x" << std::hex << (long long)this;
  std::cout << " => " << en << std::endl << std::dec;
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
    std::cout << "THREAD: initCount = " << initCount << std::endl;
   repeatCount = initCount;
  while (repeatCount--)
    {
      cout << "I am '" << name << "' 0x";
      cout << std::hex << (long long)this << std::dec;
      cout << " count " << repeatCount << "\n";
      //cout << "This thing is " << (onOffState?"on":"off");
      //cout << " \n";
      wait = onOffState?onTime:offTime;
      group_->set(onOffState);
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


pattern::pattern(int on, int off, int repeat, int delay, 
		 std::string cname, class AppFunction* gp):
  onTime(on),
  offTime(off),
  initCount(repeat),
  afterFlashDelay(delay),
  name(cname),
  group_(gp)
{
  std::cout << "Create pattern named " << cname << "\n";
}

void pattern::start() {
  // start a thread, and remember the thread ID
  auto t = std::thread(&pattern::thread, this);

  hand = t.native_handle();
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  t.detach(); //join();

  std::cout << "Thread presumably created\n";
}

void pattern::stop() {
  std::cout << "Stop Pattern 0x" << std::hex << (long long)this;
  std::cout << std::dec << std::endl;
  
  pthread_cancel(hand);
}

static pattern* plist[5];

int main () {
  int i, n=0, num=0;
  bool quit=false;
  AppFunction gp1, gp2;

   srand(time(NULL));

   for (i=0; i<5; i++)
     {
       std::cout << "Main thread, create new pattern " << i << "\n";
       std::string name = "blah ";
       name = name + std::to_string(i);
       std::cout << "Create it called "<<name << std::endl;
       plist[i] = new pattern(2500, 2500, i+1, 10000, name, &gp1);
       if ((i&1) == 0){
	 gp1.AddPattern(plist[i]);
       } else {
	 gp2.AddPattern(plist[i]);
       }
     }

   while (!quit) {
     
   cout << "0: quit"<< std::endl;
   cout << "1: Start pattern"<< std::endl;
   cout << "2: Stop pattern"<< std::endl;

   std::cin >> i;

   switch (i) {
   case 0: {
     quit = true;
   break;
   }
   case 1: {
          if ((n&1) == 0){
     gp1.start_pattern(n/2);
            } else {
     gp2.start_pattern(n/2);
            }
     ++n;
     ++num;
     if (n==5) {
       quit = true;
     }
   }
     break;
   case 2: {
     --n;
     std::cout << "Going to stop " << plist[n]->GetName() << std::endl;
          if ((n&1) == 0){
     gp1.stop_pattern(n/2);
            } else {
     gp2.stop_pattern(n/2);
            }
	  //     gp1.stop_pattern(n);
	  //     plist[n] = nullptr;
   }
     break;
   default: {
   }
   break;
   }
   }
    
   //   pthread_exit(NULL);
   std::cout << "End of main program\n";
}
