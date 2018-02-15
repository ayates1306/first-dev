#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__
#include <iostream>
using namespace std;
const int DefaultSize = 10;

// In the line template <Class T>, the thing in brackets is what will
// change. It is the parameter.

template <class T>  // declare the template and the parameter
class Array   // Note that in this declararion, I can use Array
// but elsewhere I need to use Array<T>
{
 public:
  Array(int itsSize = DefaultSize);
  Array(const Array &rhs);
  ~Array() { delete [] pType; }

  // operators
  Array& operator=(const Array&);
  T& operator[](int offset) {return pType[offset];}
  const T& operator[](int offset) const {return pType[offset];}

  // accessors
  int GetSize() { return itsSize;}

private:
  T *pType;
  int itsSize;

};

// implementation follows below.
// Note that this implementation is a template definition so can live in 
// the header file, rather than a cpp file.

// constructor
template <class T>
Array<T>::Array(int size):
  itsSize(size)
{
  pType = new T[size];
  for (int i=0; i<size; i++)
    pType[i] = 0;

  std::cout << "Array constructed of size " << size << std::endl;
}


// copy constructor
template <class T>
Array<T>::Array(const Array &rhs)
{
  itsSize = rhs.GetSize();
  pType = new T[itsSize];
  for (int i=0; i<itsSize; i++)
    pType[i] = rhs[i];
}

// operator=
template <class T>
Array<T> & Array<T>::operator=(const Array &rhs)
{
  if (this == &rhs)
    return *this;
  delete [] pType;
  itsSize = rhs.GetSize();
  pType = new T[itsSize];
  for (int i=0; i<itsSize; i++)
    pType[i] = rhs[i];
  return *this;
}


#endif //  __TEMPLATE_H__
