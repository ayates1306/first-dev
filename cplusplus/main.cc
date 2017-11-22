#include <iostream>

/* Day 9 is about references 

References sound a little like pointers; it is an alias for some
other object. Actions performed on the references actually happen
on the object.


*/


int main()
{
  using namespace std;
  int intOne;
  int &rSomeRef = intOne;

  intOne = 5;
  cout << "IntOne:   " << intOne << endl;
  cout << "rSomeRef: " << rSomeRef << endl;

  rSomeRef = 7;

  cout << "IntOne:   " << intOne << endl;
  cout << "rSomeRef: " << rSomeRef << endl;

  return 0;
}
