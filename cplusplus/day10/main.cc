

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
  void DrawShape() const;
  void DrawShape(int aWidth, int qHeight) const;

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

// overloaded DrawShape - takes no parameters
// and draws a shape based on the current
// class member values
void Rectangle::DrawShape() const
{
  DrawShape(itsWidth, itsHeight);
}

// Overloaded drawshape - takes 2 params
// width and height; draws the shape based
// on these args
void Rectangle::DrawShape(int width, int height) const
{
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
  std::cout << "DrawShape() :\n";
  theRect.DrawShape();
  std::cout << "DrawShape(20,10) :\n";
  theRect.DrawShape(20, 10);

  return 0;
}

