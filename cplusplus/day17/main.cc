// streams
// cin and cout
// and stdio
// ">>" is the extraction operator; iostream has overloaded it 
// with a number of types, eg, int, short, char* etc

#include <iostream>
#include <cstdio>

void peek()
{
  char ch;
  std::cout << "Enter a phrase:";
  while (std::cin.get(ch))
    {
      if (ch == '!')
	std::cin.putback('$');
      else
	std::cout << ch;
      while (std::cin.peek() == '#')
	std::cin.ignore(1,'#');
    }
}

void get2()
{
  char stra[20];
  char strb[20];
  std::cout << "Enter first string :";
  std::cin.get(stra, 20); // this allows spaces in the input
  std::cout << "First string: " << stra << std::endl;

  // experiment to show how to (partially) flush the input buffer
  // before reading from it again with the extraction operator
  std::cin.ignore(20,'\n'); // ignores 20 characters or up to \n

  std::cout << "Enter next string :";
  std::cin >> strb; // see! this stops at a space
  std::cout << "Next string: " << strb << std::endl;
}

void get()
{
  char a,b,c;
  std::cout << "enter 3 letters:\n";
  std::cin.get(a).get(b).get(c);
  std::cout << "a: "<< a << " b: " << b << " c "<<c<<" \n";
}

void eof()
{
  char ch;
  std::cout << "Enter some text and press return; CTRL-D to finish\n";
  while ((ch = std::cin.get()) != EOF)
    {
      std::cout << "> " << ch /*<< std::hex << (int)ch*/ << std::endl;
    }
  std::cout << "All done!\n";
}

void cin_tests()
{
  int i;
  long l;
  double d;
  float f;
  unsigned int ui;
  char c[50];

  using namespace std;

  cout << "Int: ";
  cin >> i;
  cout << "Long: ";
  cin >> l;
  cout << "Double :";
  cin >> d;
  cout << "float :";
  cin >> f;
  cout << "uint :";
  cin >> ui;
  cout << "Your name :";
  cin >> c;   // Note that cin treats whitespace as the end of input!

  cout << "Int: " << i << endl;
  cout << "Long: " << l << endl;
  cout << "Double :"<< d << endl;
  cout << "float :" << f << endl;
  cout << "uint :" << ui << endl;
  cout << "String: "<< c << endl;
  cout << "\nNow multi line input.\n";
  cout << "Int, long, double:";
  cin >> i >> l >> d;
  cout << "Int: " << i << endl;
  cout << "Long: " << l << endl;
  cout << "Double :"<< d << endl;
  
}

int main()
{
  peek();
  return 0;
}

