#include <PA9.h>
#include "snd_checkbox.h"
#include <ulib/ulib.h>
#include <vector>
#include "../geometry/Point.h"
#include "../geometry/Dimension.h"
#include "../geometry/Rectangle.h"
#include "../Tools.h"
#include "../Commands.h"
#include "Component.h"
#include "CheckBox.h"

using namespace jlpt;

CheckBox::CheckBox(Component* parent) :
  Component(parent) {
  type = TYPE_CHECKBOX;
  checked = false;
  imgChecked = NULL;
  checkedImageName = "checked.gif";
  this->setBorder(RGB15(0, 0, 0), 1, 31);
  this->setSize(20, 20);
  // Son par defaut
  this->setSound(snd_checkbox, (u32)snd_checkbox_size);
}

CheckBox::~CheckBox() {
  delete imgChecked;
  delete checkedImageName;
}

bool CheckBox::getChecked() {
  return checked;
}

void CheckBox::setChecked(bool c) {
  checked = c;
}

void CheckBox::display(SCREEN scr) {
  Component::display(scr);
  if (visible && screen == scr) {
    if (imgChecked != NULL && checked) {
      ulDrawImageXY(imgChecked, getX(), getY());
    }
    // Dessin de la selection
    drawSelection();
  }
}

int CheckBox::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {
    // Gestion clavier : A
    if(ul_keys.pressed.A && this->getSelected()) {
      press();
      return CHECK;
    } else if (ul_keys.touch.click) {
      if (this->containsStylus()) {
        press();
        return CHECK;
      }
      // Ne contient pas le stylet
      else {
        this->setSelected(false);
      }
    }
  }
  return CMD_NONE;
}

void CheckBox::press() {
  this->setSelected(true);
  if (checked) {
    checked = false;
  } else {
    checked = true;
  }
  this->playSound();
}

void CheckBox::hide() {

  if (imgChecked != NULL) {
    ulUnrealizeImage(imgChecked);
  }
  Component::hide();
}

void CheckBox::show() {

  if (imgChecked == NULL) {
    imgChecked = loadImageGIF(checkedImageName, UL_PF_PAL4);
  } else {
    ulRealizeImage(imgChecked);
  }

  // Traitement standard
  Component::show();
}
