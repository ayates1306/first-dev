// Day 18
// Lesson: namespaces and using
// namespace creates a collection of objects; namespaces can be
// added to by multiple entities.
// 'using' is either a directive or a declaration, depending on context
// As a directive, using puts all of the namespace variables into current scope.
// As a declaration, it provides access to a specific variable (or class, etc)
// in a namespace rather than the whole namespace.
//
// unnamed namespaces are like static. Static is being deprecated apparently.
// Namespaces can be aliased too.
// A silly example would be:
// namespace s = std;
// s:cout << "s is an alias for std!" << s::endl;

#include <iostream>

// Namespaces prevent the linker error "<identifier> multiply defined"
// caused by multiple objects having the same name in scope.

int myvar = 1;

// unnamed namespace provides variables for only this translation 
// unit (ie module). There should be no clashes with other modules
// using the same variable names, provided that they are static or
// also in an unnamed namespace.
namespace {
  int some_variable;
  int another; 
}

// named namespaces
namespace myspace {
  int myvar;
}

// Adding another variable to a namespace
namespace myspace {
  int myvar2;
}

// which implies I can do this silly thing:
namespace std {
  int myvar3;
}

int main(void) {
  std::cout << "Myvar " << myvar << std::endl;
  int myvar =2;  // shadows global namespace myvar - no warning by default from g++

  // Note in the line below, using :: means take the variable
  // from the global namespace, not local scope.
  std::cout << "Global Myvar (using ::) " << ::myvar << std::endl;

  // Whereas here, myvar without :: means take the local scoped variable.
  std::cout << "Local Myvar " << myvar << std::endl;

  {
    int myvar = 3; // Yet another variable in a different scope
    std::cout << "Local Myvar " << myvar << std::endl;
    // Here, :: gets the global variable, not the outer scope variable.
    std::cout << "Global Myvar (using ::) " << ::myvar << std::endl;
  }

  myspace::myvar = 4;
  std::cout << "Myspace Myvar " << myspace::myvar << std::endl;
  myspace::myvar2 = 5;
  std::cout << "Myspace Myvar2 " << myspace::myvar2 << std::endl;

  // silly misuse of std namespace
  std::myvar3 = 6;
  std::cout << "std Myvar3 " << std::myvar3 << std::endl;

  // The 'using' directive
  std::cout << "Before namespace: Current scope Myvar " << myvar << std::endl;
  std::cout << "Before namespace: myspace::Myvar " << myspace::myvar << std::endl;

  {
    using namespace myspace;
    std::cout << "After namespace: Current scope Myvar " << myvar << std::endl;
    std::cout << "Note that the using directive did *not* make the myspace ";
    std::cout << "myvar take precedence over the local myvar." << std::endl;
  }

  // 'using' as a declaration
  {
    //    int myvar2 = 7;  // Cannot do this if I use myspace::myvar2 below...
    using myspace::myvar2;
    std::cout << "Myvar2 is only in myspace; Read access without qualifier: " << myvar2 << std::endl;
    myvar2++;
    std::cout << "Myvar2 is only in myspace; Write & read access without qualifier: " << myvar2 << std::endl;
  }

  std::cout << "My unnamed namespace variables : " << some_variable <<  " and " << another << std::endl;

  namespace s = std;
  s::cout << s::endl << "s is an alias for std!" << s::endl;

  return 0;
}
