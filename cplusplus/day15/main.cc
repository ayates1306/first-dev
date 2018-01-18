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
  virtual void Speak() const = 0;
protected:
  int itsAge;
};

class Kitten: public Cat
{
public:
  void Speak() const { cout << "Meow"; }
};

class Tiger: public Cat
{
public:
  void Speak() const { cout << "Grrrrr"; }
};

int main()
{
  typedef void (Cat::*CatFunc)()const;
  CatFunc pFunc[2];
  Cat *ptr=0;
  ptr = new Kitten;
  pFunc[0] = &Cat::Speak; // note the &
  (ptr->*pFunc[0])();
  cout << "\n";
  delete ptr;

  ptr = new Tiger;
  pFunc[1] = &Cat::Speak; // note the &
  (ptr->*pFunc[1])();
  cout << "\n";
  delete ptr;

  return 0;
}

