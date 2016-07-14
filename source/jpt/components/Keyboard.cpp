#include <ulib/ulib.h>
#include <vector>
#include "../Commands.h"
#include "../geometry/Point.h"
#include "../geometry/Dimension.h"
#include "../geometry/Rectangle.h"
#include "Component.h"
#include "TextComponent.h"
#include "../Tools.h"
#include "Button.h"
#include "Keyboard.h"

using namespace jlpt;

Keyboard::Keyboard(Component* parent) :
  Component(parent) {

  this->setBackgroundColor(RGB15(31, 31, 31), 16);
  this->setSize(200, 90);
  this->setLocation(28, 54);
  this->setBorder(RGB15(0, 0, 0), 2, 31);
  this->setShadow(RGB15(0, 0, 0), 3);
}

Keyboard::~Keyboard() {
}
