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

protected:
  BREED itsBreed;
};

Mammal::Mammal():
  itsAge(10),
  itsWeight(5)
{
  cout << "Mammal constructor\n";
}

Mammal::Mammal(int age):
  itsAge(age),
  itsWeight(5)
{
  cout << "Mammal (int) constructor\n";
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

Dog::Dog(int age):
  Mammal(age),
  itsBreed(GOLDEN)
{
  cout << "Dog(int) constructor\n";
}

Dog::Dog(int age, int weight):
  Mammal(age),
  itsBreed(GOLDEN)
{
  itsWeight = weight;
  cout << "Dog(int,int) constructor\n";
}

Dog::Dog(int age, int weight, BREED breed):
  Mammal(age),
  itsBreed(breed)

{
  itsWeight = weight;
  cout << "Dog (int, int, breed) constructor\n";
}


Dog::~Dog()
{
  cout << "Dog destructor\n";
}

int main(void)
{
  Dog fido;
  Dog rover(1);
  Dog fluffy(2,3);
  Dog rex (5,6,DOBERMAN);
  fido.Speek();
  fido.WagTail();
  cout << "Fido is "<<fido.GetAge() << " years old\n";
  cout << "Rover is "<<rover.GetAge() << " years old\n";
  cout << "Fluffy is "<<fluffy.GetAge() << " years old\n";
  cout << "Rex is "<<rex.GetAge() << " years old\n";
}


