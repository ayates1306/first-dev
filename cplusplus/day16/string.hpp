// day16; String class

#include <iostream>
#include <string.h>
using namespace std;

class String
{
public:
  // constructors
  String(); // basic constructor
  String(const char *const); // constructor from const char*
  String(const String&);  // copy constructor
  ~String();  // destructor

  // overloaded operators
  char& operator[](unsigned int offset);
  char operator[](unsigned int offset) const;
  String operator+(const String &);
  void operator+=(const String &);
  String& operator=(const String &);

  // General accessors
  int GetLen() const {return itsLen;}
  const char*GetString() const {return theStr;}
  static int ConstructorCount;

private:
  String(int); // private constructor
  char *theStr;
  unsigned int itsLen;
};

String::String() // basic constructor
{
  theStr = new char[1];
  theStr[0] = '\0';
  itsLen = 1;
  //    cout << "\tConstructor, void, @" << (unsigned long)theStr << "\n";
   ConstructorCount++;
}

// private helper constructor, used only by
// class methods to create a String of a
// given size. NULL filled.
String::String(int len)
{
  theStr = new char[len+1];
  for (int i=0;i<len;i++)
    {
      theStr[i] = '\0';
    }
  itsLen = len;
  //    cout << "\tConstructor(int), theStr @ "<< hex << theStr << "\n";
   ConstructorCount++;
}

// converts a char array into a String
String::String(const char*const str)
{
  itsLen = strlen(str);
  theStr = new char[itsLen+1];
  for (unsigned int i=0; i<itsLen;i++)
      theStr[i] = str[i];
  theStr[itsLen]='\0';
  //  cout << "\tConstructor(char*), theStr @ "<< hex << theStr << "\n";
   ConstructorCount++;
}

// copy constructor
String::String(const String &rhs)
{
  itsLen = rhs.itsLen;
  theStr = new char[itsLen+1];
  for (unsigned int i=0; i<itsLen;i++)
      theStr[i] = rhs[i];
  theStr[itsLen]='\0';
  //cout << "\tCopy Constructor\n";
   ConstructorCount++;
}

// destructor, frees allocated memory
String::~String()
{
  delete [] theStr;
  itsLen = 0;
 cout << "\tString destructor\n";
}

// assignment operator/operator equals; frees existing memory then 
// copies string and size
String& String::operator=(const String &rhs)
{
  if (this == &rhs)
    {
      cout << " \tthis == &rhs\n";
      return *this;
    }
  // free this
  // new str based on len of rhs
  // copy str from rhs to this
  delete [] theStr;
  theStr = new char[rhs.itsLen+1];
  itsLen = rhs.itsLen;
  for (unsigned int i=0; i<rhs.itsLen; i++)
      theStr[i] = rhs[i];
  theStr[itsLen] = '\0';

  //    cout << "\tcopied in operator =, new str @ " <<(unsigned long) theStr << "\n";
  return *this;
}
 
// constant offset operator
char String::operator[](unsigned int offset) const
{
  if (offset < itsLen)
      return theStr[offset];
  else
    return theStr[itsLen-1];
}

// creates a new string by appending the rhs to the
// current string
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

// change current string; return nothing
void String::operator+=(const String&rhs)
{
  unsigned int rhsLen = rhs.GetLen();
  unsigned int totalLen = rhsLen + itsLen;
  String temp(totalLen);
  unsigned int i,j;
  for (i=0; i<itsLen; i++)
    temp[i] = theStr[i];
  for (j=0; j<rhsLen; j++, i++)
    temp[i] = rhs[j];
  temp[totalLen] = '\0';
  *this = temp;
}

// non constant offset operator. Returns
// reference to character so it can be changed
char& String::operator[](unsigned int pos)
{
  if (pos < itsLen)
    return theStr[pos];
  else
    return theStr[itsLen-1];
}

 int String::ConstructorCount = 0;


