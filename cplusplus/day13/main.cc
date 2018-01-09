#include <iostream>

// day13
// arrays and linked lists

using namespace std;

class CAT
{
public:
  CAT() { itsAge = 1;}
  ~CAT() {}
  int GetAge() const { return itsAge;}
private:
  int itsAge;
};

int main()
{
  CAT litter[5];
  CAT *plitter[5];
  int i;

  for (i=0; i<5; i++)
    {
      cout << "Kitten " << i << " is "<<litter[i].GetAge()<< " years old\n";
    }

  for (i=0; i<5; i++)
    {
      plitter[i] = new CAT;
      cout << "Kitten " << i << " is "<<plitter[i]->GetAge()<< " years old\n";
    }

  for (i=0; i<5; i++)
    {
      delete plitter[i];
    }

  cout << "Example of accepting input from the user. Enter some text now:";
  char buf[80];
  cin.get(buf, 79);
  cout << endl << "You typed " << buf << endl;

  return 0;
}
