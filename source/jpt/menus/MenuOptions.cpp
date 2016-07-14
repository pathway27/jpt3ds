#include <ulib/ulib.h>
#include <PA9.h>
#include "snd_back.h"
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
#include "../grids/VocabularyList.h"
#include "MenuOptions.h"

using namespace jlpt;

MenuOptions::MenuOptions(Component* parent) :
  Menu(parent, "title_options.gif") {

  TabbedPanel* tabPane = new TabbedPanel(this, NULL);
  tabPane->setSize(236, 110);
  tabPane->setLocation(10, 40);
  tabPane->loadInactiveTabImage("panel_title.gif", UL_PF_PAL4);
  this->add(tabPane);

  Panel* gamePane = new Panel(tabPane, "Game");
  gamePane->setBackgroundColor(RGB15(31, 31, 31), 16);
  gamePane->setBorder(RGB15(0, 6, 31), 3, 16);
  gamePane->setShadow(RGB15(0, 0, 0), 3);
  gamePane->loadTabImage("panel_title_1.gif", UL_PF_PAL4);
  tabPane->add(gamePane);

  TextComponent* labelDifficulty = new TextComponent(gamePane, "Difficulty :");
  labelDifficulty->setLocation(10, 10);
  labelDifficulty->setTextShadow(RGB15(31, 31, 31));
  gamePane->add(labelDifficulty);

  listDifficulty = new List(gamePane);
  listDifficulty->setBackgroundColor(RGB15(0, 6, 31), 31);
  listDifficulty->setLocation(100, 10);
  listDifficulty->addEntry("EASY");
  listDifficulty->addEntry("NORMAL");
  listDifficulty->addEntry("HARD");
  listDifficulty->setSelectable(true);
  listDifficulty->setSelected(true);
  gamePane->add(listDifficulty);

  TextComponent* labelSpeed = new TextComponent(gamePane, "Speed :");
  labelSpeed->setLocation(40, 35);
  labelSpeed->setTextShadow(RGB15(31, 31, 31));
  gamePane->add(labelSpeed);

  listSpeed = new List(gamePane);
  listSpeed->setBackgroundColor(RGB15(0, 6, 31), 31);
  listSpeed->setLocation(100, 35);
  listSpeed->addEntry("SLOW");
  listSpeed->addEntry("NORMAL");
  listSpeed->addEntry("FAST");
  listSpeed->setSelectable(true);
  gamePane->add(listSpeed);

  TextComponent* labelJoker = new TextComponent(gamePane, "Joker :");
  labelJoker->setLocation(40, 60);
  labelJoker->setTextShadow(RGB15(31, 31, 31));
  gamePane->add(labelJoker);

  checkJoker = new CheckBox(gamePane);
  checkJoker->setLocation(100, 60);
  checkJoker->setSelectable(true);
  gamePane->add(checkJoker);

  Panel* profilePane = new Panel(tabPane, "Profile");
  profilePane->setBackgroundColor(RGB15(31, 31, 31), 16);
  profilePane->setBorder(RGB15(6, 12, 0), 3, 16);
  profilePane->setShadow(RGB15(0, 0, 0), 3);
  profilePane->loadTabImage("panel_title_2.gif", UL_PF_PAL4);
  tabPane->add(profilePane);

  listLanguage = new List(gamePane);
  listLanguage->setBackgroundColor(RGB15(6, 12, 0), 31);
  listLanguage->setLocation(70, 10);
  listLanguage->addEntry("ENGLISH");
  listLanguage->addEntry("FRENCH");
  listLanguage->setSelectable(true);
  listLanguage->setSelected(true);
  profilePane->add(listLanguage);

  Button* changeName = new Button(profilePane, RGB15(6,12,0), "CHANGE NAME");
  changeName->setSize(90, 21);
  changeName->centerX(35);
  changeName->setCommand(CHANGE_NAME);
  changeName->setBorder(RGB15(0, 0, 0), 1, 31);
  changeName->setTextColor(RGB15(31, 31, 31));
  changeName->setTextShadow(RGB15(0, 0, 0));
  changeName->setSelectable(true);
  changeName->setSelected(false);
  profilePane->add(changeName);

  Button* deleteProfile = new Button(profilePane, RGB15(6,12,0), "DELETE");
  deleteProfile->setSize(90, 21);
  deleteProfile->centerX(60);
  deleteProfile->setCommand(DELETE_PROFILE);
  deleteProfile->setBorder(RGB15(0, 0, 0), 1, 31);
  deleteProfile->setTextColor(RGB15(31, 31, 31));
  deleteProfile->setTextShadow(RGB15(0, 0, 0));
  deleteProfile->setSelectable(true);
  profilePane->add(deleteProfile);

  scorePane = new Panel(tabPane, "Scores");
  scorePane->setBackgroundColor(RGB15(31, 31, 31), 16);
  scorePane->setBorder(RGB15(31, 6, 0), 3, 16);
  scorePane->setShadow(RGB15(0, 0, 0), 3);
  scorePane->loadTabImage("panel_title_3.gif", UL_PF_PAL4);
  tabPane->add(scorePane);

  listScore = new List(scorePane);
  listScore->setBackgroundColor(RGB15(31, 6, 0), 31);
  listScore->centerX(15);
  listScore->addEntry("HIRAGANA");
  listScore->addEntry("KATAKANA");
  listScore->addEntry("KANJI");
  listScore->addEntry("VOCABULARY");
  listScore->addEntry("DRAWING");
  listScore->addEntry("NUMBERS");
  listScore->setSelectable(true);
  listScore->setSelected(true);
  scorePane->add(listScore);

  Button* resetScore = new Button(scorePane, RGB15(31,6,0), "RESET");
  resetScore->setSize(70, 21);
  resetScore->setLocation(35, 55);
  resetScore->setCommand(RESET_CURRENT_SCORE);
  resetScore->setBorder(RGB15(0, 0, 0), 1, 31);
  resetScore->setTextColor(RGB15(31, 31, 31));
  resetScore->setTextShadow(RGB15(0, 0, 0));
  resetScore->setSelectable(true);
  scorePane->add(resetScore);

  Button* resetAllScore = new Button(scorePane, RGB15(31,6,0), "RESET ALL");
  resetAllScore->setSize(80, 21);
  resetAllScore->setLocation(125, 55);
  resetAllScore->setCommand(RESET_SCORE);
  resetAllScore->setBorder(RGB15(0, 0, 0), 1, 31);
  resetAllScore->setTextColor(RGB15(31, 31, 31));
  resetAllScore->setTextShadow(RGB15(0, 0, 0));
  resetAllScore->setSelectable(true);
  scorePane->add(resetAllScore);

  Button* m_btn_back = new Button(this, RGB15(13,13,13), "BACK");
  m_btn_back->setSize(90, 21);
  m_btn_back->centerX(160);
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
}

