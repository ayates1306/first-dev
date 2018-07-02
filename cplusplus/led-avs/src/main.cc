#include <iostream>
#include <vector>

/*

Configure vector of RGB LEDS


 */


class RGBLED {
public:
  RGBLED(int id);
  ~RGBLED();
  void Set(unsigned int hexrgb);
private:
  int id_;
};

RGBLED::RGBLED(int id) : id_(id) {
  std::cout << "Create RGB LED\n";
}

RGBLED::~RGBLED() {
  std::cout << "Create RGB LED\n";
}


class LEDGroup {
public:
  LEDGroup() {}
  ~LEDGroup() {}
  void AddLED(RGBLED*led);
  void Set(unsigned int hexrgb);
  void Set(unsigned int head_colour, unsigned int body_colour,
	   int head, int len);
  void Set(unsigned int head_colour, unsigned int body_colour,
	   unsigned int back_colour,
	   int head, int len);
private:
  std::vector<RGBLED*> LEDGroup_;
};

void RGBLED::Set(unsigned int hexrgb) {
  std::cout << id_ << " ";
  std::cout << std::hex << hexrgb << std::dec << " ";
}

void LEDGroup::AddLED(RGBLED*led) {
  LEDGroup_.push_back(led);
}

/* Basic operation to set all LEDs to the same colour */
void LEDGroup::Set(unsigned int hexrgb) {
  auto it = LEDGroup_.begin();
  while (it != LEDGroup_.end()) {
    (*it)->Set(hexrgb);
    it++;
  }
  std::cout << std::endl;
}

/* Operation to set the head node to one colour, then the next N to another */
void LEDGroup::Set(unsigned int head_colour, unsigned int body_colour,
		   int head, int len) {
  LEDGroup_[head]->Set(head_colour);
  auto it = std::next(LEDGroup_.begin(), head+1);

  while (len) {
    it++;
    if (it == LEDGroup_.end()) {
      it = LEDGroup_.begin();
    }
    (*it)->Set(body_colour);
    len--;
  }
}

/* Operation to set the head node to one colour, then the next N to another
 then finally the remaining LEDS some third colour*/
void LEDGroup::Set(unsigned int head_colour, unsigned int body_colour,
		   unsigned int back_colour,
		   int head, int len) {
  LEDGroup_[head]->Set(head_colour);
  auto it = std::next(LEDGroup_.begin(), head+1);
  auto initial = std::next(LEDGroup_.begin(), head);

  while (len) {
    if (it == LEDGroup_.end()) {
      it = LEDGroup_.begin();
    }
    (*it)->Set(body_colour);
    len--;
    it++;
  }

  do {
    (*it)->Set(back_colour);
    it++;
    if (it == LEDGroup_.end()) {
      it = LEDGroup_.begin();
    }
  } while (it != initial);
  
}



int main() {
  std::cout << "Alexa LED test\n";
  int i;
  LEDGroup myGroup;
  for (i=0; i<7; i++) {
    RGBLED*led = new RGBLED(i);
    myGroup.AddLED(led);
  }

  //  myGroup.Set(0xff);
  myGroup.Set(0xef, 0x7f, 0x00, 0, 2);
  std::cout << std::endl;

  myGroup.Set(0xef, 0x7f, 0x00, 5, 2);
  std::cout << std::endl;

  myGroup.Set(0xef, 0x7f, 0x00, 1, 3);
  std::cout << std::endl;

}


