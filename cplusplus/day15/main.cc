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
  static int HowManyCats;
private:
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
      cout << "Cat count " << plitter[i]->HowManyCats << "\n";
    }
  cout << "lose the cats ...\n";
  for (i=0; i<5; i++)
    {
      cout << "litter " << i << "\n";
      delete plitter[i];
      cout << "Cat count " << plitter[i]->HowManyCats << "\n";
    }
  return 0;
}

