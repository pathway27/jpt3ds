#include <ulib/ulib.h>
#include <PA9.h>
#include "snd_select.h"
#include <vector>
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"
#include "../geometry/Dimension.h"
#include "../Tools.h"
#include "../Commands.h"
#include "../components/Component.h"
#include "../scores/ScoreManager.h"
#include "Grid.h"

using namespace jlpt;

Grid::Grid(Component* parent, char* imageName, char* imageKeyName) :
  Component(parent) {
  type = TYPE_GRID;
  this->imageName = imageName;
  this->imageKeyName = imageKeyName;
  imgTiles = NULL;
  imgKey = NULL;
  imgUnknown = NULL;
  selectedItem = new Point(0, 0);
}

Grid::~Grid() {
  delete imageName;
  delete imageKeyName;
  delete imgTiles;
  delete imgKey;
  delete imgUnknown;
  delete selectedItem;
}

void Grid::show() {

  if (imgTiles == NULL) {
    imgTiles = loadImageGIF(imageName, UL_PF_PAL4);
  } else {
    ulRealizeImage(imgTiles);
  }
  if (imgKey == NULL) {
    imgKey = loadImageGIF(imageKeyName, UL_PF_PAL4);
  } else {
    ulRealizeImage(imgKey);
  }
  if (imgUnknown == NULL) {
    imgUnknown = loadImageGIF("unknown.gif", UL_PF_PAL4);
  } else {
    ulRealizeImage(imgUnknown);
  }
  Component::show();
  displayIdeogram(selectedItem->getX(), selectedItem->getY());
}

void Grid::hide() {

  if (imgTiles != NULL) {
    ulUnrealizeImage(imgTiles);
  }
  if (imgKey != NULL) {
    ulUnrealizeImage(imgKey);
  }
  if (imgUnknown != NULL) {
    ulUnrealizeImage(imgUnknown);
  }
  Component::hide();
}

void Grid::drawIdeogram(UL_IMAGE* imgTiles, int i, int j, int x, int y,
  int level) {
  if (j <= level) {
    drawTile(imgTiles, i, j, x, y);
  } else {
    ulDrawImageXY(imgUnknown, x, y);
  }
}

void Grid::displayIdeogram(int i, int j) {
  this->playSoundEx0(snd_select, (u32)snd_select_size);
}

void Grid::displayUnlockMessage(char* sentence) {
  // Reinitialisation du systeme de sprites
  PA_ResetSpriteSysScreen(SCREEN_UP);

  // Reinitialisation des fonds d'ecrans
  PA_ResetBgSysScreen(SCREEN_UP);

  // Initialisation du fond reserve au texte
  PA_Init16cBg(SCREEN_UP, BG_0);

  // Fond d'ecran superieur
  PA_LoadTiledBg(SCREEN_UP, BG_3, bg_top_vocabulary);

  for (unsigned int i = 0; i < strlen(sentence); i+=4) {
    PA_16cText(SCREEN_UP, 25, 60, SCREEN_WIDTH - 25, SCREEN_HEIGHT - 20,
        sentence, BLACK, SIZE_2, i+1);
    PA_WaitForVBL();
  }
  PA_16cText(SCREEN_UP, 25, 60, SCREEN_WIDTH - 25, SCREEN_HEIGHT - 20,
      sentence, BLACK, SIZE_2, strlen(sentence));
}

void Grid::setScoreManager(ScoreManager* s) {
  scoreManager = s;
}
