#include <ulib/ulib.h>
#include <PA9.h>
#include <vector>
#include "../../gfx/all_gfx.h"
#include "../Commands.h"
#include "../geometry/Point.h"
#include "../geometry/Dimension.h"
#include "../geometry/Rectangle.h"
#include "../fonts/Ascii.h"
#include "../fonts/Jis.h"
#include "../components/ProgressBar.h"
#include "../components/Component.h"
#include "../components/TextComponent.h"
#include "../Tools.h"
#include "../scores/ScoreManager.h"
#include "../menus/Menu.h"
#include "../components/Panel.h"
#include "../components/TabbedPanel.h"
#include "../grids/Grid.h"
#include "../grids/GridKanji.h"
#include "../grids/GridHiragana.h"
#include "../grids/GridKatakana.h"
#include "../components/Button.h"
#include "../components/Keyboard.h"
#include "../components/KeyboardAscii.h"
#include "../components/Input.h"
#include "../grids/VocabularyList.h"
#include "../files/File.h"
#include "../files/FileReader.h"
#include "Game.h"
#include "GameIdeogram.h"
#include "GameKanji.h"

using namespace jlpt;

GameKanji::GameKanji(Component* parent, ScoreManager* s) :
  GameIdeogram(parent, s) {
  input->setMaxLength(25);
  this->gameId = 2;
  this->maxLevel = 30;
  this->maxX = 29;
  this->maxY = 3;
  
  // EASY MODE
  easyJokerButton->setLocation(100, 25);
  
  easyButtons[0]->setSize(140, 21);
  easyButtons[0]->centerX(55);
  easyButtons[0]->setXOffsetForText(10);
  easyButtons[0]->setYOffsetForText(7);
  
  easyButtons[1]->setSize(140, 21);
  easyButtons[1]->centerX(85);
  easyButtons[1]->setXOffsetForText(10);
  easyButtons[1]->setYOffsetForText(7);
  
  easyButtons[2]->setSize(140, 21);
  easyButtons[2]->centerX(115);
  easyButtons[2]->setXOffsetForText(10);
  easyButtons[2]->setYOffsetForText(7);
  
  // NORMAL MODE
  normalJokerButton->setLocation(100, 25);
  
  normalButtons[0]->setSize(114, 21);
  normalButtons[0]->setLocation(10, 55);
  normalButtons[0]->setXOffsetForText(18);
  normalButtons[0]->setYOffsetForText(7);
  
  normalButtons[1]->setSize(114, 21);
  normalButtons[1]->setLocation(10, 85);
  normalButtons[1]->setXOffsetForText(18);
  normalButtons[1]->setYOffsetForText(7);
  
  normalButtons[2]->setSize(114, 21);
  normalButtons[2]->setLocation(10, 115);
  normalButtons[2]->setXOffsetForText(18);
  normalButtons[2]->setYOffsetForText(7);
  
  normalButtons[3]->setSize(114, 21);
  normalButtons[3]->setLocation(130, 55);
  normalButtons[3]->setXOffsetForText(18);
  normalButtons[3]->setYOffsetForText(7);
  
  normalButtons[4]->setSize(114, 21);
  normalButtons[4]->setLocation(130, 85);
  normalButtons[4]->setXOffsetForText(18);
  normalButtons[4]->setYOffsetForText(7);
  
  normalButtons[5]->setSize(114, 21);
  normalButtons[5]->setLocation(130, 115);
  normalButtons[5]->setXOffsetForText(18);
  normalButtons[5]->setYOffsetForText(7);  
}

GameKanji::~GameKanji() {
  // NOTHING TO DO
}

std::string GameKanji::readSolution(int rndX, int rndY) {
  GAME_KANJI_DATA data;
  std::string filePath = getFilePath("game_kanji.txt", scoreManager);
  FileReader* fileReader = new FileReader(filePath.c_str(), UNICODE);
  fileReader->open("rb");
  if (fileReader->exists()) {
    fileReader->seek((4*rndX + rndY)*sizeof(data));
    fileReader->read(&data, sizeof(data), 1);
    fileReader->close();
    return std::string(fileReader->getAscii(data.meaning, 50));
  }
  return std::string("emu");
}

bool GameKanji::isPaletteOk() {
  return (kanji_Pal[randomX][randomY] != NULL);
}

void* GameKanji::getPalette(int x, int y) {
  return (void*)kanji_Pal[x][y];
}

void* GameKanji::getSprite(int x, int y) {
  return (void*)kanji_Sprite[x][y];
}
