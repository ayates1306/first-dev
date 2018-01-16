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
  virtual int GetHowManyCats() { return HowManyCats; } // accessor function
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
  Cat *plitter[5];
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
      cout << "Cat count " << plitter[i]->GetHowManyCats() << "\n";
      delete plitter[i];
      // Note that now GetHowManyCats() is a member function of the
      // Cat class, I can only use it from an object. If I delete
      // the object, as here, then it is no longer valid to call
      // the function. I get a seg fault if I delete the object
      // and then call ->GetHowManyCats()
    }
  return 0;
}