MenuOptions::~MenuOptions() {
  delete listDifficulty;
  delete listSpeed;
  delete listScore;
  delete checkJoker;
  delete scorePane;
}

void MenuOptions::show() {
  // Recuperation des parametres du joueur
  RECORDS record = scoreManager->getSelectedRecord();
  listDifficulty->setSelectedEntry(record.defaultDifficulty);
  listSpeed->setSelectedEntry(record.defaultSpeed);
  listLanguage->setSelectedEntry(record.language-1);
  checkJoker->setChecked(record.defaultJoker);

  // Traitement standard
  Component::show();

  if (scorePane->isVisible()) {
    displayScores(0);
  }
}

int MenuOptions::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {
    TabbedPanel* tabPane = (TabbedPanel*)this->getComponent(0, TYPE_TABPANE);
    int paneIndex = tabPane->getVisiblePanelIndex();

    // Gestion clavier : A
    if (ul_keys.pressed.A) {
      Component::dealEvent(scr);
      if (paneIndex == 2) {
        if (listScore->getSelected()) {
          displayScores(listScore->getSelectedEntry());
        }
      }
    }
    // Gestion clavier : LEFT
    else if (ul_keys.pressed.left) {
      // Onglet Profile
      if (paneIndex == 1) {
        if (listLanguage->getSelected()) {
          listLanguage->pressLeft();
        }
      }
      // Onglet Scores
      else if (paneIndex == 2) {
        if (listScore->getSelected()) {
          listScore->pressLeft();
          displayScores(listScore->getSelectedEntry());
        } else {
          tabPane->getVisiblePanel()->selectBefore();
        }
      } else {
        Component::dealEvent(scr);
      }
    }
    // Gestion clavier : RIGHT
    else if (ul_keys.pressed.right) {
      // Onglet Profile
      if (paneIndex == 1) {
        if (listLanguage->getSelected()) {
          listLanguage->pressRight();
        }
      }
      // Onglet Scores
      else if (paneIndex == 2) {
        if (listScore->getSelected()) {
          listScore->pressRight();
          displayScores(listScore->getSelectedEntry());
        } else {
          tabPane->getVisiblePanel()->selectAfter();
        }
      } else {
        Component::dealEvent(scr);
      }
    }
    // Gestion clavier : UP
    else if (ul_keys.pressed.up) {
      tabPane->getVisiblePanel()->selectBefore();
    }
    // Gestion clavier : DOWN
    else if (ul_keys.pressed.down) {
      tabPane->getVisiblePanel()->selectAfter();
    }
    // Autres evenements
    else {
      int cmd = Component::dealEvent(scr);
      if (cmd == BACK) {
        saveOptions();
      } else if (cmd == DELETE_PROFILE) {
        scoreManager->deleteProfile();
      } else if (cmd == RESET_SCORE) {
        scoreManager->reset();
        displayScores(listScore->getSelectedEntry());
      } else if (cmd == RESET_CURRENT_SCORE) {
        scoreManager->resetScore(listScore->getSelectedEntry());
        displayScores(listScore->getSelectedEntry());
      } else if ((cmd == LIST_LEFT || cmd == LIST_RIGHT)
          && scorePane->isVisible()) {
        displayScores(listScore->getSelectedEntry());
      }
      return cmd;
    }
  }
  return CMD_NONE;
}

