#include <iostream>
#include <string.h>
// example string class
// will learn about [] operator overloading

using namespace std;

class String
{
public:
  // constructors
  String(); // basic constructor
  String(const char*); // constructor from const char*
  // copy constructor
 

  // destructor
  ~String();

  String& operator=(const String &);
  String operator+(const String &);
  char& operator[](unsigned int offset);
  char operator[](unsigned int offset) const;

  const char*GetString() const {return theStr;}

private:
  String(int); // private constructor
  char *theStr;
  unsigned int itsLen;
};

// constant offset operator
char String::operator[](unsigned int offset) const
{
  if (offset < itsLen)
    {
      return theStr[offset];
    }
  return theStr[itsLen-1];
}

char& String::operator[](unsigned int pos)
{
  if (pos < itsLen)
    return theStr[pos];
  else
    return theStr[itsLen-1];
}

String::String(int len)
{
  theStr = new char[len+1];
  for (int i=0;i<len;i++)
    {
      theStr[i] = '\0';
    }
  itsLen = len;
  cout << "Constructor(int), theStr @ "<< hex << theStr << "\n";
}

String::String(const char*str)
{
  itsLen = strlen(str);
  theStr = new char[itsLen+1];
  cout << "String created in constr str* " << hex << (long) theStr << "\n";
  cout << "const str is at " << hex << (long)str << " and its len was "<< dec << itsLen << endl;
  for (unsigned int i=0; i<itsLen;i++)
    {
      theStr[i] = str[i];
    }
  theStr[itsLen]='\0';
}

String::String() // basic constructor
{
  itsLen = 1;
  theStr = new char[1];
  theStr[0] = '\0';
  cout << "Constructor, void, @" << (unsigned long)theStr << "\n";
 }

String::~String()
{
  cout << "Destructor, theStr @ "<< hex << (long int)theStr<<"\n";
  if (theStr != NULL)
    {
    delete [] theStr;
    theStr = NULL;
    }
}

String String::operator+(const String &rhs)
{
  int TotalLen = itsLen + rhs.itsLen;
  String temp(TotalLen+1);
  for (unsigned i=0; i<itsLen; i++)
    {
      temp[i] = theStr[i];
    }
  for (unsigned i=0; i<rhs.itsLen; i++)
    {
      temp[itsLen+i] = rhs[i];
    }
  temp[TotalLen]='\0';
  return temp;
}

String& String::operator=(const String &rhs)
{
  cout << "assignment operator, this is "<<(long int)this << " &rhs @"<<(long int)&rhs<< "\n";
  if (this == &rhs)
    {
      cout << " this == &rhs\n";
    return *this;
    }
  // free this
  // new str based on len of rhs
  // copy str from rhs to this
  delete [] theStr;
  theStr = new char[rhs.itsLen+1];
  itsLen = rhs.itsLen;
  for (unsigned int i=0; i<rhs.itsLen; i++)
    {
      theStr[i] = rhs[i];
    }
  theStr[itsLen] = '\0';

  cout << "copied in operator =, new str @ " <<(unsigned long) theStr << "\n";
  return *this;
}

int main()
{
  String first = "hello";
  cout << "first made, @" <<  hex << (long int)&first << "\n";
  cout << "First says " << first.GetString() << "\n";

  String second = "second";
  cout << "Second made, @"<< hex << (long int)&second << "\n";
  cout << "Second says " << second.GetString() << "\n";

  first = second; // aka first = first.operator=(second);
  cout << "copied\n";
  cout << "First says " << first.GetString() << "\n";

  first = "thirdly";
  cout << "first made, @" <<  hex << (long int)&first << "\n";
  cout << "First says " << first.GetString() << "\n";

  first[3] = 'x'; // aka first.operator[](int);
  cout << "First says " << first.GetString() << "\n";
  cout << "Third element of first string is " << first[3] << endl;

  // addition operator
  // aka first.operator+(second)
  String third = first+second;

  cout << "After adding, third is " << third.GetString() << endl;

  return 0;
}

