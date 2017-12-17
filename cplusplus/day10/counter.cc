#include <iostream>

/* Operator overloading example */

using namespace std;

class Counter {
public:
  Counter();
  ~Counter() {};
  int GetItsVal() const {return itsVal;}
  void SetItsVal(int x) {itsVal = x;}
  void Increment() {++itsVal;} // naive increment function
  Counter operator++ (); // overloaded ++ operator
private:
  int itsVal;
};

Counter::Counter():
  itsVal(0)
{
  cout << "New counter" << endl;
}

// One way of overloading ++ is to return a newly created object
Counter Counter::operator++()
{
  Counter temp;
  ++itsVal;
  temp.SetItsVal(itsVal);
  return temp;
}

/*
Prefix operators are overloaded with this style:
returnType Operator op()
eg
void operator++ ()
 */


int main()
{
  Counter i;
  cout << "The value of i is " << i.GetItsVal() << endl;
  i.Increment();
  cout << "The value of i is " << i.GetItsVal() << endl;
  ++i; // calls prefix operator
  Counter b = ++i;
  cout << "The value of i is " << i.GetItsVal() << endl;
  cout << "The value of b is " << b.GetItsVal() << endl;
  return 0;
}

