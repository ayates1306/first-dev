// day 15
// static member variables.
// These allow data to be shared. They are shared by all instances of the class.
// Pointers to member functions


#include <iostream>

using namespace std;

class Cat
{
public:
  Cat():itsAge(1) {}
  virtual ~Cat() {}
  virtual int GetAge() const = 0; // pure virtual
protected:
  int itsAge;
};

class Kitten: public Cat
{
public:
  int GetAge() const { return 5; }
};

int main()
{
  int (Cat::*pFunc)() const = 0;
  Cat *ptr=0;
  ptr = new Kitten;
  pFunc = &Cat::GetAge; // note the &
  cout << "ptr to age fn = " << (ptr->*pFunc)() << "\n";
  delete ptr;

  return 0;
}

