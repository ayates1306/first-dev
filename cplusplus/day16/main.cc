// day16, containment
// Example program showing passing by value vs passing by reference.
// Note the number of constructors called.
// Calling pPrintFunc calls no more constructors (passing by value)
// whereas PrintFunc calls 3 constructors as part of the copy
// This is all very similar to C, passing pointers as opposed to
// passing by value.
#include "string.hpp"

class Employee
{
public:
  Employee();
  Employee(const char*, const char*, const char*, const long);
  ~Employee();
  Employee(const Employee&);
  Employee & operator=(const Employee&);

  const String & GetFirstName() const { return itsFirstName; }
  const String & GetLastName() const { return itsLastName;}
  const String & GetAddress() const { return itsAddress; }
  long GetSalary() const { return itsSalary; }

  void SetFirstName(const String &fName) { itsFirstName = fName;}
  void SetLastName(const String &lName) { itsLastName = lName;}
  void SetAddress(const String &addr) { itsAddress = addr;}
  void SetSalary(const long salary) { itsSalary = salary; }  
private:
  String itsFirstName;
  String itsLastName;
  String itsAddress;
  long itsSalary;  
};

Employee::Employee():
  itsFirstName(""),
  itsLastName(""),
  itsAddress(""),
  itsSalary(0)
{
}


Employee::Employee(const char * firstName, const char*lastName, const char*address, const long salary):
  itsFirstName(firstName),
  itsLastName(lastName),
  itsAddress(address),
  itsSalary(salary)
{
}

Employee::Employee(const Employee &rhs):
  itsFirstName(rhs.GetFirstName()),
  itsLastName(rhs.GetLastName()),
  itsAddress(rhs.GetAddress()),
  itsSalary(rhs.GetSalary())
{}

Employee::~Employee() {}

Employee & Employee::operator= (const Employee &rhs)
{
  if (this == &rhs)
    return *this;

  itsFirstName=rhs.GetFirstName();
  itsLastName=rhs.GetLastName();
  itsAddress=rhs.GetAddress();
  itsSalary=rhs.GetSalary();

  return *this;
}

void PrintFunc(Employee);
void rPrintFunc(const Employee&);

int main()
{
  cout << "Creating Edie...\n";
  Employee Edie ("Jane", "Doe", "1234 Shore Parkway", 20000);
  Edie.SetSalary(50000);
  cout << "Calling SetFirstName char*\n";
  Edie.SetFirstName("Edythe");
  cout << "Creating temporary string\n";
  String LastName("Levine");
  cout << "Calling SetLastName String\n";
  Edie.SetLastName(LastName);

  cout << "Construtor count " << String::ConstructorCount << "\n";
  rPrintFunc(Edie);
  cout << "Construtor count " << String::ConstructorCount << "\n";
  PrintFunc(Edie);
  cout << "Construtor count " << String::ConstructorCount << "\n";
  return 0;
}

void PrintFunc(Employee emp)
{
  cout << "Name : ";
  cout << emp.GetFirstName().GetString();
  cout << "." << emp.GetLastName().GetString();
  cout << "\nAddress : ";
  cout << emp.GetAddress().GetString();
  cout << "\nSalary : ";
  cout << emp.GetSalary();
  cout << endl;
}

void rPrintFunc(const Employee& emp)
{
  cout << "Name : ";
  cout << emp.GetFirstName().GetString();
  cout << "." << emp.GetLastName().GetString();
  cout << "\nAddress : ";
  cout << emp.GetAddress().GetString();
  cout << "\nSalary : ";
  cout << emp.GetSalary();
  cout << endl;
}

