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
#include "KeyboardAscii.h"

using namespace jlpt;

const int button_location[50][2] = { { 4, 5 }, { 20, 5 }, { 36, 5 }, { 52, 5 },
    { 68, 5 }, { 84, 5 }, { 100, 5 }, { 116, 5 }, { 132, 5 }, { 148, 5 }, {
        164, 5 }, { 180, 5 }, { 12, 21 }, { 28, 21 }, { 44, 21 }, { 60, 21 }, {
        76, 21 }, { 92, 21 }, { 108, 21 }, { 124, 21 }, { 140, 21 },
    { 156, 21 }, { 172, 21 }, { 4, 37 }, { 20, 37 }, { 36, 37 }, { 52, 37 }, {
        68, 37 }, { 84, 37 }, { 100, 37 }, { 116, 37 }, { 132, 37 },
    { 148, 37 }, { 164, 37 }, { 4, 53 }, { 28, 53 }, { 44, 53 }, { 60, 53 }, {
        76, 53 }, { 92, 53 }, { 108, 53 }, { 124, 53 }, { 140, 53 },
    { 156, 53 }, { 172, 53 }, { 36, 69 }, { 52, 69 }, { 68, 69 }, { 148, 69 },
    { 164, 69 } };

const int button_size[50][2] = { { 15, 15 }, { 15, 15 }, { 15, 15 },
    { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, {
        15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, {
        15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, {
        15, 15 }, { 23, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, {
        15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, {
        31, 15 }, { 23, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, {
        15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, { 15, 15 }, {
        15, 15 }, { 15, 15 }, { 79, 15 }, { 15, 15 }, { 15, 15 } };

char* button_text[50] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
    "-", "=", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", NULL, NULL,
    "a", "s", "d", "f", "g", "h", "j", "k", "l", NULL, NULL, "z", "x", "c",
    "v", "b", "n", "m", ",", ".", "/", ";", "'", NULL, "[", "]" };

char* button_image[50] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, "keyboard_del.gif", "keyboard_caps.gif", NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, "keyboard_enter.gif",
        "keyboard_shift.gif", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, "keyboard_space.gif", NULL, NULL };

bool button_mode[50][2] = { { false, true }, { false, true }, { false, true },
    { false, true }, { false, true }, { false, true }, { false, true }, {
        false, true }, { false, true }, { false, true }, { false, true }, {
        false, true }, { true, true }, { true, true }, { true, true }, { true,
        true }, { true, true }, { true, true }, { true, true }, { true, true },
    { true, true }, { true, true }, { true, true }, { false, true }, { true,
        true }, { true, true }, { true, true }, { true, true }, { true, true },
    { true, true }, { true, true }, { true, true }, { true, true }, { true,
        true }, { false, true }, { true, true }, { true, true },
    { true, true }, { true, true }, { true, true }, { true, true }, { true,
        true }, { false, true }, { false, true }, { false, true }, { false,
        true }, { false, true }, { true, true }, { false, true },
    { false, true } };

KeyboardAscii::KeyboardAscii(Component* parent, KB_MODE mode) :
  Keyboard(parent) {
  capsPressed = false;
  shiftPressed = false;

  for (int i = 0; i < 50; i++) {
    bool isActive = button_mode[i][mode];
    Button* button;

    // Bouton actif
    if (isActive) {
      if (button_text[i] != NULL) {
        button = new Button(this, RGB15(31, 25, 0), button_text[i]);
        button->setMaxDelay(5);
      } else {
        button = new Button(this, button_image[i]);
        button->setMaxDelay(10);
      }
      button->setCommand(KEY_PRESSED);
      button->setTextColor(RGB15(0, 0, 0));
      button->setTextShadow(RGB15(31, 31, 31));
    }
    // Bouton inactif
    else {
      button = new Button(this, RGB15(20, 20, 20), button_text[i]);
      button->setBackgroundColor(RGB15(20, 20, 20), 16);
      button->setTextColor(RGB15(31, 31, 31));
      button->setTextShadow(RGB15(0, 0, 0));
    }

    button->setSize(button_size[i][0], button_size[i][1]);
    button->setLocation(button_location[i][0], button_location[i][1]);
    button->setYOffsetForText(4);
    add(button);
  }
}

KeyboardAscii::~KeyboardAscii() {
}

void KeyboardAscii::pressCaps() {
  // Changement de l'etat de la touche
  if (capsPressed) {
    capsPressed = false;
  } else {
    capsPressed = true;
  }

  // Desactivation du shift
  shiftPressed = false;

  // Modification du texte des touches
  for (unsigned int i = 0; i < children.size(); i++) {
    Component* component = children.at(i);
    if (component->getType() == TYPE_BUTTON) {
      if (capsPressed) {
        ((Button*)component)->capitalize();
      } else {
        ((Button*)component)->lower();
      }
    }
  }
}

void KeyboardAscii::pressShift() {
  // Changement de l'etat de la touche
  if (shiftPressed) {
    shiftPressed = false;
  } else {
    shiftPressed = true;
  }

  // Desactivation du caps
  capsPressed = false;
  
  // Modification du texte des touches
  for (unsigned int i = 0; i < children.size(); i++) {
    Component* component = children.at(i);
    if (component->getType() == TYPE_BUTTON) {
      if (shiftPressed) {
        ((Button*)component)->capitalize();
      } else {
        ((Button*)component)->lower();
      }
    }
  }
}

int KeyboardAscii::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {

    for (unsigned int i = 0; i < children.size(); i++) {
      Component* component = children.at(i);
      if (component->getType() == TYPE_BUTTON) {
        int cmd = component->dealEvent(scr);
        if (cmd == KEY_PRESSED) {
          const char* txt = ((Button*)component)->getText();
          // On a tapé un caractere
          if (txt != NULL && txt[0] != 0) {
            if (shiftPressed) {
              pressShift();
            }
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
            } else if (str.compare("keyboard_caps.gif") == 0) {
              pressCaps();
              return KEY_CAPS;
            } else if (str.compare("keyboard_shift.gif") == 0) {
              pressShift();
              return KEY_SHIFT;
            } else if (str.compare("keyboard_space.gif") == 0) {
              return KEY_SPACE;
            }
          }
        }
      }
    }
  }
  return CMD_NONE;
}
