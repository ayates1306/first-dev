#include <iostream>

class SimpleCat
{
public:
  SimpleCat();
  ~SimpleCat();
  int GetAge() const { return *this->itsAge; } // Note 'this'
  int GetJustAnInt() const { return this->JustAnInt; } // NB this is a pointer to the object so needs ->
private:
  int *itsAge;
  int JustAnInt;
};

SimpleCat::SimpleCat()
{
  itsAge = new int(2);
  JustAnInt = 6;
  std::cout << "Constructor\n";
}

SimpleCat::~SimpleCat()
{
  std::cout << "Destructor\n";
  delete itsAge;
}

int main()
{
  SimpleCat arashi;
  unsigned int *pi = new unsigned int; // throws an exception
  delete pi;
  pi = NULL;

  std::cout << "make paws\n";
  SimpleCat *paws;
  paws = new SimpleCat;
  std::cout << "and delete paws\n";
  std::cout << "Paws is " << paws->GetAge() << " years old\n";
  std::cout << "Paws' int " << paws->GetJustAnInt() << "\n";
  delete paws;

  std::cout << "end of program\n";
  return 0;
}
