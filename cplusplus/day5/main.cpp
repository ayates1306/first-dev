#include <iostream>

using namespace std;

void foo(int x = 50)
{
  cout << "Foo says x is " << x << endl;
}

int main(void)
{
  cout << "In main" << endl;
  foo (10);
  foo();
  return 0;
}
