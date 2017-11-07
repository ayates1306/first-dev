#include <iostream>


/* Day 6 notes
   C++ object extend the language, as opposed to C which has no
   language extensions.
   Extensions means the ability to create new objects with functions
   and data types.
   A new type is created by declaring a class.
   Encapsulations bundles data and functions into a collection called an object.
   It sounds like a class is an object (or, an object is an instantiation of a class).

   Variables in a class are known as member variables, or data members.
   Functions in a class typically work on the member variables.
   They are known as member functions, or Methods.

   use 'class' keyword to define a class.
   use the dot operator to access variables or methods in a class.

   variables in a class are private by default. Private means they can only be accessed by other methods of the class.

   General rule is to keep member variables private and provide public accessor functions. This means that we can change the actual implementation of the variables (eg, the type of variables) without exposing this to the outside world.
   The accessor function fetches the variable, potentially using a new object type. ints vs unsigned ints, or a new "age" type?
   We might even calculate the variable on the fly; this is all hidden behind the accessor.


 */

class Cat {
public:  // member variables and methods which follow are public
  unsigned int itsAge; // its here can differentiate member variables from non member variables 
  unsigned int itsWeight;
  void meow();
};

// are there any VT class/C++ conventions?
// read the OrbPlayer code? Or is that now "old"?

int main()
{
  Cat frisky;  // this creates an object of type Cat. The variable name is frisky.

  frisky.itsAge = 10;
  frisky.itsWeight = 30;
  frisky.meow();

 return 0;
}

