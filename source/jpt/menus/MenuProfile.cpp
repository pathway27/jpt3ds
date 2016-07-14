#include <PA9.h>
#include "snd_back.h"
#include <ulib/ulib.h>
#include <vector>
#include "../Commands.h"
#include "../geometry/Point.h"
#include "../geometry/Dimension.h"
#include "../geometry/Rectangle.h"
#include "../components/Component.h"
#include "../components/TextComponent.h"
#include "../Tools.h"
#include "../scores/ScoreManager.h"
#include "Menu.h"
#include "../components/Panel.h"
#include "../components/TabbedPanel.h"
#include "../fonts/Jis.h"
#include "../grids/Grid.h"
#include "../grids/GridKanji.h"
#include "../grids/GridHiragana.h"
#include "../grids/GridKatakana.h"
#include "../components/Image.h"
#include "../components/Button.h"
#include "../components/Input.h"
#include "../components/Keyboard.h"
#include "../components/KeyboardAscii.h"
#include "../grids/VocabularyList.h"
#include "MenuProfile.h"

using namespace jlpt;

MenuProfile::MenuProfile(Component* parent) :
  Menu(parent, "title_name.gif") {

  nameInput = new Input(this, "");
  nameInput->setMaxLength(15);
  nameInput->setSize(100, 21);
  nameInput->centerX(36);
  nameInput->setBorder(RGB15(0, 0, 0), 1, 31);
  nameInput->setBackgroundColor(RGB15(31, 31, 31), 16);
  nameInput->setShadow(RGB15(0, 0, 0), 2);
  this->add(nameInput);

  okButton = new Button(this, RGB15(31, 25, 0), "OK");
  okButton->setSize(21, 21);
  okButton->setSelectable(true);
  okButton->setLocation(nameInput->getMaxX() + 10, 36);
  okButton->setCommand(OK);
  okButton->setBorder(RGB15(0, 0, 0), 2, 31);
  okButton->setShadow(RGB15(0, 0, 0), 3);
  okButton->setTextShadow(RGB15(15, 15, 15));
  this->add(okButton);
  
  Button* m_btn_back = new Button(this, RGB15(13,13,13), "BACK");
  m_btn_back->setSelectable(true);
  m_btn_back->setSize(100, 21);
  m_btn_back->centerX(165);
  m_btn_back->setCommand(BACK);
  m_btn_back->setBorder(RGB15(0, 0, 0), 2, 31);
  m_btn_back->setShadow(RGB15(0, 0, 0), 3);
  m_btn_back->setTextColor(RGB15(31, 31, 31));
  m_btn_back->setTextShadow(RGB15(0, 0, 0));
  m_btn_back->setSound(snd_back, (u32)snd_back_size);
  this->add(m_btn_back);

  Image* backImage = new Image(m_btn_back, "bt_back.gif");
  backImage->setLocation(5, 5);
  m_btn_back->add(backImage);  
  
  keyboard = new KeyboardAscii(this, KB_FULL);
  keyboard->centerX(65);
  this->add(keyboard);

}

MenuProfile::~MenuProfile() {
  delete nameInput;
  delete keyboard;
  delete okButton;
}

int MenuProfile::dealOKEvent() {
  if (isValidName()) {
    return OK;
  } else {
    return CMD_NONE;
  }
}

void MenuProfile::updateOKButton() {
  okButton->setVisibility(isValidName());
}

int MenuProfile::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {
    if (ul_keys.pressed.A) {
      return dealOKEvent();
    } else if (ul_keys.pressed.B) {
      back();
    } else {
      int cmd = Component::dealEvent(scr);
      // Bouton back
      if (cmd == BACK) {
        return BACK;
      }
      // Bouton ok
      else if (cmd == OK) {
        return dealOKEvent();
      }
      // Gestion clavier
      else if (cmd == KEY_DEL) {
        nameInput->del();
        updateOKButton();
      } else if (cmd == KEY_ENTER) {
        return dealOKEvent();
      } else if (cmd == KEY_SPACE) {
        nameInput->addChar(' ');
        updateOKButton();
      } else if (cmd >= 32 && cmd <= 126) {
        nameInput->addChar(cmd);
        updateOKButton();
      }
    }
    return CMD_NONE;
  }
  return CMD_NONE;
}

Input* MenuProfile::getInput() {
  return nameInput;
}

bool MenuProfile::isValidName() {
  if (nameInput->size() > 0) {
    return true;
  }
  return false;
}

void MenuProfile::show() {
  Component* back = getComponent(1, TYPE_BUTTON);
  back->setSelected(false);
  Component::show();
  updateOKButton();
}