void MenuOptions::saveOptions() {
  scoreManager->setDefaultDifficulty(listDifficulty->getSelectedEntry());
  scoreManager->setDefaultSpeed(listSpeed->getSelectedEntry());
  scoreManager->setDefaultJoker(checkJoker->getChecked());
  // 1 = English, 2 = French
  scoreManager->setLanguage(listLanguage->getSelectedEntry()+1);
  scoreManager->writeProfiles();
}

void MenuOptions::displayScores(int gameIndex) {
  if (scoreManager == NULL) {
    return;
  }
  // Reinitialisation du systeme de sprites
  PA_ResetSpriteSysScreen(SCREEN_UP);

  // Reinitialisation des fonds d'ecrans
  PA_ResetBgSysScreen(SCREEN_UP);

  // Initialisation du fond reserve au texte
  PA_Init16cBg(SCREEN_UP, BG_0);

  // Fond d'ecran superieur
  PA_LoadTiledBg(SCREEN_UP, BG_3, bg_top_scores);

  RECORDS record = scoreManager->getSelectedRecord();
  char txt[25];

  sprintf(txt, "Level reached : %s", scoreManager->getGameLevel(gameIndex));
  PA_16cText(SCREEN_UP, 25, 50, SCREEN_WIDTH, SCREEN_HEIGHT, txt, BLACK,
      SIZE_2, 35);

  sprintf(txt, "Games played : %d", record.nbGames[gameIndex]);
  PA_16cText(SCREEN_UP, 25, 65, SCREEN_WIDTH, SCREEN_HEIGHT, txt, BLACK,
      SIZE_2, 25);

  sprintf(txt, "Perfects : %d", record.perfects[gameIndex]);
  PA_16cText(SCREEN_UP, 25, 80, SCREEN_WIDTH, SCREEN_HEIGHT, txt, BLACK,
      SIZE_2, 25);

  sprintf(txt, "Good answers : %d", record.goodAnswers[gameIndex]);
  PA_16cText(SCREEN_UP, 25, 95, SCREEN_WIDTH, SCREEN_HEIGHT, txt, BLACK,
      SIZE_2, 25);

  sprintf(txt, "Bad answers : %d", record.badAnswers[gameIndex]);
  PA_16cText(SCREEN_UP, 25, 110, SCREEN_WIDTH, SCREEN_HEIGHT, txt, BLACK,
      SIZE_2, 25);

  sprintf(txt, "Jokers used : %d", record.nbPassed[gameIndex]);
  PA_16cText(SCREEN_UP, 25, 125, SCREEN_WIDTH, SCREEN_HEIGHT, txt, BLACK,
      SIZE_2, 25);

  sprintf(txt, "Games unfinished : %d", record.nbEndOfTime[gameIndex]);
  PA_16cText(SCREEN_UP, 25, 140, SCREEN_WIDTH, SCREEN_HEIGHT, txt, BLACK,
      SIZE_2, 25);

  sprintf(txt, "Games aborted : %d", record.nbAbortions[gameIndex]);
  PA_16cText(SCREEN_UP, 25, 155, SCREEN_WIDTH, SCREEN_HEIGHT, txt, BLACK,
      SIZE_2, 25);
}
