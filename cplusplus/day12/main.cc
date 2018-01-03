#include <iostream>
// day 12, inheritance

// in general terms, we have specialisation and generalisation.
// inheritance is how C++ implements this relationship.
// This is derivation. A class that inherits functionality from
// another class is derived.
// The original class is the base class.
// Typically a base class will have more than 1 derived class.
using namespace std;

enum BREED {GOLDEN, CAIRN, DANDIE, SHETLAND, DOBERMAN, LAB};

class Mammal
{
public:
  // constructors
  Mammal();
  ~Mammal();

  // accessors
  int GetAge() const {return itsAge;}
  void SetAge(int age) {itsAge = age; }
  int GetWeight() const {return itsWeight; }
  void SetWeight(int weight) {itsWeight = weight;}

  // other methods
  void Speek() const { cout << "Mammal sound\n"; }
  void Sleep() const { cout << "Zzzzz\n"; }

protected: // because private data is not available to derived classes
  int itsAge;
  int itsWeight;
};

class Dog : public Mammal  // public inheritance
{
public:
  // constructors
  Dog();
  ~Dog();

  // Accessors
  BREED GetBreed() const { return itsBreed; }
  void SetBreed(BREED breed) { itsBreed = breed;}
  
  // other methods
  void WagTail() const { cout << "Tail wagging\n";}
  void BegForFood() const { cout << "Begging for food\n";}

protected:
  BREED itsBreed;
};

Mammal::Mammal():
  itsAge(1),
  itsWeight(5)
{
  cout << "Mammal constructor\n";
}

Mammal::~Mammal()
{
  cout << "Mammal destructor\n";
}

Dog::Dog():
  itsBreed(GOLDEN)
{
  cout << "Dog constructor\n";
}

Dog::~Dog()
{
  cout << "Dog desctructor\n";
}

int main(void)
{
  Dog fido;
  fido.Speek();
  fido.WagTail();
  cout << "Fido is "<<fido.GetAge() << " years old\n";
}


