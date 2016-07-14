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
#include "../components/Button.h"
#include "../grids/VocabularyList.h"
#include "MenuPractice.h"

using namespace jlpt;

MenuPractice::MenuPractice(Component* parent) :
  Menu(parent) {

  Button* m_btn_hiragana = new Button(this, "bt_hira.gif");
  m_btn_hiragana->setSize(40, 40);
  m_btn_hiragana->setLocation(34, 20);
  m_btn_hiragana->setBorder(RGB15(0, 0, 0), 2, 31);
  m_btn_hiragana->setShadow(RGB15(0, 0, 0), 3);
  m_btn_hiragana->setCommand(GAME_HIRA);
  m_btn_hiragana->setSelectable(true);
  m_btn_hiragana->setSelected(true);
  add(m_btn_hiragana);

  Button* m_btn_katakana = new Button(this, "bt_kata.gif");
  m_btn_katakana->setSize(40, 40);
  m_btn_katakana->setLocation(108, 20);
  m_btn_katakana->setBorder(RGB15(0, 0, 0), 2, 31);
  m_btn_katakana->setShadow(RGB15(0, 0, 0), 3);
  m_btn_katakana->setCommand(GAME_KATA);
  m_btn_katakana->setSelectable(true);
  add(m_btn_katakana);

  Button* m_btn_kanji = new Button(this, "bt_kanji.gif");
  m_btn_kanji->setSize(40, 40);
  m_btn_kanji->setLocation(182, 20);
  m_btn_kanji->setBorder(RGB15(0, 0, 0), 2, 31);
  m_btn_kanji->setShadow(RGB15(0, 0, 0), 3);
  m_btn_kanji->setCommand(GAME_KANJI);
  m_btn_kanji->setSelectable(true);
  add(m_btn_kanji);

  Button* m_btn_vocab = new Button(this, "bt_vocab.gif");
  m_btn_vocab->setSize(40, 40);
  m_btn_vocab->setLocation(34, 92);
  m_btn_vocab->setBorder(RGB15(0, 0, 0), 2, 31);
  m_btn_vocab->setShadow(RGB15(0, 0, 0), 3);
  m_btn_vocab->setCommand(GAME_VOCAB);
  m_btn_vocab->setSelectable(true);
  add(m_btn_vocab);

  Button* m_btn_draw = new Button(this, "bt_draw.gif");
  m_btn_draw->setSize(40, 40);
  m_btn_draw->setLocation(108, 92);
  m_btn_draw->setBorder(RGB15(0, 0, 0), 2, 31);
  m_btn_draw->setShadow(RGB15(0, 0, 0), 3);
  m_btn_draw->setCommand(GAME_DRAW);
  m_btn_draw->setSelectable(true);
  add(m_btn_draw);

  Button* m_btn_numbers = new Button(this, "bt_numbers.gif");
  m_btn_numbers->setSize(40, 40);
  m_btn_numbers->setLocation(182, 92);
  m_btn_numbers->setBorder(RGB15(0, 0, 0), 2, 31);
  m_btn_numbers->setShadow(RGB15(0, 0, 0), 3);
  m_btn_numbers->setCommand(GAME_NUMBERS);
  m_btn_numbers->setSelectable(true);
  add(m_btn_numbers);

  Button* m_btn_back = new Button(this, RGB15(13,13,13), "BACK");
  m_btn_back->setSize(100, 21);
  m_btn_back->centerX(160);
  m_btn_back->setCommand(BACK);
  m_btn_back->setBorder(RGB15(0, 0, 0), 2, 31);
  m_btn_back->setShadow(RGB15(0, 0, 0), 3);
  m_btn_back->setTextColor(RGB15(31, 31, 31));
  m_btn_back->setTextShadow(RGB15(0, 0, 0));
  m_btn_back->setSelectable(true);
  m_btn_back->setSound(snd_back, (u32)snd_back_size);
  add(m_btn_back);

  m_title = new Button(this, RGB15(31, 25, 0), "HIRAGANA");
  m_title->setSize(100, 21);
  m_title->centerX(65);
  m_title->setBorder(RGB15(0, 0, 0), 2, 31);
  m_title->setTextShadow(RGB15(15, 15, 15));
  add(m_title);
  
  Component* backImage = new Component(m_btn_back, "bt_back.gif");
  backImage->setLocation(5, 5);
  m_btn_back->add(backImage);
}

MenuPractice::~MenuPractice() {
  delete m_title;
}

int MenuPractice::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {
    if (ul_keys.pressed.left) {
      selectBefore();
    } else if (ul_keys.pressed.right) {
      selectAfter();
    } else if (ul_keys.pressed.up) {
      selectUp();
    } else if (ul_keys.pressed.down) {
      selectDown();
    } else if (ul_keys.pressed.A) {
      press();
    } else if (ul_keys.pressed.B) {
      back();
    } else if (ul_keys.touch.click) {
      this->setSelectedChildren(false);
      int cmd = Component::dealEvent(scr);
      updateTitle();
      return cmd;
    } else {
      int cmd = Component::dealEvent(scr);
      updateTitle();
      return cmd;
    }
  }
  updateTitle();
  return CMD_NONE;
}

void MenuPractice::updateTitle() {
  for (unsigned int i = 0; i < this->getButtons().size(); i++) {
    Button* button = this->getButtons().at(i);
    if (button->getSelected()) {
      switch(button->getCommand()) {
        case GAME_HIRA:
          m_title->setText("HIRAGANA");
          break;
        case GAME_KATA:
          m_title->setText("KATAKANA");
          break;
        case GAME_KANJI:
          m_title->setText("KANJI");
          break;
        case GAME_VOCAB:
          m_title->setText("VOCABULARY");
          break;
        case GAME_DRAW:
          m_title->setText("DRAWING");
          break;
        case GAME_NUMBERS:
          m_title->setText("NUMBERS");
          break;
        default:
          break;
      }
    }
  }  
}

void MenuPractice::selectDown() {
  std::vector<Button*> buttons = getButtons();
  if (buttons.size() > 0) {
    for (unsigned int i = 0; i < buttons.size(); i++) {
      Button* button = buttons.at(i);
      if (button->getSelected()) {
        button->setSelected(false);
        if (i >= 0 && i <= 2) {
          buttons.at(i + 3)->setSelected(true);
        } else {
          buttons.at(6)->setSelected(true);
        }
        return;
      }
    }
  }
}

void MenuPractice::selectUp() {
  std::vector<Button*> buttons = getButtons();
  if (buttons.size() > 0) {
    for (unsigned int i = 0; i < buttons.size(); i++) {
      Button* button = buttons.at(i);
      if (button->getSelected()) {
        if (i >= 3 && i <= 5) {
          button->setSelected(false);
          buttons.at(i - 3)->setSelected(true);
        } else if (i == 6) {
          button->setSelected(false);
          buttons.at(4)->setSelected(true);
        }
        return;
      }
    }
  }
}
