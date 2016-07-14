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
#include "../components/CheckBox.h"
#include "../components/Input.h"
#include "../components/List.h"
#include "../components/Keyboard.h"
#include "../fonts/Ascii.h"
#include "../grids/VocabularyList.h"
#include "MenuDifficulty.h"

using namespace jlpt;

const static char* vocabIndexes[50] = { 
    "A", "I", "U", "E", "O",
    "KA", "KI", "KU", "KE", "KO",
    "SA", "SHI", "SU", "SE", "SO",
    "TA", "CHI", "TSU", "TE", "TO",
    "NA", "NI", "NU", "NE", "NO",
    "HA", "HI", "FU", "HE", "HO",
    "MA", "MI", "MU", "ME", "MO",
    "YA", "YU", "YO", "RA", "RI",
    "RE", "RO", "WA", "CUSTOM1", "CUSTOM2",
    "CUSTOM3", "CUSTOM4", "CUSTOM5", "CUSTOM6", "CUSTOM7"
};

MenuDifficulty::MenuDifficulty(Component* parent) :
  Menu(parent, "title_difficulty.gif") {

  Panel* difficultyPane = new Panel(this, NULL);
  difficultyPane->setSize(246, 110);
  difficultyPane->setLocation(5, 35);
  difficultyPane->setBackgroundColor(RGB15(31, 31, 31), 16);
  difficultyPane->setBorder(RGB15(31, 6, 0), 3, 16);
  this->add(difficultyPane);

  listVocabIndex = new List(this);
  listVocabIndex->setLocation(120, 45);
  for(int i = 0; i < 50; i++) {
    listVocabIndex->addEntry((char*)vocabIndexes[i]);
  }  
  listVocabIndex->setSelectable(true);
  this->add(listVocabIndex);
  
  listDifficulty = new List(this);
  listDifficulty->setLocation(120, 45);
  listDifficulty->addEntry("EASY");
  listDifficulty->addEntry("NORMAL");
  listDifficulty->addEntry("HARD");
  listDifficulty->setSelectable(true);
  listDifficulty->setSelected(true);
  this->add(listDifficulty);

  listSpeed = new List(this);
  listSpeed->setLocation(120, 80);
  listSpeed->addEntry("SLOW");
  listSpeed->addEntry("NORMAL");
  listSpeed->addEntry("FAST");
  listSpeed->setSelectable(true);
  this->add(listSpeed);
  
  checkJoker = new CheckBox(this);
  checkJoker->setLocation(120, 110);
  checkJoker->setSelectable(true);
  this->add(checkJoker);

  goButton = new Button(this, RGB15(31, 25, 0), "GO!!!");
  goButton->setSize(70, 21);
  goButton->setLocation(40, 150);
  goButton->setBorder(RGB15(0, 0, 0), 2, 31);
  goButton->setShadow(RGB15(0, 0, 0), 3);
  goButton->setTextShadow(RGB15(15, 15, 15));
  goButton->setSelectable(true);
  this->add(goButton);

  backButton = new Button(this, RGB15(13,13,13), "BACK");
  backButton->setSize(90, 21);
  backButton->setLocation(130, 150);
  backButton->setCommand(BACK);
  backButton->setBorder(RGB15(0, 0, 0), 2, 31);
  backButton->setShadow(RGB15(0, 0, 0), 3);
  backButton->setTextColor(RGB15(31, 31, 31));
  backButton->setTextShadow(RGB15(0, 0, 0));
  backButton->setSelectable(true);
  backButton->setSound(snd_back, (u32)snd_back_size);
  this->add(backButton);

  Image* backImage = new Image(backButton, "bt_back.gif");
  backImage->setLocation(5, 5);
  backButton->add(backImage);

  fontAscii = new Ascii(SCREEN_DOWN);
}

MenuDifficulty::~MenuDifficulty() {
  delete goButton;
  delete backButton;
  delete fontAscii;
  delete listDifficulty;
  delete listSpeed;
  delete listVocabIndex;
  delete checkJoker;
}

void MenuDifficulty::display(SCREEN scr) {
  Component::display(scr);
  if (visible && screen == scr) {
    fontAscii->displayString("Level:", 1, 6);
    fontAscii->displayString("Speed:", 1, 10);
    if(checkJoker->isVisible()) {
      fontAscii->displayString("Joker:", 1, 14);
    }
  }
}

