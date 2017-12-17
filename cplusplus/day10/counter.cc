#include <iostream>

/* Operator overloading example */

using namespace std;

class Counter {
public:
  Counter();
  Counter(int val);
  ~Counter() {};
  int GetItsVal() const {return itsVal;}
  void SetItsVal(int x) {itsVal = x;}
  void Increment() {++itsVal;} // naive increment function
  Counter operator++ (); // overloaded ++ operator
private:
  int itsVal;
};

// Constructor with no arg
Counter::Counter():
  itsVal(0)
{
  cout << "New 0 counter" << endl;
}

// New constructor which takes a value
Counter::Counter(int val):
  itsVal(val)
{
  cout << "New assigned constructor "<<endl;
}

// I can return a Counter which is created automatically
Counter Counter::operator++()
{
  ++itsVal;
  return Counter(itsVal);
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

