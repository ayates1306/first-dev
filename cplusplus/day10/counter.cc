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
  Counter(const Counter & orig); // copy
  const Counter &operator++ (); // overloaded prefix ++ operator, now returns a reference
  Counter operator++(int); // overloaded postfix++ operator
  Counter operator+(const Counter &); // overload + operator
  Counter & operator=(const Counter&); // overload = operator, aka assignement
private:
  int itsVal;
};

// assignment operator
Counter & Counter::operator=(const Counter&rhs)
{
  cout << "Assignment operator " << endl;
  if (this == &rhs)
    return *this;
  itsVal = rhs.GetItsVal();
  return *this;
}

// Copy constructor; not the same as assignment operator
// because the assignment operator can delete the original
// object if it was mallocked.
Counter::Counter(const Counter & orig)
{
  cout << "Shalow Copy op"<< endl;
  itsVal = orig.GetItsVal();
}

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
const Counter & Counter::operator++()
{
  ++itsVal;
  return *this;
}

// overloading the postfix operator
// note that we pass in a int as an arg to tell the compiler
// that we are overloading the postfix; This *must* be an int!!
Counter Counter::operator++(int Flag)
{
  Counter temp(*this); // create a valued object
  ++itsVal; // Increment the object's counter value
  return temp; // and return the temporary copy
}

// overload the + operator, ie, the addition operator
Counter Counter::operator+(const Counter &rhs)
{
  return Counter(itsVal + rhs.GetItsVal());
}

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
  cout << "Use postfix++" << endl;
  Counter c = b++;
  cout << "The value of b is " << b.GetItsVal() << endl;
  cout << "The value of c is " << c.GetItsVal() << endl;
  c = i+b;
  cout << "c is now " << c.GetItsVal() << endl;
  return 0;
}

