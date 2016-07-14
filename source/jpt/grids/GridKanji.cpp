#include <ulib/ulib.h>
#include <PA9.h>
#include <vector>
#include "../../gfx/all_gfx.h"
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"
#include "../geometry/Dimension.h"
#include "../Tools.h"
#include "../files/File.h"
#include "../files/FileReader.h"
#include "../Commands.h"
#include "../components/Component.h"
#include "../fonts/Jis.h"
#include "../scores/ScoreManager.h"
#include "Grid.h"
#include "GridKanji.h"

using namespace jlpt;

GridKanji::GridKanji(Component* parent, char* imageName, char* imageKeyName) :
  Grid(parent, imageName, imageKeyName) {
  keyboardMode = KB_KANJI_LVL4_1;
}

int GridKanji::dealEvent(SCREEN scr) {
  if (visible) {
    if (ul_keys.pressed.left) {
      int i = selectedItem->getX();
      if (i == 0) {
        selectedItem->setX(9);
      } else {
        selectedItem->setX(i-1);
      }
      displayIdeogram(selectedItem->getX(), selectedItem->getY());
    } else if (ul_keys.pressed.right) {
      int i = selectedItem->getX();
      if (i == 9) {
        selectedItem->setX(0);
      } else {
        selectedItem->setX(i+1);
      }
      displayIdeogram(selectedItem->getX(), selectedItem->getY());
    } else if (ul_keys.pressed.up) {
      int i = selectedItem->getY();
      if (i == 0) {
        selectedItem->setY(3);
      } else {
        selectedItem->setY(i-1);
      }
      displayIdeogram(selectedItem->getX(), selectedItem->getY());
    } else if (ul_keys.pressed.down) {
      int i = selectedItem->getY();
      if (i == 3) {
        selectedItem->setY(0);
      } else {
        selectedItem->setY(i+1);
      }
      displayIdeogram(selectedItem->getX(), selectedItem->getY());
    } else if (ul_keys.pressed.X || ul_keys.pressed.Y || ul_keys.pressed.A) {
      if (keyboardMode == KB_KANJI_LVL4_1) {
        keyboardMode = KB_KANJI_LVL4_2;
      } else if (keyboardMode == KB_KANJI_LVL4_2) {
        keyboardMode = KB_KANJI_LVL4_3;
      } else {
        keyboardMode = KB_KANJI_LVL4_1;
      }
      displayIdeogram(selectedItem->getX(), selectedItem->getY());
    }
    // Gestion stylet
    else if (ul_keys.touch.click) {
      Rectangle* rect = getBounds();
      if (rect->contains(ul_keys.touch.x, ul_keys.touch.y)) {
        int i = (ul_keys.touch.x - getX() - 1) / 16;
        int j = (ul_keys.touch.y - getY() - 1) / 16;
        selectedItem->setLocation(i, j);
        displayIdeogram(i, j);
      }
      // Gestion des modes
      else {
        int x0 = getMaxX() + 4;
        int y0 = getY();
        Rectangle* rectMode = new Rectangle(x0, y0, 16, 16);

        if (rectMode->contains(ul_keys.touch.x, ul_keys.touch.y)) {
          keyboardMode = KB_KANJI_LVL4_1;
          displayIdeogram(selectedItem->getX(), selectedItem->getY());
          delete rectMode;
          return CMD_NONE;
        }

        rectMode->setRect(x0, y0 + 24, 16, 16);

        if (rectMode->contains(ul_keys.touch.x, ul_keys.touch.y)) {
          keyboardMode = KB_KANJI_LVL4_2;
          displayIdeogram(selectedItem->getX(), selectedItem->getY());
          delete rectMode;
          return CMD_NONE;
        }

        rectMode->setRect(x0, y0 + 48, 16, 16);

        if (rectMode->contains(ul_keys.touch.x, ul_keys.touch.y)) {
          keyboardMode = KB_KANJI_LVL4_3;
          displayIdeogram(selectedItem->getX(), selectedItem->getY());
          delete rectMode;
          return CMD_NONE;
        }
        delete rectMode;
      }
    }
  }

  return CMD_NONE;
}

