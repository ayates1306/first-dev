#include <iostream>

using namespace std;

/* Overloading test 
 *
 * Overloading is where more than one function has the 
 * same name, but different parameter lists.
 * This is also known as polymorphism.
 *
 */


int Double(int a)
{
  cout << "double an int" << endl;
  return a*a;
}

long Double(long a)
{
  cout << "double a long" << endl;
  return a*a;
}

float Double(float a)
{
  cout << "double a float" << endl;
  return a*a;
}

double Double(double a)
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
  
  j = Double(i);
  cout << "doubled was " << j << endl;

  m = Double(l);
  cout << "long doubled was " << m << endl;

  g = Double(f);
  cout << "float doubled was " << g << endl;
  
  e = Double(d);
  cout << "double doubled was " << e << endl;

  return 0;
}

