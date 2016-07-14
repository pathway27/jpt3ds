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
#include "../grids/GridHiragana.h"
#include "../grids/GridKatakana.h"
#include "../components/Button.h"
#include "../components/Image.h"
#include "MenuMain.h"

using namespace jlpt;

MenuMain::MenuMain(Component* parent) :
  Menu(parent) {

  Button* m_btn_learn = new Button(this, RGB15(31, 25, 0), "LEARN");
  m_btn_learn->setSize(100, 21);
  m_btn_learn->centerX(25);
  m_btn_learn->setCommand(LEARN);
  m_btn_learn->setBorder(RGB15(0, 0, 0), 2, 31);
  m_btn_learn->setShadow(RGB15(0, 0, 0), 3);
  m_btn_learn->setTextShadow(RGB15(15, 15, 15));
  m_btn_learn->setSelectable(true);
  m_btn_learn->setSelected(true);
  add(m_btn_learn);

  Button* m_btn_practice = new Button(this, RGB15(31, 25, 0), "PRACTICE");
  m_btn_practice->setSize(100, 21);
  m_btn_practice->centerX(65);
  m_btn_practice->setCommand(PRACTICE);
  m_btn_practice->setBorder(RGB15(0, 0, 0), 2, 31);
  m_btn_practice->setShadow(RGB15(0, 0, 0), 3);
  m_btn_practice->setTextShadow(RGB15(15, 15, 15));
  m_btn_practice->setSelectable(true);
  add(m_btn_practice);

  Button* m_btn_options = new Button(this, RGB15(31, 25, 0), "OPTIONS");
  m_btn_options->setSize(100, 21);
  m_btn_options->centerX(105);
  m_btn_options->setCommand(OPTIONS);
  m_btn_options->setBorder(RGB15(0, 0, 0), 2, 31);
  m_btn_options->setShadow(RGB15(0, 0, 0), 3);
  m_btn_options->setTextShadow(RGB15(15, 15, 15));
  m_btn_options->setSelectable(true);
  add(m_btn_options);

  Button* m_btn_back = new Button(this, RGB15(13,13,13), "BACK");
  m_btn_back->setSize(100, 21);
  m_btn_back->centerX(145);
  m_btn_back->setCommand(BACK);
  m_btn_back->setBorder(RGB15(0, 0, 0), 2, 31);
  m_btn_back->setShadow(RGB15(0, 0, 0), 3);
  m_btn_back->setTextColor(RGB15(31, 31, 31));
  m_btn_back->setTextShadow(RGB15(0, 0, 0));
  m_btn_back->setSelectable(true);
  m_btn_back->setSound(snd_back, (u32)snd_back_size);
  add(m_btn_back);

  Image* backImage = new Image(m_btn_back, "bt_back.gif");
  backImage->setLocation(5, 5);
  m_btn_back->add(backImage);
}

MenuMain::~MenuMain() {
  // NOTHING TO DO
}

int MenuMain::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {
    if (ul_keys.pressed.up) {
      selectBefore();
    } else if (ul_keys.pressed.down) {
      selectAfter();
    } else if (ul_keys.pressed.A) {
      press();
    } else if (ul_keys.pressed.B) {
      back();
    } else if (ul_keys.touch.click) {
      this->setSelectedChildren(false);
      return Component::dealEvent(scr);
    } else {
      return Component::dealEvent(scr);
    }
  }
  return CMD_NONE;
}
