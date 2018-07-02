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
// StartPattern, first ask group to kill other patterns on it?
// What about priorities on LEDs?
//
// Patterns represent some state
// Patterns should be independent
// But some patterns are grouped by function (eg, wifi, audio)
// so changing a grouped pattern should stop any currently
// running pattern on that group.
// Does that mean that the APIs are:
// add_pattern_to_group()  -- no need
// StartPattern(group, pattern)
// As only 1 pattern can exist at one time on a group,
// we just maintain the current pattern inside the group and
// stop it next time StartPattern() is called.

// So really, "group" should be named "function", ie, functional
// block for the app. A pattern is a representation of the state
// of the functional block.

// StartPattern(function, pattern) sounds more logical.

// Think about the messages on the bus, ie the rules:
// First we need to configure patterns
// So let's say:
//   pattern 1 is WiFi scanning
//   pattern 2 is WiFi connected
//   pattern 3 is audio muted
//   pattern 4 is audio streaming
// Connectivity will send, eg:
//   StartPattern(1) or
//   StartPattern(2)
// and audio will send, eg:
//   StartPattern(3) or
//   StartPattern(4)
//
// This means that the pattern needs to know what other patterns
// to stop first. So each pattern has a group associated with it.
//

// Config options
// pattern type, time, etc etc
// pattern.group = G

// Pros and cons:
// Pros: IPC command is simple. StartPattern, pattern=N
// Cons: Need to look up which group N is on



// commands:
// On X StartPattern(1)
// On Y StartPattern(2)
// Handler looks up Group for pattern N
// then calls group[N].StartPattern()

// Stop pattern - IRL this would release any resources owned
// by the pattern (group), thus allowing other groups at a lower
// priority to drive such LEDs.

class AppFunctionInterface;

// class to keep track of the on/off state and the time between them
// plus the number of repeats
// When the state changes, the pattern needs to notify its 'function',
// or owner, that the state has changed.
class pattern {
public:
  pattern(int on, int off, int repeat, int delay, std::string cname,
	  AppFunctionInterface *group);
  ~pattern();
  std::string GetName() const { return name; }
  void Start();
  void Stop();
  void StopGroup();
private:
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
  void thread();
  bool thread_started_;
  pthread_t hand;
  std::thread t_;
  class AppFunctionInterface *group_;
};

class AppFunctionInterface {
public:
  //  AppFunction() : current_pattern_(nullptr) {};
  AppFunctionInterface() : current_pattern_(nullptr) {std::cout << "AppFnInt\n";}
  virtual ~AppFunctionInterface(); 
  void StartPattern(int);
  void StopPattern();
  virtual void set(bool on) = 0;
  void AddPattern(pattern*);
private:
  pattern* current_pattern_;
  std::vector<pattern*> pattern_list_;
};

class AppFunction : public AppFunctionInterface {
public:
  AppFunction():AppFunctionInterface() {};
  virtual ~AppFunction() {};
  void set(bool on);
};

class AppTestFunction : public AppFunctionInterface {
public:
  AppTestFunction():AppFunctionInterface() {};
  virtual ~AppTestFunction() {};
  void set(bool on);
};

void AppFunctionInterface::AddPattern(pattern* p)
{
  pattern_list_.push_back(p);
}

// Stop any currently executing pattern on this Function
// and start a new one
void AppFunctionInterface::StartPattern(int n) {
  if (current_pattern_ != nullptr) {
    current_pattern_->Stop();
  }

  current_pattern_ = pattern_list_[n];

  std::cout << "Start current pattern\n";
  std::cout << "Add Pattern 0x" << std::hex << (long long)current_pattern_;
  std::cout << std::dec << std::endl;
  current_pattern_->Start();
}

void AppFunctionInterface::StopPattern() {
  // Free all patterns 
  if (current_pattern_ != nullptr) {
      current_pattern_->Stop();
  }

  current_pattern_ = nullptr;
}


