// Example program to show c-style strings and the
// example string class interoperating

#include <iostream>
#include "string.hpp"

int main()
{
  String one= "One ";
  String two= "Two ";
  String three = one+two;
  const char* four = "Four ";
  std::cout << three.GetString() << std::endl;
  std::cout << four << std::endl;
  three = one+four;
  std::cout << three.GetString() << std::endl;
  three = four + one; // normally cannot use operator + on a const char*
  std::cout << three.GetString() << std::endl;

  return 0;
}
