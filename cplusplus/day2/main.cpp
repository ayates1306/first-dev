#include <iostream>

int main(void)
{
  /* std:: provides some objects. cout is one of those objects */
  /* What else is in std:: and how can I find out?
     Clearly there is a header file somewhere...?
     std:: is the Standard Library, provided by every ANSI compliant compiler
     'std' is a namespace specifier
     << is the output redirection operator


  */
  std::cout << "Hello world\n";
  std::cout << "here is 5 " << 5 << "\n";
  std::cout << std::endl;
  std::cout << (float)5/8 << std::endl;
  std::cout << "And a double now " << (double) 7000*7000 << std::endl;
  return 0;
}