AppFunctionInterface::~AppFunctionInterface() {
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
  std::cout << "Functional Group set 0x" << std::hex << (long long)this;
  std::cout << " => " << en << std::endl << std::dec;
}

void AppTestFunction::set(bool en) {
  std::cout << "This is a test interface: Functional Group set 0x" << std::hex << (long long)this;
  std::cout << " => " << en << std::endl << std::dec;
}

pattern::~pattern()
{
  std::cout << "~pattern. Destroy " << name << "\n";

  //t_.~thread();  
  if (thread_started_) {
    pthread_cancel(hand);
  //t_.join();
  }
  thread_started_ = false;
  //  pthread_t thread_;
  void thread();
  std::string GetName() const { return name; }
  pthread_t hand;
};


void pattern::thread()
{
  int wait;
  while(1) {
    std::cout << "THREAD: initCount = " << initCount << std::endl;
   repeatCount = initCount*2;
  while (repeatCount--)
    {
      cout << "I am '" << name << "' 0x";
      cout << std::hex << (long long)this << std::dec;
      cout << " count " << repeatCount << "\n";
      cout << "This thing is " << (onOffState?"on":"off");
      cout << " \n";
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
		 std::string cname, class AppFunctionInterface* gp):
  name(cname),
  thread_started_(false),
  group_(gp)
{
  std::cout << std::dec << std::endl;
  group_->AddPattern(this);
}

void pattern::Start() {
  // start a thread, and remember the thread ID
  t_ = std::thread(&pattern::thread, this);

  hand = t_.native_handle();
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  //    t.detach(); //join();

  thread_started_=true;
}

void pattern::StopGroup() {
  group_->StopPattern();
}

void pattern::Stop() {
  std::cout << "Stop Pattern 0x" << std::hex << (long long)this;
  std::cout << std::dec << std::endl;
  
  pthread_cancel(hand);
  t_.join();
  thread_started_=false;
}

static pattern* plist[5];
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




int main () {
  int i, n=0, num=0;
  bool quit=false;
  AppTestFunction gp2;
  AppFunction gp1;

   srand(time(NULL));

   for (i=0; i<5; i++)
     {
       if ((i&1) == 0){
	 std::string name = "WiFi pattern ";
	 name = name + std::to_string(i);
	 std::cout << "Create it called "<<name << std::endl;
	 plist[i] = new pattern(2500, 2500, i+1, 10000, name, &gp1);
       } else {
	 std::string name = "Audio Pattern ";
	 name = name + std::to_string(i);
	 std::cout << "Create it called "<<name << std::endl;
	 plist[i] = new pattern(2500, 2500, i+1, 10000, name, &gp2);
       }
     }

   while (!quit) {
     
   cout << "0: quit"<< std::endl;
   cout << "1: Start pattern"<< std::endl;
   cout << "2: Stop pattern"<< std::endl;
   cout << "3: Stop GROUP pattern"<< std::endl;

   std::cin >> i;

   switch (i) {
   case 0: {
     quit = true;
   break;
   }
     // This would be the StartPattern(p) message.
     // P was previously configured
   case 1: {
     std::cout << "Simulated command:\n";
     std::cout << "pattern_start(n) where N is in the "
       "global list of patterns\n";
          if ((n&1) == 0){
	    std::cout << "gp1 start\n";
	    gp1.StartPattern(n/2);
            } else {
	    std::cout << "gp2 start\n";
	    gp2.StartPattern(n/2);
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
	    gp1.StopPattern();
	  } else {
	    gp2.StopPattern();
	  }
   }
     break;
   case 3: {
     --n;
     std::cout << "PATTERN Going to stop " << plist[n]->GetName() << std::endl;
     plist[n]->StopGroup();
   }
     break;
   default: {
   }
     break;
   }
   }

   for (i=0; i<5; i++) {
     delete plist[i];
     plist[i] = nullptr;
     //     plist[i]->join();
   }
    
   //   pthread_exit(NULL);
   std::cout << "End of main program\n";
}
