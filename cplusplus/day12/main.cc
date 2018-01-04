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
  virtual ~Mammal();

  // accessors
  int GetAge() const {return itsAge;}
  void SetAge(int age) {itsAge = age; }
  int GetWeight() const {return itsWeight; }
  void SetWeight(int weight) {itsWeight = weight;}

  // other methods
  void Speak() const { cout << "Mammal sound\n"; }
  void Sleep() const { cout << "Zzzzz\n"; }
  virtual void Move() const { cout << "Mammal move 1 step\n";}
  virtual void Move(int n) const { cout << "Mammal move " << n << " steps\n";}

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
  virtual ~Dog();

  // Accessors
  BREED GetBreed() const { return itsBreed; }
  void SetBreed(BREED breed) { itsBreed = breed;}
  
  // other methods
  void WagTail() const { cout << "Tail wagging\n";}
  void BegForFood() const { cout << "Begging for food\n";}

  // overridden speak method
  void Speak() const {cout << "Woof!\n"; }

  // override the Move method
  void Move() const {cout << "Dog move 5 steps\n";}

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
  Mammal *fido = new Dog;
  Mammal *dino = new Mammal;
  Dog rex;
  //  fido->WagTail(); // Note that I cannot do this because Mammal doesn't have a WagTail method. I will learn about multiple inheritance later.
  cout << "Fido is "<<fido->GetAge() << " years old\n";
  cout << "Dino speak:";
  dino->Speak();
  cout << "Fido move:";
  fido->Move();
  cout << "Dino move:";
  dino->Move();
  cout << "Dino move 2:";
  dino->Move(2);
  cout << "Fido move 2:";
  fido->Move(2);  // Note I can call Move(int) even though fido is a Dog* because really it's a Mammal*
  cout << "Rex speak:";
  rex.Speak();  // Compare a real Dog::Speak() with a ptr to a Dog, below:
  cout << "Fido speak:";
  fido->Speak();  // Note that Mammal::Speak() is not virtual so this calls the Mammal speak even though fifo is a new Dog
  delete fido;
  delete dino;
}


