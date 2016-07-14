#include <PA9.h>
#include "snd_button.h"
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

using namespace jlpt;

Button::Button(Component* parent, char* imageName) :
  TextComponent(parent, NULL, imageName) {
  init();
}

Button::Button(Component* parent, UL_COLOR color, char* text) :
  TextComponent(parent, text) {
  init();
  setBackgroundColor(color, 31);
  int textWidth = ulGetStringWidth(text);
  setSize(textWidth + 12, 20);
  yOffsetForText = 7;

}

void Button::init() {
  type = TYPE_BUTTON;
  pressed = false;
  delay = 0;
  maxDelay = 30;
  this->addColor(RGB15(0, 0, 31));
  // Son par defaut
  this->setSound(snd_button, (u32)snd_button_size);
}

Button::~Button() {
}

void Button::press() {
  setSelected(true);
  pressed = true;
  nbFrame = 0;
  delay = 0;
  this->playSound();
}

void Button::setMaxDelay(int d) {
  maxDelay = d;
}

int Button::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {
    // Gestion clavier : A
    if(ul_keys.pressed.A && this->getSelected() && this->isSelectable) {
      press();
    } 
    // Gestion clavier : B
    else if(ul_keys.pressed.B && this->getCommand() == BACK) {
      press();
    } else {
      // L'evenement a deja eu lieu
      // L'animation est terminee
      if (pressed && delay >= maxDelay) {
        pressed = false;
        delay = 0;
        return command;
      } else {
        int cmd = Component::dealEvent(scr);
        if (cmd != CMD_NONE) {
          press();
        }
        return CMD_NONE;
      }
    }
  }
  return CMD_NONE;
}

void Button::display(SCREEN scr) {

  if (visible && screen == scr) {

    countFps();

    if (pressed) {
      delay++;
    }

    // Image de fond
    if (imgBg != NULL) {
      if (pressed) {
        if ((nbFrame >= 0 && nbFrame <= 5) || (nbFrame >= 10 && nbFrame <= 15)
            || (nbFrame >= 20 && nbFrame <= 25) || (nbFrame >= 30 && nbFrame
            <= 35) || (nbFrame >= 40 && nbFrame <= 45) || (nbFrame >= 50
            && nbFrame <= 55)) {
          ulDrawImageXY(imgBg, getX(), getY());
        } else {
          drawBackground(this->getColor(0));
        }
      } else {
        ulDrawImageXY(imgBg, getX(), getY());
      }
    }
    // Couleur de fond
    if (hasBgColor) {
      if (pressed) {
        if ((nbFrame > 0 && nbFrame < 5) || (nbFrame > 10 && nbFrame < 15)
            || (nbFrame > 20 && nbFrame < 25) || (nbFrame > 30 && nbFrame < 35)
            || (nbFrame > 40 && nbFrame < 45) || (nbFrame > 50 && nbFrame < 55)) {
          UL_COLOR tmp = bgColor;
          bgColor = this->getColor(0);
          drawBackground();
          bgColor = tmp;
        } else {
          drawBackground();
        }
      } else {
        drawBackground();
      }
    }

    drawBorder();
    drawShadow();
    drawText();

    // Affichage des enfants   
    displayChildren(scr);

    // Dessin de la selection
    drawSelection();
  }
}
