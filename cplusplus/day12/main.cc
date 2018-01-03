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
  Mammal(int);
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
  Dog(int age);
  Dog(int age, int weight);
  Dog(int age, int weight, BREED breed);
  ~Dog();

  // Accessors
  BREED GetBreed() const { return itsBreed; }
  void SetBreed(BREED breed) { itsBreed = breed;}
  
  // other methods
  void WagTail() const { cout << "Tail wagging\n";}
  void BegForFood() const { cout << "Begging for food\n";}

  // overridden speak method
  void Speak() const {cout << "Woof!\n"; }

protected:
  BREED itsBreed;
};

Mammal::Mammal():
  itsAge(10),
  itsWeight(5)
{
}

Mammal::Mammal(int age):
  itsAge(age),
  itsWeight(5)
{
}

Mammal::~Mammal()
{
}

Dog::Dog():
  itsBreed(GOLDEN)
{
}

Dog::Dog(int age):
  Mammal(age),
  itsBreed(GOLDEN)
{
}

Dog::Dog(int age, int weight):
  Mammal(age),
  itsBreed(GOLDEN)
{
  itsWeight = weight;
}

Dog::Dog(int age, int weight, BREED breed):
  Mammal(age),
  itsBreed(breed)

{
  itsWeight = weight;
}


Dog::~Dog()
{
}

int main(void)
{
  Dog fido;
  fido.Speak();
  fido.WagTail();
  cout << "Fido is "<<fido.GetAge() << " years old\n";
}


