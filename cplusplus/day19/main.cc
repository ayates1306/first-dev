#include <iostream>
#include "template.h"

class Animal { // will be a common base class for Horse and Bird
public:
  Animal() {itsWeight = 0;}
  Animal(int);
  ~Animal() {};
  int GetWeight() const { return itsWeight; }
  void Display() const { std::cout << itsWeight; }
private:
  int itsWeight;
};

Animal::Animal(int weight):
  itsWeight(weight)
{
}


int main()
{
  Array<int> theArray;
  Array<Animal> theZoo;
  Animal * pAnimal;

  // fill the arrays
  for (int i=0; i<theArray.GetSize(); i++)
    {
      theArray[i] = i*2;
      pAnimal = new Animal(i*3); // weight
      theZoo[i] = *pAnimal;
      delete pAnimal;
    }

  // now print the contents of the arrays
  for (int i=0; i<theArray.GetSize(); i++)
    {
      std::cout << "theArray[" << i << "]:\t";
      std::cout << theArray[i] << "\t\t";
      std::cout << "theZoo[" << i << "]:\t";
      theZoo[i].Display();
      std::cout << std::endl;
    }


  return 0;
}
