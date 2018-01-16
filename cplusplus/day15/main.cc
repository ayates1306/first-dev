// day 15
// static member variables.
// These allow data to be shared. They are shared by all instances of the class.

#include <iostream>

using namespace std;

class Cat
{
public:
  Cat(int age):itsAge(age) {HowManyCats++;}
  virtual ~Cat() { HowManyCats--;}
  virtual int GetAge() { return itsAge; }
  virtual void SetAge(int age) { itsAge = age;}
  static int GetHowManyCats() { return HowManyCats; } // accessor function
private:
  static int HowManyCats; // variable is now private (and still static)
  int itsAge;
};

// Note we need to define & initialise this 
// variable somewhere, as it is not in the 
// instantiated classes (later on, when they 
// are created)
int Cat::HowManyCats=0; 


int main()
{
  int i;
  //  Cat litter[5];
  Cat *plitter[5] = {0,0,0,0,0};
  for (i=0; i<5; i++)
    {
      cout << "Create a cat!\n";
      plitter[i] = new Cat(i);;
      cout << "Cat count " << plitter[i]->GetHowManyCats() << "\n";
    }
  cout << "lose the cats ...\n";
  for (i=0; i<5; i++)
    {
      cout << "litter " << i << "\n";
      delete plitter[i];
      cout << "Count " << Cat::GetHowManyCats() << "\n";
      // Note that now GetHowManyCats() is a static member function 
      // of the Cat class, I can actually use it without an object.
      // A brief experiment suggested even casting NULL to a Cat*
      // allowed me to access NULL->GetHowManyCats() which doesn't
      // feel right.
      // This suggests that the compiler knows that the function
      // is static and therefore at 1 specific memory location, so
      // ignored the actual address of the pointer to object that I 
      // gave it.
    }
  return 0;
}

