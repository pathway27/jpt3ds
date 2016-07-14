#include <ulib/ulib.h>
#include <vector>
#include <string>
#include "../Commands.h"
#include "../geometry/Point.h"
#include "../geometry/Dimension.h"
#include "../geometry/Rectangle.h"
#include "Component.h"
#include "TextComponent.h"
#include "../Tools.h"
#include "Input.h"

using namespace jlpt;

Input::Input(Component* parent, char* txt):TextComponent(parent, txt) {
	type = TYPE_INPUT;
}
   
Input::~Input() {
	delete text;
}  

void Input::display(SCREEN scr) {
	TextComponent::display(scr);
   if (visible && screen == scr) {
      drawCursor();
	}	
}

void Input::drawCursor() {
   if(nbFrame >= 0 && nbFrame <= 30) {
	   int textWidth = ulGetStringWidth(text->data());   
		ulDrawFillRect(getX() + getWidth()/2 + textWidth/2, getY() + yOffsetForText - 2, getX() + getWidth()/2 + textWidth/2 + 2, getY() + yOffsetForText + 10, RGB15(0,0,0));
	}
}   
