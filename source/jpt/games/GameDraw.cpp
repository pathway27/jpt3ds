#include <PA9.h>
#include "snd_back.h"
#include <ulib/ulib.h>
#include <vector>
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"
#include "../geometry/Dimension.h"
#include "../fonts/Ascii.h"
#include "../components/Component.h"
#include "../components/ProgressBar.h"
#include "../data/Stroke.h"
#include "../data/Gesture.h"
#include "../components/DrawComponent.h"
#include "../scores/ScoreManager.h"
#include "../Tools.h"
#include "../Commands.h"
#include "../components/TextComponent.h"
#include "../components/Panel.h"
#include "../components/Button.h"
#include "../components/Image.h"
#include "Game.h"
#include "GameDraw.h"

using namespace jlpt;

GameDraw::GameDraw(Component* parent, ScoreManager* s) :
  Game(parent, s) {
  
  Button* backButton = (Button*)getComponent(0, TYPE_BUTTON);
  backButton->setSize(64, 18);
  backButton->setLocation(185, 100);
  backButton->setXOffsetForText(10);
  backButton->setYOffsetForText(5);
  
  Panel* panelPlay = new Panel(this);
  panelPlay->setBackgroundColor(RGB15(31, 31, 31), 28);
  panelPlay->setSize(80, 90);
  panelPlay->setLocation(177, 0);
  this->add(panelPlay);

  Button* btnClear = new Button(this, RGB15(31, 25, 0), "CLEAR");
  btnClear->setCommand(CLEAR);
  btnClear->setMaxDelay(5);
  btnClear->setSize(64, 18);
  btnClear->setLocation(185, 7);
  btnClear->setBorder(RGB15(0, 0, 0), 2, 31);
  btnClear->setTextShadow(RGB15(15, 15, 15));
  btnClear->setYOffsetForText(5);
  panelPlay->add(btnClear);

  Button* btnCompare = new Button(this, RGB15(31, 25, 0), "COMPARE");
  btnCompare->setCommand(COMPARE);
  btnCompare->setMaxDelay(5);
  btnCompare->setSize(64, 18);
  btnCompare->setLocation(185, 30);
  btnCompare->setBorder(RGB15(0, 0, 0), 2, 31);
  btnCompare->setYOffsetForText(5);
  btnCompare->setTextShadow(RGB15(15, 15, 15));
  panelPlay->add(btnCompare);

  Button* btnLeft = new Button(this, RGB15(31, 25, 0), "<");
  btnLeft->setCommand(LIST_LEFT);
  btnLeft->setMaxDelay(5);
  btnLeft->setSize(21, 18);
  btnLeft->setLocation(185, 53);
  btnLeft->setBorder(RGB15(0, 0, 0), 2, 31);
  btnLeft->setYOffsetForText(5);
  btnLeft->setTextShadow(RGB15(15, 15, 15));
  panelPlay->add(btnLeft);

  Button* btnRight = new Button(this, RGB15(31, 25, 0), ">");
  btnRight->setCommand(LIST_RIGHT);
  btnRight->setMaxDelay(5);
  btnRight->setSize(21, 18);
  btnRight->setLocation(228, 53);
  btnRight->setBorder(RGB15(0, 0, 0), 2, 31);
  btnRight->setYOffsetForText(5);
  btnRight->setTextShadow(RGB15(15, 15, 15));
  panelPlay->add(btnRight);

  Panel* panelAdmin = new Panel(this);
  panelAdmin->setBackgroundColor(RGB15(31, 31, 31), 28);
  panelAdmin->setSize(80, 51);
  panelAdmin->setLocation(177, 141);
  this->add(panelAdmin);

  Button* btnSave = new Button(this, RGB15(31, 25, 0), "APPEND");
  btnSave->setCommand(APPEND);
  btnSave->setMaxDelay(5);
  btnSave->setSize(64, 18);
  btnSave->setLocation(185, 146);
  btnSave->setBorder(RGB15(0, 0, 0), 2, 31);
  btnSave->setYOffsetForText(5);
  btnSave->setTextShadow(RGB15(15, 15, 15));
  panelAdmin->add(btnSave);

  Button* btnReplace = new Button(this, RGB15(31, 25, 0), "REPLACE");
  btnReplace->setCommand(REPLACE);
  btnReplace->setMaxDelay(5);
  btnReplace->setSize(64, 18);
  btnReplace->setLocation(185, 169);
  btnReplace->setBorder(RGB15(0, 0, 0), 2, 31);
  btnReplace->setYOffsetForText(5);
  btnReplace->setTextShadow(RGB15(15, 15, 15));
  panelAdmin->add(btnReplace);
    
  dc = new DrawComponent(this);
  dc->setSize(150, 150);
  dc->setLocation(11, 21);
  dc->setBorder(RGB15(0, 0, 0), -2, 31);
  dc->setBackgroundColor(RGB15(31, 31, 31), 28);
  this->add(dc);
}

GameDraw::~GameDraw() {
}

int GameDraw::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {
    if (ul_keys.pressed.left) {
      dc->left(1);
    } else if (ul_keys.pressed.right) {
      dc->right(1);
    } else if (ul_keys.pressed.L) {
      dc->left(10);
    } else if (ul_keys.pressed.R) {
      dc->right(10);
    } 
    else {
      int cmd = Component::dealEvent(scr);
      if (cmd == CLEAR) {
        dc->clear();
      } else if (cmd == COMPARE) {
        dc->normalize();
        dc->compare();
      } else if (cmd == APPEND) {
        dc->normalize();
        dc->memorize();        
        dc->append();
      } else if (cmd == REPLACE) {
        dc->normalize();
        dc->memorize();
        dc->replace();
      } else if (cmd == LIST_LEFT) {
        dc->left(1);
      } else if (cmd == LIST_RIGHT) {
        dc->right(1);
      } else {
        return cmd;
      }
    }
  }
  return CMD_NONE;
}
