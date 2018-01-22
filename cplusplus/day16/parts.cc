// day 16, parts catalogue
// to demonstrate delegation to contained parts list

#include <iostream>
using namespace std;

// ****** Part ********************
// Abstract class of parts
class Part
{
public:
  Part():itsPartNumber(1) {}
  Part(int PartNumber): itsPartNumber(PartNumber) {}
  virtual ~Part(){};
  int GetPartNumber() const { return itsPartNumber; }
  virtual void Display() const = 0;
private:
  int itsPartNumber;
};

// implementation of pure virtual function so that 
// derived classes can chain up

void Part::Display() const
{
  cout << endl << "Part Number: " << itsPartNumber << endl;
}

// ********** Car Part ********************
class CarPart : public Part
{
public:
  CarPart():itsModelYear(94){}
  CarPart(int year, int PartNumber);
  ~CarPart();
  virtual void Display() const
  {
    Part::Display(); // chain up
    cout << "Model year: ";
    cout << itsModelYear << endl;
  }
private:
  int itsModelYear;
};

CarPart::~CarPart()
{
}

CarPart::CarPart(int year, int PartNumber):
  Part(PartNumber),
  itsModelYear(year)
{
}

// ********** Airplane part ********************
class AirPlanePart: public Part
{
public:
  AirPlanePart():itsEngineNumber(1){}
  AirPlanePart(int EngineNumber, int PartNumber);
  virtual void Display() const
  {
    Part::Display();
    cout << "Engine No.:";
    cout << itsEngineNumber << endl;
  }
private:
  int itsEngineNumber;
};

AirPlanePart::AirPlanePart(int EngineNumber, int PartNumber):
  Part(PartNumber),
  itsEngineNumber(EngineNumber)
{
}

// ********** Part Node ********************
class PartNode
{
public:
  PartNode(Part*);
  ~PartNode();
  void SetNext(PartNode*node)
  {
    itsNext = node;
  }
  PartNode* GetNext() const;
  Part* GetPart() const;
private:
  Part *itsPart;
  PartNode *itsNext;
};
// PartNode implementation

PartNode::PartNode(Part* pPart):
  itsPart(pPart),
  itsNext(0)
{
}

PartNode::~PartNode()
{
  delete itsPart;
  itsPart = 0;
  delete itsNext;
  itsNext = 0;
}

// return NULL if no next PartNode
PartNode * PartNode::GetNext() const
{
  return itsNext;
}

Part * PartNode::GetPart() const
{
  if (itsPart)
    return itsPart;
  else
    return NULL;
}

// ********** Part List ********************
class PartsList
{
public:
  PartsList();
  ~PartsList();
  // needs copy constructor and operator equals
  void Iterate(void (Part::*f)()const) const;
  Part*Find(int &position, int PartNumber) const;
  Part*GetFirst() const;
  void Insert(Part*);
  Part* operator[](int) const;
  int GetCount() const { return itsCount ;}
  static PartsList& GetGlobalPartsList()
  {
    return GlobalPartsList;
  }
private:
  PartNode *pHead;
  int itsCount;
  static PartsList GlobalPartsList;
};

PartsList PartsList::GlobalPartsList;

PartsList::PartsList():
  pHead(0),
  itsCount(0)
{}

PartsList::~PartsList()
{
  delete pHead;
}

Part * PartsList::GetFirst() const
{
  if (pHead)
    return pHead->GetPart();
  else
    return NULL;
}

Part * PartsList::operator[](int offset) const
{
  PartNode * pNode = pHead;
  if (!pHead)
    return NULL;
  if (offset > itsCount)
    return NULL;
  for (int i=0; i<offset; i++)
    pNode = pNode->GetNext();
  return pNode->GetPart();
}

Part * PartsList::Find(int &position, int PartNumber) const
{
  PartNode *pNode = 0;
  for (pNode = pHead, position = 0; 
       pNode != NULL;
       pNode = pNode->GetNext(), position++)
    {
      if (pNode->GetPart()->GetPartNumber() == PartNumber)
	{
	  break;
	}
    }
  if (pNode == NULL)
    return NULL;
  else
    return pNode->GetPart();
}

void PartsList::Iterate(void (Part::*func)()const) const
{
  if (!pHead)
    return;
  PartNode*pNode = pHead;
  do
    (pNode->GetPart()->*func)();
  while ((pNode = pNode->GetNext()));
}

void PartsList::Insert(Part*pPart)
{
  PartNode * pNode = new PartNode(pPart); // copy of pPart passed in
  PartNode * pCurrent = pHead;
  PartNode * pNext = 0;

  int New = pPart->GetPartNumber();
  int Next = 0;
  itsCount++;

  if (!pHead)
    {
      pHead = pNode; // this becomes the LL head
      return;
    }
  
  // if this is smaller than the head, then
  // this becomes the new head
  if (pHead->GetPart()->GetPartNumber() > New)
    {
      pNode->SetNext(pHead);
      pHead = pNode;
      return;
    }

  for (;;)
    {
      // if there is no next then this goes afer it
      if (pCurrent->GetNext() == NULL)
	{
	  pCurrent->SetNext(pNode);
	  return;
	}
      // if the part goes after this one but before
      // the next one, then insert it here.
      pNext = pCurrent->GetNext();
      Next = pNext->GetPart()->GetPartNumber();
      if (Next > New)
	{
	  pCurrent->SetNext(pNode);
	  pNode->SetNext(pNext);
	  return;
	}
      pCurrent = pNext;
    }
}

class PartsCatalogue : private PartsList
{
public:
  void Insert(Part*);
  int Exists(int PartNumber);
  Part* Get(int PartNumber);
  void operator+(const PartsCatalogue &);
  void ShowAll() { Iterate(&Part::Display);}
private:
};

void PartsCatalogue::Insert(Part *newPart)
{
  int partNumber = newPart->GetPartNumber();
  int offset;

  if (!Find(offset, partNumber))
    PartsList::Insert(newPart); // note qualification to avoid calling itself
  else
    {
      cout << partNumber << "was already the ";
      switch (offset)
	{
	case 0: cout << "first\n"; break;
	case 1: cout << "second\n"; break;
	case 2: cout << "third\n"; break;
	default: cout << offset+1 << "th\n"; break;
	}
      cout << "rejected!\n";
    }
}

int PartsCatalogue::Exists(int PartNum)
{
  int offset;
  Find(offset, PartNum);
  return offset;
}

Part * PartsCatalogue::Get(int PartNum)
{
  int offset;
  Part * thePart = Find(offset, PartNum);
  return thePart;
}

int main()
{
  PartsCatalogue pc;
  Part *pPart = 0;
  int PartNumber;
  int value;
  int choice;

  while (1)
    {
      cout << "(0) Quit (1) Car (2) Plane : ";
      cin >> choice;

      if (!choice)
	break;

      cout << "New Partnumber?: ";
      cin >> PartNumber;

      if (choice == 1)
	{
	  cout << "Model year? ";
	  cin >> value;
	  pPart = new CarPart(value, PartNumber);
	}
      else
	{
	  cout << "Engine number? ";
	  cin >> value;
	  pPart = new AirPlanePart(value, PartNumber);
	}
      pc.Insert(pPart);
    }
  pc.ShowAll();
  return 0;
}
