#include <iostream>

using namespace std;

/* Overloading test 
 *
 * Overloading is where more than one function has the 
 * same name, but different parameter lists.
 * This is also known as polymorphism.
 *
 */


int Square(int a)
{
  cout << "double an int" << endl;
  return a*a;
}

long Square(long a)
{
  cout << "double a long" << endl;
  return a*a;
}

float Square(float a)
{
  cout << "double a float" << endl;
  return a*a;
}

double Square(double a)
{
  cout << "double a double" << endl;
  return a*a;
}

using namespace std;


int main(void)
{
  int i = 1, j;
  long l = 2, m;
  float f = 3.5, g;
  double d = 16.667, e;
  cout << "In main" << endl;
  
  j = Square(i);
  cout << "squared was " << j << endl;

  m = Square(l);
  cout << "long squared was " << m << endl;

  g = Square(f);
  cout << "float squared was " << g << endl;
  
  e = Square(d);
  cout << "double squared was " << e << endl;

  return 0;
}

