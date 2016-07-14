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
#include "KeyboardJis.h"

using namespace jlpt;

const s8 btn_location[NB_JIS_KEYS][2] = { 
    { 4, 5 }, { 20, 5 }, { 36, 5 }, { 52, 5 }, { 68, 5 }, 
    { 12, 21 }, { 28, 21 }, { 44, 21 }, { 60, 21 }, { 76, 21 }, 
    { 4, 37 }, { 20, 37 }, { 36, 37 }, { 52, 37 }, { 68, 37 } 
};

const s8 btn_size[NB_JIS_KEYS][2] = { 
    { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, 
    { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, { 23, 15 }, 
    { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, { 31, 15 } 
};

const int tile_number[NB_JIS_KEYS][2] = { 
    { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 }, 
    { 5, 0 }, { 6, 0 }, { 7, 0 }, { 8, 0 }, { -1, -1 },
    { 9, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, { -1, -1 }
};

char * btn_image[NB_JIS_KEYS] = { 
    "kanji.gif", "kanji.gif", "kanji.gif", "kanji.gif", "kanji.gif", 
    "kanji.gif", "kanji.gif", "kanji.gif", "kanji.gif", "keyboard_del.gif", 
    "kanji.gif", "kanji.gif", "kanji.gif", "kanji.gif", "keyboard_enter.gif" 
};

KeyboardJis::KeyboardJis(Component* parent) :
  Keyboard(parent) {
  imgTiles = NULL;
  this->setSize(103, 57);
  
  for (u8 i = 0; i < NB_JIS_KEYS; i++) {
    Button* button;

    if (tile_number[i][0] >= 0) {
      button = new Button(this, RGB15(31, 25, 0), "");
      button->setMaxDelay(5);
    } else {
      button = new Button(this, btn_image[i]);
      button->setMaxDelay(10);
    }
    button->setCommand(KEY_PRESSED);
    button->setTextColor(RGB15(0, 0, 0));
    button->setTextShadow(RGB15(31, 31, 31));

    button->setSize(btn_size[i][0], btn_size[i][1]);
    button->setLocation(btn_location[i][0], btn_location[i][1]);
    button->setYOffsetForText(4);
    add(button);
  }
}

KeyboardJis::~KeyboardJis() {
}

void KeyboardJis::display(SCREEN scr) {
  Component::display(scr);
  if (visible && screen == scr) {
    for(u8 i = 0; i < NB_JIS_KEYS; i++) {
      if(tile_number[i][0] >= 0) {
        u8 j = tile_number[i][0];
        u8 k = tile_number[i][1];        
        ulSetImageTile(imgTiles, 16*j, 16*k, 16*j + FONT_TILE_16x16, 16*k + FONT_TILE_16x16);
        ulDrawImageXY(imgTiles, this->getX() + btn_location[i][0], this->getY() + btn_location[i][1]);
      }
    }
  }
}

void KeyboardJis::show() {
  if (imgTiles == NULL) {
    imgTiles = loadImageGIF("kanji.gif", UL_PF_PAL4);
  } else {
    ulRealizeImage(imgTiles);
  }
  Component::show();
}

void KeyboardJis::hide() {

  if (imgTiles != NULL) {
    ulUnrealizeImage(imgTiles);
  }
  Component::hide();
}

int KeyboardJis::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {

    for (unsigned int i = 0; i < children.size(); i++) {
      Component* component = children.at(i);
      if (component->getType() == TYPE_BUTTON) {
        int cmd = component->dealEvent(scr);
        if (cmd == KEY_PRESSED) {
          const char* txt = ((Button*)component)->getText();
          // On a tapé un caractere
          if (txt != NULL && txt[0] != 0) {
            return txt[0];
          }
          // Touches speciales
          else {
            char* imageName = ((Button*)component)->getBackgroundImageName();
            std::string str = std::string(imageName);
            if (str.compare("keyboard_del.gif") == 0) {
              return KEY_DEL;
            } else if (str.compare("keyboard_enter.gif") == 0) {
              return KEY_ENTER;
            }
          }
        }
      }
    }
  }
  return CMD_NONE;
}
