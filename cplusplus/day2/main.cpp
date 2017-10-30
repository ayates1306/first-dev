#include <iostream>

int main(void)
{
  /* std:: provides some objects. cout is one of those objects */
  /* What else is in std:: and how can I find out?
     Clearly there is a header file somewhere...?
     std:: is the Standard Library, provided by every ANSI compliant compiler
     'std' is a namespace specifier
     << is the output redirection operator

     Next is to specify a namespace...
  */

  /* Now I want the compiler to look for everything in the std namespace */
  using namespace std;

  cout << "Hello world\n";
  cout << "here is 5 " << 5 << "\n";
  cout << endl;
  cout << (float)5/8 << endl;
  cout << "And a double now " << (double) 7000*7000 << endl;
  return 0;
}

