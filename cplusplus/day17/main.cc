// streams
// cin and cout
// and stdio
// ">>" is the extraction operator; iostream has overloaded it
// with a number of types, eg, int, short, char* etc

#include <string.h>
#include <fstream>
#include <iostream>
#include <iomanip>  // for ::ios
#include <locale>
#include <cstdio>

void file_test() {
  // NB iostream flags for file operations:
  // eof(), bad(), fail(), good()
  std::ofstream fout("myfile.dat");  // for input would be ifstream
  fout << "This line is written to myfile." << std::endl;
  fout.close();

  std::ifstream fin("myfile.dat");
  char ch;
  while (fin.get(ch))
    std::cout << ch;
  fin.close();

  // note, can do fin.read(char*buf, int len), or fout.write(char*buf, int len)

}

void peek() {
  char ch;
  std::cout << "Enter a phrase:";
  while (std::cin.get(ch))    {
    if (ch == '!')
      std::cin.putback('$');
    else
      std::cout << ch;
    while (std::cin.peek() == '#')
      std::cin.ignore(1, '#');
  }
}

void get2() {
  char stra[20];
  char strb[20];
  std::cout << "Enter first string :";
  std::cin.get(stra, 20);  // this allows spaces in the input
  std::cout << "First string: " << stra << std::endl;

  // experiment to show how to (partially) flush the input buffer
  // before reading from it again with the extraction operator
  std::cin.ignore(20, '\n');  // ignores 20 characters or up to \n

  std::cout << "Enter next string :";
  std::cin >> strb;  // see! this stops at a space
  std::cout << "Next string: " << strb << std::endl;
}

void get() {
  char a, b, c;
  std::cout << "enter 3 letters:\n";
  std::cin.get(a).get(b).get(c);
  std::cout << "a: "<< a << " b: " << b << " c " << c <<" \n";
}

void eof() {
  char ch;
  std::cout << "Enter some text and press return; CTRL-D to finish\n";
  while ((ch = std::cin.get()) != EOF)    {
      std::cout << "> " << ch /*<< std::hex << (int)ch*/ << std::endl;
    }
  std::cout << "All done!\n";
}

void cin_tests() {
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

void cout_tests(void) {
  char one[] = "this is a test string";
  std::cout.put('h').put('e').put('l').put('\n');
  std::cout << std::flush;

  int fullLen = strlen(one);
  int shorter = fullLen -2;
  int longer = fullLen +10;

  std::cout.write(one, fullLen) << std::endl;
  std::cout.write(one, shorter) << std::endl;
  std::cout.write(one, longer) << std::endl;  // NB will display whatever happens to be in memory after my string

  std::cout << "start >";
  std::cout.width(25);
  std::cout << 123 << "< End\n";

  std::cout << "start >";
  std::cout.width(25);
  std::cout.fill('*');
  std::cout << 123 << "< next >";
  std::cout << 456 << "< end\n";

  std::cout << "Start >";
  std::cout.width(4);
  std::cout << 1234567 << "< end\n";

const int number = 65;
  // setf() functionality to set ios flags, where ios is IO Stream
  std::cout.fill(' ');

  std::cout.setf(std::ios::showbase);
  std::cout << "The number is " << std::hex << number << std::endl;
  std::cout << "The number is " << std::dec << number << std::endl;
  std::cout << "The number is " << std::oct << number << std::endl;
  std::cout.unsetf(std::ios::showbase);
  std::cout << "The number is " << std::hex << number << std::endl;

  std::cout.setf(std::ios::showbase);
  std::cout << "The number is " << std::hex << number << std::endl;
  std::cout << "The number is ";
  std::cout.width(10);
  std::cout << std::hex << number << std::endl;

  std::cout << "The number is ";
  std::cout.width(10);
  std::cout.setf(std::ios::left);
  std::cout << std::hex << number << std::endl;

  std::cout << "The number is ";
  std::cout.setf(std::ios::internal);  // Odd - this doesn't seem to affect the output later
  std::cout.width(10);
// I actually need to use std::setw(10) here as workaround for setf() not doing what I expect.
  std::cout << std::internal << std::setw(10) << std::dec << (0-number) << std::endl;

  std::cout << "The number is " << std::setw(10) << std::hex << number << std::endl;

  std::cout << "Internal fill:\n" << std::internal
              << std::setw(12) << -1.23  << '\n'
              << std::setw(12) << 42 << '\n'
              << std::setw(12) << std::put_money(123, true) << "\n\n";
}

int main() {
  file_test();
 
  return 0;
}