void GridKanji::displayIdeogram(int i, int j) {

  if (keyboardMode == KB_KANJI_LVL4_2) {
    i += 10;
  } else if (keyboardMode == KB_KANJI_LVL4_3) {
    i += 20;
  }
  int level = scoreManager->getSelectedRecord().level[2];
  
  // Niveau pas assez grand  
  if (i > level) {
    displayUnlockMessage("To unlock this kanji ideogram, please go to the game section and choose 'KANJI'.\n\n You need to make a perfect at this game to unlock the next column.\n\nMaximum level is Grand Master (29 perfects).");
  }
  // Affichage du caractere selectionne
  else if (kanji_Sprite[i][j] != NULL && i <= level) {

    // Reinitialisation du systeme de sprites
    PA_ResetSpriteSysScreen(SCREEN_UP);

    // Reinitialisation des fonds d'ecrans
    PA_ResetBgSysScreen(SCREEN_UP);

    // Initialisation du fond reserve au texte
    PA_Init16cBg(SCREEN_UP, BG_0);

    // Fond d'ecran superieur
    PA_LoadTiledBg(SCREEN_UP, BG_3, bg_top_syllabus);

    // Fond pour ecrire avec les kanas
    Jis jis(SCREEN_UP, BG_2);

    PA_LoadSpritePal(SCREEN_UP, PALETTE_0, (void*)kanji_Pal[i][j]);
    PA_CreateSprite(SCREEN_UP, SPRITE_0, (void*)kanji_Sprite[i][j], 
    OBJ_SIZE_64X64,COLOR_256, PALETTE_0, 21 , 53);
    
    // Lecture du fichier des definitions
    KANJI_DATA data;
    std::string filePath = getFilePath("kanji.txt", scoreManager);
    FileReader* fileReader = new FileReader(filePath.c_str(), UNICODE);
    fileReader->open("rb");
    fileReader->seek((i*4 + j)*sizeof(data));
    fileReader->read(&data, sizeof(data), 1);

    const u16* kunYomi = fileReader->getKana(data.kunYomi, 30);
    if(!isEmpty(kunYomi)) {
      PA_16cText(SCREEN_UP,95,46, SCREEN_WIDTH, SCREEN_HEIGHT, "Kun yomi : ", BLACK, SIZE_2, 10);
      jis.displayJapaneseString(kunYomi,12,7);
    }

    const u16* onYomi = fileReader->getKana(data.onYomi, 30);
    if(!isEmpty(onYomi)) {
      PA_16cText(SCREEN_UP,95,78, SCREEN_WIDTH, SCREEN_HEIGHT, "On yomi : ", BLACK, SIZE_2, 10);
      jis.displayJapaneseString(onYomi,12,11);
    }

    const char* meaning = fileReader->getAscii(data.meaning, 50);
    if(!isEmpty(meaning)) {
      char mean[60];
      sprintf(mean, "Meaning : %s", meaning);
      PA_16cText(SCREEN_UP,95,112, SCREEN_WIDTH - 20, SCREEN_HEIGHT, mean, BLACK, SIZE_2, 40);
    }
    fileReader->close();
  }
  Grid::displayIdeogram(i, j);
}

void GridKanji::drawIdeogram(UL_IMAGE* imgTiles, int i, int j, int x, int y,
  int level) {
  // 1ere page de kanji
  if (keyboardMode == KB_KANJI_LVL4_1) {
    if (i <= level) {
      drawTile(imgTiles, i, j, x, y);
    } else {
      ulDrawImageXY(imgUnknown, x, y);
    }
  }
  // 2eme page de kanji
  else if (keyboardMode == KB_KANJI_LVL4_2) {
    if ((i+10) <= level) {
      drawTile(imgTiles, i, j, x, y);
    } else {
      ulDrawImageXY(imgUnknown, x, y);
    }
  }
  // 3eme page de kanji
  else if (keyboardMode == KB_KANJI_LVL4_3) {
    if ((i+20) <= level) {
      if (j != 11) {
        drawTile(imgTiles, i, j, x, y);
      }
    } else {
      ulDrawImageXY(imgUnknown, x, y);
    }
  }
}

void GridKanji::display(SCREEN scr) {
  Component::display(scr);
  if (visible && screen == scr) {

    if (imgTiles == NULL) {
      show();
    } else {
      int x = getX();
      int y = getY();

      int jOffset = 0;
      if (keyboardMode == KB_KANJI_LVL4_2) {
        jOffset = 4;
      } else if (keyboardMode == KB_KANJI_LVL4_3) {
        jOffset = 8;
      }
      int level = scoreManager->getSelectedRecord().level[2];

      // Dessin des caracteres
      for (int i = 0; i < 10; i++) {
        for (int j = 0 + jOffset; j < (4 + jOffset); j++) {
          ulDrawImageXY(imgKey, x, y);
          drawIdeogram(imgTiles, i, j, x, y, level);

          y += FONT_TILE_16x16;
        }
        y = getY();
        x += FONT_TILE_16x16;
      }

      // Dessin de la selection
      int selectedX = getX() + 16*selectedItem->getX();
      int selectedY = getY() + 16*selectedItem->getY();
      drawAnimation_1(selectedX, selectedY, selectedX+16, selectedY+16, RGB15(
          31, 31, 0));

      // Dessin des options : 1 : 2 : 3
      int x0 = getX() + getWidth() + 4;
      int x1 = x0 + 16;
      int y0 = getY();
      int y1 = y0 + 16;
      ulDrawImageXY(imgKey, x0, y0);
      if (keyboardMode == KB_KANJI_LVL4_1) {
        drawAnimation_1(x0, y0, x1, y1, RGB15(31, 31, 0));
      }
      drawShadowedText("1", x0 + 4, y0 + 4, RGB15(31, 31, 31), RGB15(0, 0, 0));

      y0 += 24;
      y1 = y0 + 16;
      ulDrawImageXY(imgKey, x0, y0);
      if (keyboardMode == KB_KANJI_LVL4_2) {
        drawAnimation_1(x0, y0, x1, y1, RGB15(31, 31, 0));
      }
      drawShadowedText("2", x0 + 4, y0 + 4, RGB15(31, 31, 31), RGB15(0, 0, 0));

      y0 += 24;
      y1 = y0 + 16;
      ulDrawImageXY(imgKey, x0, y0);
      if (keyboardMode == KB_KANJI_LVL4_3) {
        drawAnimation_1(x0, y0, x1, y1, RGB15(31, 31, 0));
      }
      drawShadowedText("3", x0 + 4, y0 + 4, RGB15(31, 31, 31), RGB15(0, 0, 0));
    }
  }
}
