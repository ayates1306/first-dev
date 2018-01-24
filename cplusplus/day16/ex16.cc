#include <iostream>
using namespace std;
class Animal;

void setValue(Animal&, int);
void setValue(Animal&, int, int);

class Animal
{
public:
  int GetWeight() const {return itsWeight;}
  int GetAge() const {return itsAge;}
  friend void setValue(Animal& theAnimal, int theWeight);
  friend void setValue(Animal& theAnimal, int theWeight, int theAge);
private:
  int itsWeight;
  int itsAge;
};

void setValue(Animal& theAnimal, int theWeight)
{
  //  friend class Animal;
  theAnimal.itsWeight = theWeight;
}

void setValue(Animal& theAnimal, int theWeight, int theAge)
{
  theAnimal.itsWeight = theWeight;
  theAnimal.itsAge = theAge;
}

int main()
{
  Animal peppy;
  setValue(peppy, 5);
  cout << peppy.GetWeight() <<endl;
  cout << peppy.GetAge() <<endl;
  return 0;
}
