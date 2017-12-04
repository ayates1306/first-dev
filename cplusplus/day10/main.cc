

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
  Rectangle(int width, int height);
  ~Rectangle() {}

  // overload class function DrawShape
  void DrawShape(int aWidth, int aHeight, bool useObject=false) const;

private:
  int itsWidth;
  int itsHeight;
};

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
  std::cout << "DrawShape(5,5, true) :\n";
  theRect.DrawShape(5,5, true);
  std::cout << "DrawShape(5,5) :\n";
  theRect.DrawShape(5, 5);

  return 0;
}

