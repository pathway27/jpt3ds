#include <ulib/ulib.h>
#include <vector>
#include <string>
#include "../Commands.h"
#include "../geometry/Point.h"
#include "../geometry/Dimension.h"
#include "../geometry/Rectangle.h"
#include "Component.h"
#include "../Tools.h"
#include "TextComponent.h"

using namespace jlpt;

TextComponent::TextComponent(Component* parent, char* text):Component(parent) {
	init(text);
}

TextComponent::TextComponent(Component* parent, char* txt, char* imageName):Component(parent, imageName) {
   init(txt);
}  
 
void TextComponent::init(char* txt) {
   maxLength = 255;
   if(txt != NULL) {
		this->text = new std::string(txt);
	} else {
	   this->text = new std::string("");
	}				
	int textWidth = ulGetStringWidth(txt);
	setSize(textWidth + 12, 20);
	xOffsetForText = 0;
	yOffsetForText = 7;
	textColor = RGB15(0, 0, 0);
	hasTextShadow = false;   
}
   
TextComponent::~TextComponent() {
	delete text;
}

int TextComponent::size() {
   if(text != NULL && text->data() != NULL) {
    	return text->size();  
   }
	return 0;
}   

void TextComponent::lower() {
   if(text != NULL && text->data() != NULL) {
      for(unsigned int i = 0; i < text->size(); i++) {
         char c = text->at(i);
         if(c >= 65 && c <= 90) {
	   		text->at(i) = c + 32;
	  		} 		
	   }   
   }   
}
 
void TextComponent::capitalize() {
   if(text != NULL && text->data() != NULL) {
      for(unsigned int i = 0; i < text->size(); i++) {
         char c = text->at(i);
         if(c >= 87 && c <= 122) {
		   	text->at(i) = c - 32;
		 	}  	
	   }   
   }   
}

void TextComponent::setMaxLength(int i) {
   maxLength = i;
} 

void TextComponent::addChar(int i) {
   if(text->size() < maxLength) {
	   text->push_back(i);
	}   
}   

void TextComponent::del() {
   if(text->size() > 0) {
		text->erase(text->size() - 1, 1);
	}		
} 

void TextComponent::clear() {
   if(text->size() > 0) {
   	text->clear();  
   }   
}   

void TextComponent::setText(const char* txt) {
   this->text = new std::string(txt);
}   

const char* TextComponent::getText() {
   return text->data();
}   

void TextComponent::setTextShadow(UL_COLOR color) {
	if(!hasTextShadow) {
		hasTextShadow = true;
		textShadowColor = color;
	}
}

void TextComponent::setXOffsetForText(int offset) {
   xOffsetForText = offset;
}

void TextComponent::setYOffsetForText(int offset) {
   yOffsetForText = offset;
}

void TextComponent::setTextColor(UL_COLOR color) {
	textColor = color;
}

void TextComponent::drawText() {
	// Dessin du texte associe
	if(text != NULL && text->data() != NULL) {
		int textWidth = ulGetStringWidth(text->data());
		// Texte et ombre
		if(hasTextShadow) {
		   drawShadowedText(text->data(), getX() + getWidth()/2 - textWidth/2 + xOffsetForText, getY() + yOffsetForText, textColor, textShadowColor);
		}
		// Texte seulement
		else {
		   Component::drawText(text->data(), getX() + getWidth()/2 - textWidth/2 + xOffsetForText, getY() + yOffsetForText, textColor);
		}
	}
}

void TextComponent::display(SCREEN scr) {
	Component::display(scr);
   if (visible && screen == scr) {
      drawText();
	}	
}
