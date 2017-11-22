#include <iostream>

/* Day 9 is about references 

References sound a little like pointers; it is an alias for some
other object. Actions performed on the references actually happen
on the object.

References must be initialised otherwise you get the "x is declared as a reference but is not initalized" error.

Asking for the address of a reference returns the address of the object.

References cannot be reassigned.
rSomeRef = intTwo is actually logically the same as dereferencing a pointer:
*(pSomePtr) = intTwo; Here you'd never expect pSomePtr to change, more, its target gets its value reassigned to intTwo. This is the same as what happens with a reference.

*/

void swap(int &a, int &b)
{
  int tmp;
  tmp = a;
  a = b;
  b = tmp;
}


int main()
{
  using namespace std;
  int intOne, intTwo;
  int &rSomeRef = intOne;


  intOne = 5;
  intTwo = 8;
  cout << "IntOne:   " << intOne << endl;
  cout << "IntTwo:   " << intTwo << endl;
  cout << "rSomeRef: " << rSomeRef << endl;

  rSomeRef = intTwo; // Actually the same as intOne = intTwo!!!

  cout << "IntOne:   " << intOne << endl;
  cout << "IntTwo:   " << intTwo << endl;
  cout << "rSomeRef: " << rSomeRef << endl;

  cout << "Address of intOne " << &intOne << endl;
  cout << "Address of rSomeRef " << &rSomeRef << endl;

  intOne = 1;
  intTwo = 2;

  cout << "Before swap: intOne " << intOne << " intTwo  " << intTwo << endl;
  swap(intOne, intTwo); // Careful - if the prototype takes references, the variables will be altered; if the function takes values, they are not.
  cout << "After swap: intOne " << intOne << " intTwo  " << intTwo << endl;


  return 0;
}
