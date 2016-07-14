#include <PA9.h>
#include "snd_list.h"
#include <ulib/ulib.h>
#include <vector>
#include <string>
#include "../geometry/Point.h"
#include "../geometry/Dimension.h"
#include "../geometry/Rectangle.h"
#include "../Commands.h"
#include "Component.h"
#include "TextComponent.h"
#include "Button.h"
#include "List.h"

using namespace jlpt;

List::List(Component* parent) :
  Component(parent) {
  type = TYPE_LIST;
  selectedEntry = -1;

  this->setSize(120, 20);

  Button* buttonLeft = new Button(this, RGB15(31,6,0), "<");
  buttonLeft->setSize(20, 20);
  buttonLeft->setLocation(0, 0);
  buttonLeft->setCommand(LIST_LEFT);
  buttonLeft->setMaxDelay(10);
  buttonLeft->setBorder(RGB15(0, 0, 0), 1, 31);
  buttonLeft->setTextColor(RGB15(31, 31, 31));
  buttonLeft->setTextShadow(RGB15(0, 0, 0));
  this->add(buttonLeft);

  buttonText = new Button(this, RGB15(31,6,0), "-- EMPTY --");
  buttonText->setSize(70, 20);
  buttonText->setLocation(25, 0);
  buttonText->setBorder(RGB15(0, 0, 0), 1, 31);
  buttonText->setTextColor(RGB15(31, 31, 31));
  buttonText->setTextShadow(RGB15(0, 0, 0));
  this->add(buttonText);

  Button* buttonRight = new Button(this, RGB15(31,6,0), ">");
  buttonRight->setSize(20, 20);
  buttonRight->setLocation(100, 0);
  buttonRight->setCommand(LIST_RIGHT);
  buttonRight->setMaxDelay(10);
  buttonRight->setBorder(RGB15(0, 0, 0), 1, 31);
  buttonRight->setTextColor(RGB15(31, 31, 31));
  buttonRight->setTextShadow(RGB15(0, 0, 0));
  this->add(buttonRight);
  
  // Son par defaut
  this->setSound(snd_list, (u32)snd_list_size);
}

List::~List() {
  // NOTHING TO DO
}

void List::addEntry(char* s) {
  entries.push_back(std::string(s));

  if (entries.size() == 1) {
    buttonText->setText(s);
    selectedEntry = 0;
  }
}

void List::display(SCREEN scr) {
  Component::display(scr);
  if (visible && screen == scr) {
    // Dessin de la selection
    drawSelection();
  }
}

int List::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {
    // Gestion clavier : LEFT
    if(ul_keys.pressed.left && this->getSelected()) {
      pressLeft();
    }
    // Gestion clavier : RIGHT
    else if(ul_keys.pressed.right && this->getSelected()) {
      pressRight();
    }
    // Gestion clavier : A
    else if(ul_keys.pressed.A && this->getSelected()) {
      pressRight();
    }
    // Gestion stylet
    else {
      int cmd = Component::dealEvent(scr);
      if (cmd == LIST_LEFT) {
        pressLeft();
      } else if (cmd == LIST_RIGHT) {
        pressRight();
      }
      return cmd;
    }
  }
  return CMD_NONE;
}

void List::pressLeft() {
  this->setSelected(true);
  if (selectedEntry == 0) {
    selectedEntry = entries.size() - 1;
  } else {
    selectedEntry--;
  }
  refreshSelectedEntry();
  this->playSound();
}

void List::pressRight() {
  this->setSelected(true);
  if (selectedEntry == entries.size() - 1 && entries.size() > 0) {
    selectedEntry = 0;
  } else {
    selectedEntry++;
  }
  refreshSelectedEntry();
  this->playSound();
}

void List::setBackgroundColor(UL_COLOR color, int alpha) {
  for (u8 i = 0; i < children.size(); i++) {
    children.at(i)->setBackgroundColor(color, alpha);
  }
}

int List::getSelectedEntry() {
  return selectedEntry;
}

void List::setSelectedEntry(u8 i) {
  selectedEntry = i;
  refreshSelectedEntry();
}

void List::refreshSelectedEntry() {
  buttonText->setText(entries.at(selectedEntry).data());
}
