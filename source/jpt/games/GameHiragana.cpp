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
#include "GameHiragana.h"

using namespace jlpt;

GameHiragana::GameHiragana(Component* parent, ScoreManager* s) :
  GameIdeogram(parent, s) {
  this->gameId = 0;
  this->maxLevel = 16;
  this->maxX = 15;
  this->maxY = 4;
}

GameHiragana::~GameHiragana() {
  // NOTHING TO DO
}

std::string GameHiragana::readSolution(int rndX, int rndY) {
  KANA_DATA data;
  std::string filePath = getFilePath("hiragana.txt", scoreManager);
  FileReader* fileReader = new FileReader(filePath.c_str(), UNICODE);
  fileReader->open("rb");
  if (fileReader->exists()) {
    fileReader->seek((5*rndX + rndY)*sizeof(data));
    fileReader->read(&data, sizeof(data), 1);
    fileReader->close();
    return std::string(fileReader->getAscii(data.syllabus, 10));
  }
  return std::string("emu");
}

bool GameHiragana::isPaletteOk() {
  return (hiragana_Pal[randomX][randomY] != NULL);  
}

void* GameHiragana::getPalette(int x, int y) {
  return (void*)hiragana_Pal[x][y];
}

void* GameHiragana::getSprite(int x, int y) {
  return (void*)hiragana_Sprite[x][y];
}
