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
#include "../components/Image.h"
#include "../grids/VocabularyList.h"
#include "MenuLearn.h"

using namespace jlpt;

MenuLearn::MenuLearn(Component* parent, ScoreManager* s) :
  Menu(parent, s) {

  TabbedPanel* tabPane = new TabbedPanel(this, NULL);
  tabPane->setSize(236, 142);
  tabPane->setLocation(10, 10);
  tabPane->loadInactiveTabImage("panel_title.gif", UL_PF_PAL4);
  this->add(tabPane);

  Panel* hiraganaPane = new Panel(tabPane, "Hiragana");
  hiraganaPane->setBackgroundColor(RGB15(31, 31, 31), 16);
  hiraganaPane->setBorder(RGB15(0, 6, 31), 3, 16);
  hiraganaPane->setShadow(RGB15(0, 0, 0), 3);
  hiraganaPane->loadTabImage("panel_title_1.gif", UL_PF_PAL4);
  tabPane->add(hiraganaPane);

  hiraganaGrid = new GridHiragana(hiraganaPane, "kanas.gif", "key_1.gif");
  hiraganaGrid->setScoreManager(s);
  hiraganaGrid->setLocation(30, 20);
  hiraganaGrid->setSize(11*16, 5*16);
  hiraganaPane->add(hiraganaGrid);

  Panel* kataganaPane = new Panel(tabPane, "Katakana");
  kataganaPane->setBackgroundColor(RGB15(31, 31, 31), 16);
  kataganaPane->setBorder(RGB15(6, 12, 0), 3, 16);
  kataganaPane->setShadow(RGB15(0, 0, 0), 3);
  kataganaPane->loadTabImage("panel_title_2.gif", UL_PF_PAL4);
  tabPane->add(kataganaPane);

  katakanaGrid = new GridKatakana(kataganaPane, "kanas.gif", "key_2.gif");
  katakanaGrid->setScoreManager(s);
  katakanaGrid->setLocation(30, 20);
  katakanaGrid->setSize(11*16, 5*16);
  kataganaPane->add(katakanaGrid);

  Panel* kanjiPane = new Panel(tabPane, "Kanji");
  kanjiPane->setBackgroundColor(RGB15(31, 31, 31), 16);
  kanjiPane->setBorder(RGB15(31, 6, 0), 3, 16);
  kanjiPane->setShadow(RGB15(0, 0, 0), 3);
  kanjiPane->loadTabImage("panel_title_3.gif", UL_PF_PAL4);
  tabPane->add(kanjiPane);

  kanjiGrid = new GridKanji(kanjiPane, "kanji.gif", "key_3.gif");
  kanjiGrid->setScoreManager(s);
  kanjiGrid->setLocation(38, 28);
  kanjiGrid->setSize(10*16, 4*16);
  kanjiPane->add(kanjiGrid);

  Panel* vocabularyPane = new Panel(tabPane, "Vocabulary");
  vocabularyPane->setBackgroundColor(RGB15(31, 31, 31), 16);
  vocabularyPane->setBorder(RGB15(25, 19, 0), 3, 16);
  vocabularyPane->setShadow(RGB15(0, 0, 0), 3);
  vocabularyPane->loadTabImage("panel_title_4.gif", UL_PF_PAL4);
  tabPane->add(vocabularyPane);

  vocabList = new VocabularyList(vocabularyPane);
  vocabList->setScoreManager(s);
  vocabList->setLocation(22, 13);
  vocabList->setSize(192, 96);
  vocabularyPane->add(vocabList);

  Button* m_btn_back = new Button(this, RGB15(13,13,13), "BACK");
  m_btn_back->setSize(100, 21);
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

MenuLearn::~MenuLearn() {
  delete hiraganaGrid;
  delete katakanaGrid;
  delete kanjiGrid;
  delete vocabList;
}
