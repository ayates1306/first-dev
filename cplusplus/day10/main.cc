

/* Day 10
 * More advanced functions
 * overloading of members and operators
 * writing functions to support classes with dynamically allocated variables
 *
 * Remember, polymorphism is another word for overloading
 */



#include <iostream>

// Rectangle class
class Rectangle
{
public:
  // constructor
  Rectangle();
  Rectangle(int width, int height);
  ~Rectangle() {}

  // overload class function DrawShape
  void DrawShape(int aWidth, int aHeight, bool useObject=false) const;

  int GetWidth() const { return itsWidth; }
  int GetHeight() const { return itsHeight; }

private:
  int itsWidth;
  int itsHeight;
};

// constructor implementation which gives defaults
Rectangle::Rectangle()
{
  itsWidth = 15;
  itsHeight = 2;
}

// constructor implementation
Rectangle::Rectangle(int width, int height)
{
  itsWidth = width;
  itsHeight = height;
}


// Overloaded drawshape - takes 2 params
// width and height; draws the shape based
// on these args
void Rectangle::DrawShape(int width, int height, bool useObject) const
{
  if (useObject)
    {
      height = itsHeight;
      width = itsWidth;
    }
  for (int i=0; i<height; i++)
  {
    for (int j=0; j<width; j++)
      {
	std::cout << "*";
      }
    std::cout << "\n";
  }
}

int main()
{
  Rectangle theRect(30,5);
  Rectangle theSecondRect; // note omit parentheses
  // otherwise you get:
  //  error: request for member ‘DrawShape’ in ‘theSecondRect’, which is of non-class type ‘Rectangle()’ theSecondRect.DrawShape(5, 5, true);
  //
  std::cout << "theRect.DrawShape(5,5, true) :\n";
  theRect.DrawShape(5,5, true);
  std::cout << "theSecondRect.DrawShape(5,5, true) :\n";
  theSecondRect.DrawShape(5, 5, true);

  std::cout << "First rect width:" << theRect.GetWidth() << " and height " << theRect.GetHeight() << "\n";
  std::cout << "2nd rect width  :" << theSecondRect.GetWidth() << " and height " << theSecondRect.GetHeight() << "\n";

  return 0;
}

