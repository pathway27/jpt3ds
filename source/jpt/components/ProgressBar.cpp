#include <ulib/ulib.h>
#include <PA9.h>
#include <vector>
#include "../../gfx/all_gfx.h"
#include "../geometry/Point.h"
#include "../geometry/Dimension.h"
#include "../geometry/Rectangle.h"
#include "Component.h"
#include "ProgressBar.h"

using namespace jlpt;

ProgressBar::ProgressBar(int max) {

  this->location = new Point(0, 0);
  this->maxValue = max;
  this->currentValue = 0;
  this->nbSprites = 25;
  this->startSpriteNumber = 20;
}

ProgressBar::~ProgressBar() {
  delete location;
}

void ProgressBar::init() {

  PA_LoadSpritePal(SCREEN_UP, PALETTE_6, (void*)progressbar_1_Pal);
  PA_LoadSpritePal(SCREEN_UP, PALETTE_7, (void*)progressbar_2_Pal);
  PA_LoadSpritePal(SCREEN_UP, PALETTE_8, (void*)progressbar_3_Pal);
  PA_LoadSpritePal(SCREEN_UP, PALETTE_9, (void*)progressbar_4_Pal);

  deleteSprites();
  createSprites(true);
}

int ProgressBar::getCurrentValue() {
  return currentValue;
}

void ProgressBar::setMaxValue(int max) {
  maxValue = max;
  reset();
}

void ProgressBar::setLocation(int x, int y) {
  this->location->setLocation(x, y);
}

void ProgressBar::display() {
  deleteSprites();
  createSprites(false);
}

void ProgressBar::createSprites(bool wait) {
  int progress = (currentValue*nbSprites)/maxValue;
  for (int i = 0; i < nbSprites; i++) {
    // Progression remplie
    if (i < progress) {
      if(i == 0) {
        PA_CreateSprite(SCREEN_UP, startSpriteNumber + i, (void*)progressbar_1_Sprite,
            OBJ_SIZE_8X32,COLOR_256, PALETTE_6, location->getX() + i*8, location ->getY());
      } else if(i == (nbSprites - 1)) {
        PA_CreateSprite(SCREEN_UP, startSpriteNumber + i, (void*)progressbar_1_Sprite,
            OBJ_SIZE_8X32,COLOR_256, PALETTE_6, location->getX() + i*8, location ->getY());
        PA_SetSpriteHflip(SCREEN_UP, startSpriteNumber + i, 1);
      } else {
        PA_CreateSprite(SCREEN_UP, startSpriteNumber + i, (void*)progressbar_2_Sprite,
            OBJ_SIZE_8X32,COLOR_256, PALETTE_7, location->getX() + i*8, location ->getY());
      }
    }
    // Progression non remplie
    else {
      if(i == 0) {
        PA_CreateSprite(SCREEN_UP, startSpriteNumber + i, (void*)progressbar_4_Sprite,
            OBJ_SIZE_8X32,COLOR_256, PALETTE_9, location->getX() + i*8 , location ->getY());
        PA_SetSpriteHflip(SCREEN_UP, startSpriteNumber + i, 1);
      } else if(i == (nbSprites - 1)) {
        PA_CreateSprite(SCREEN_UP, startSpriteNumber + i, (void*)progressbar_4_Sprite,
            OBJ_SIZE_8X32,COLOR_256, PALETTE_9, location->getX() + i*8 , location ->getY());
      } else {
        PA_CreateSprite(SCREEN_UP, startSpriteNumber + i, (void*)progressbar_3_Sprite,
            OBJ_SIZE_8X32,COLOR_256, PALETTE_8, location->getX() + i*8 , location ->getY());
      }
    }
  }
}

void ProgressBar::increment() {
  if (currentValue < maxValue) {
    currentValue++;
  }
}

void ProgressBar::reset() {
  currentValue = 0;
}

void ProgressBar::deleteSprites() {
  for (int i = 0; i < nbSprites; i++) {
    PA_DeleteSprite(SCREEN_UP, startSpriteNumber + i);
  }
}
