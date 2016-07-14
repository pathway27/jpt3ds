#include <ulib/ulib.h>
#include <vector>
#include "../geometry/Point.h"
#include "../geometry/Dimension.h"
#include "../geometry/Rectangle.h"
#include "../components/Component.h"
#include "../components/TextComponent.h"
#include "../components/Button.h"
#include "../components/CheckBox.h"
#include "../components/List.h"
#include "../Commands.h"
#include "../components/Panel.h"
#include "../Tools.h"
#include "../scores/ScoreManager.h"
#include "Menu.h"

using namespace jlpt;

Menu::Menu(Component* parent) :
  Component(parent) {
  init();
}

Menu::Menu(Component* parent, ScoreManager* s) :
  Component(parent) {
  init();
  this->scoreManager = s;
}

Menu::Menu(Component* parent, char* imageName) :
  Component(parent) {
  init();
  Component* component = new Component(parent, imageName);
  component->setLocation(16, 16);
  add(component);
}

Menu::~Menu() {
  delete scoreManager;
}

void Menu::init() {
  type = TYPE_MENU;
  scoreManager = NULL;
  Panel* panel = new Panel(this);
  add(panel);
}

void Menu::press() {
  for (unsigned int i = 0; i < children.size(); i++) {
    Component* component = children.at(i);
    if (component != NULL && component->getSelected()) {
      if (component->getType() == TYPE_BUTTON) {
        ((Button*)component)->press();
      } else if(component->getType() == TYPE_CHECKBOX) {
        ((CheckBox*)component)->press();
      } else if(component->getType() == TYPE_LIST) {
        ((List*)component)->pressRight();
      }
    }
  }
}

void Menu::back() {
  for (unsigned int i = 0; i < children.size(); i++) {
    Component* component = children.at(i);
    if (component->getSelectable()) {
      int cmd = component->getCommand();
      if (cmd == BACK) {
        component->press();
      } else {
        component->setSelected(false);
      }
    }
  }
}

std::vector<Button*> Menu::getButtons() {
  std::vector<Button*> buttons;
  for (unsigned int i = 0; i < children.size(); i++) {
    Component* component = children.at(i);
    if (component != NULL && component->getType() == TYPE_BUTTON) {
      buttons.push_back((Button*)component);
    }
  }
  return buttons;
}

void Menu::selectBefore() {
  std::vector<Button*> buttons = getButtons();
  if (buttons.size() > 0) {
    for (unsigned int i = 0; i < buttons.size(); i++) {
      Button* button = buttons.at(i);
      if (button->getSelected()) {
        button->setSelected(false);
        if (i == 0) {
          buttons.at(buttons.size() - 1)->setSelected(true);
        } else {
          buttons.at(i-1)->setSelected(true);
        }
        return;
      }
    }
  }

  selectFirst();
}

void Menu::selectAfter() {

  for (unsigned int i = 1; i < children.size(); i++) {
    Component* component = children.at(i);
    if (component != NULL && component->getSelected() && component->getType()
        == TYPE_BUTTON) {
      component->setSelected(false);
      if (i == children.size() - 1) {
        selectFirst();
      } else {
        children.at(i+1)->setSelected(true);
      }
      return;
    }
  }
  // Composant selectionne non trouve : on selectionne le 1er par defaut
  selectFirst();
}

void Menu::selectFirst() {
  for (unsigned int i = 0; i < children.size(); i++) {
    Component* component = children.at(i);
    if (component != NULL && component->getType() == TYPE_BUTTON) {
      component->setSelected(true);
      return;
    }
  }
}

void Menu::setScoreManager(ScoreManager* s) {
  scoreManager = s;
}