int MenuDifficulty::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {
    // HAUT
    if (ul_keys.pressed.up) {
      if (listDifficulty->getSelected()) {
        listDifficulty->setSelected(false);
        backButton->setSelected(true);
      } else if (listVocabIndex->getSelected()) {
        listVocabIndex->setSelected(false);
        backButton->setSelected(true);
      } else if (listSpeed->getSelected()) {
        listSpeed->setSelected(false);
        if(listDifficulty->isVisible()) {
          listDifficulty->setSelected(true);
        } else {
          listVocabIndex->setSelected(true);
        }
      } else if (checkJoker->getSelected()) {
        checkJoker->setSelected(false);
        listSpeed->setSelected(true);
      } else if (goButton->getSelected()) {
        goButton->setSelected(false);
        if(checkJoker->isVisible()) {
          checkJoker->setSelected(true);
        } else {
          listSpeed->setSelected(true);
        }
      } else if (backButton->getSelected()) {
        backButton->setSelected(false);
        if(checkJoker->isVisible()) {
          checkJoker->setSelected(true);
        } else {
          listSpeed->setSelected(true);
        }
      } else {
        if(listDifficulty->isVisible()) {
          listDifficulty->setSelected(true);
        } else {
          listVocabIndex->setSelected(true);
        }
      }
    } 
    // BAS
    else if (ul_keys.pressed.down) {
      if (listDifficulty->getSelected()) {
        listDifficulty->setSelected(false);
        listSpeed->setSelected(true);
      } else if (listVocabIndex->getSelected()) {
        listVocabIndex->setSelected(false);
        listSpeed->setSelected(true);
      } else if (listSpeed->getSelected()) {
        listSpeed->setSelected(false);
        if(checkJoker->isVisible()) {
          checkJoker->setSelected(true);
        } else {
          goButton->setSelected(true);
        }
      } else if (checkJoker->getSelected()) {
        checkJoker->setSelected(false);
        goButton->setSelected(true);
      } else if (goButton->getSelected()) {
        goButton->setSelected(false);
        if(listDifficulty->isVisible()) {
          listDifficulty->setSelected(true);
        } else {
          listVocabIndex->setSelected(true);
        }
      } else if (backButton->getSelected()) {
        backButton->setSelected(false);
        if(listDifficulty->isVisible()) {
          listDifficulty->setSelected(true);
        } else {
          listVocabIndex->setSelected(true);
        }
      } else {
        if(listDifficulty->isVisible()) {
          listDifficulty->setSelected(true);
        } else {
          listVocabIndex->setSelected(true);
        }
      }
    } 
    // GAUCHE
    else if (ul_keys.pressed.left) {
      if (goButton->getSelected()) {
        goButton->setSelected(false);
        backButton->setSelected(true);
      } else if (backButton->getSelected()) {
        backButton->setSelected(false);
        goButton->setSelected(true);
      } else if (listDifficulty->isVisible() && listDifficulty->getSelected()) {
        listDifficulty->pressLeft();
      } else if (listVocabIndex->isVisible() && listVocabIndex->getSelected()) {
        if(listVocabIndex->getSelectedEntry() > 0) {
          listVocabIndex->pressLeft();
        }
      } else if (listSpeed->getSelected()) {
        listSpeed->pressLeft();
      } else if(!checkJoker->getSelected() && checkJoker->isVisible()){
        if(listDifficulty->isVisible()) {
          listDifficulty->setSelected(true);
        } else {
          listVocabIndex->setSelected(true);
        }
      }
    } 
    // DROITE
    else if (ul_keys.pressed.right) {
      if (goButton->getSelected()) {
        goButton->setSelected(false);
        backButton->setSelected(true);
      } else if (backButton->getSelected()) {
        backButton->setSelected(false);
        goButton->setSelected(true);
      } else if (listDifficulty->isVisible() && listDifficulty->getSelected()) {
        listDifficulty->pressRight();
      } else if (listVocabIndex->isVisible() && listVocabIndex->getSelected()) {
        if(listVocabIndex->getSelectedEntry() < scoreManager->getLevel(3)) {
          listVocabIndex->pressRight();
        }
      } else if (listSpeed->getSelected()) {
        listSpeed->pressRight();
      } else if(!checkJoker->getSelected() && checkJoker->isVisible()){
        if(listDifficulty->isVisible()) {
          listDifficulty->setSelected(true);
        } else {
          listVocabIndex->setSelected(true);
        }
      }
    } 
    // KEY A
    else if (ul_keys.pressed.A) {
      press();
    } 
    // KEY B
    else if (ul_keys.pressed.B) {
      back();
    } 
    // Stylet
    else if (ul_keys.touch.click) {
      this->setSelectedChildren(false);
      return Component::dealEvent(scr);
    } else {
      return Component::dealEvent(scr);
    }
  }
  return CMD_NONE;
}

void MenuDifficulty::setCommand(int c) {
  goButton->setCommand(c);
}

int MenuDifficulty::getDifficulty() {
  return listDifficulty->getSelectedEntry();
}

int MenuDifficulty::getSpeed() {
  return listSpeed->getSelectedEntry();
}

int MenuDifficulty::getVocabIndex() {
  return listVocabIndex->getSelectedEntry();
}

bool MenuDifficulty::getJoker() {
  return checkJoker->getChecked();
}

void MenuDifficulty::show() {

  // Options par defaut de l'utilisateur
  RECORDS record = scoreManager->getSelectedRecord();
  listSpeed->setSelectedEntry(record.defaultSpeed);
  listDifficulty->setSelectedEntry(record.defaultDifficulty);
  checkJoker->setChecked(record.defaultJoker);
  listVocabIndex->setSelectedEntry(scoreManager->getLevel(3));
  listSpeed->setSelected(false);
  listDifficulty->setSelected(false);
  checkJoker->setSelected(false);
  listVocabIndex->setSelected(false);
  backButton->setSelected(false);
  goButton->setSelected(false);
  
  // Traitement standard
  Component::show();
}

void MenuDifficulty::showVocabIndex() {
  listVocabIndex->show();
  listVocabIndex->setSelected(true);
  listDifficulty->hide();
  listDifficulty->setSelected(false);
}

void MenuDifficulty::hideVocabIndex() {
  listVocabIndex->hide();
  listVocabIndex->setSelected(false);
  listDifficulty->show();
  listDifficulty->setSelected(true);
}

void MenuDifficulty::hideJoker() {
  checkJoker->hide();
  checkJoker->setSelected(false);
}
