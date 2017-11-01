#include <iostream>

using namespace std;

void foo(int x, int y=2, int z=3)
{
  cout << "Foo says x is " << x << endl;
}



int main(void)
{
  cout << "In main" << endl;
  foo (10, 20, 30);
  foo(4);
  return 0;
}
