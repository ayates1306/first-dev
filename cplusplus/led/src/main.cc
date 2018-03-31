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
  std::string GetName() const { return name; }
  pthread_t hand;
};

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
  // start a thread, and remember the thread ID
  auto t = std::thread(&pattern::thread, this);

  hand = t.native_handle();

  t.detach(); //join();

  std::cout << "Thread presumably created\n";
  //  while(1);
}




static  pattern *plist[5];

int main () {
  int i, n=0, num=0;
  bool quit=false;

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
     plist[n] = new pattern(50, 50, 2, 100, name);
     ++n;
     ++num;
     if (n==5) {
       quit = true;
     }
   }
     break;
   case 2: {
     n--;
     std::cout << "Going to delete " << plist[n]->GetName() << std::endl;
     delete plist[n];
   }
   break;
   default: {
   }
   break;
   }
   }
    
   //   pthread_exit(NULL);
}
