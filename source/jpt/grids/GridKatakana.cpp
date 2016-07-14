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
#include "GridKatakana.h"

using namespace jlpt;

GridKatakana::GridKatakana(Component* parent, char* imageName,
  char* imageKeyName) :
  Grid(parent, imageName, imageKeyName) {
  keyboardMode = KB_NORMAL;
}

int GridKatakana::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {
    int level = scoreManager->getLevel(1);
    if (ul_keys.pressed.left) {
      int i = selectedItem->getX();
      if (i == 0) {
        selectedItem->setX(10);
      } else {
        selectedItem->setX(i-1);
      }
      displayIdeogram(selectedItem->getX(), selectedItem->getY());
    } else if (ul_keys.pressed.right) {
      int i = selectedItem->getX();
      if (i == 10) {
        selectedItem->setX(0);
      } else {
        selectedItem->setX(i+1);
      }
      displayIdeogram(selectedItem->getX(), selectedItem->getY());
    } else if (ul_keys.pressed.up) {
      int i = selectedItem->getY();
      if (i == 0) {
        selectedItem->setY(4);
      } else {
        selectedItem->setY(i-1);
      }
      displayIdeogram(selectedItem->getX(), selectedItem->getY());
    } else if (ul_keys.pressed.down) {
      int i = selectedItem->getY();
      if (i == 4) {
        selectedItem->setY(0);
      } else {
        selectedItem->setY(i+1);
      }
      displayIdeogram(selectedItem->getX(), selectedItem->getY());
    } else if (ul_keys.pressed.X || ul_keys.pressed.Y || ul_keys.pressed.A) {
      // Tres bon niveau
      if (level >= 14) {
        if (keyboardMode == KB_DAKUTEN) {
          keyboardMode = KB_HANDAKUTEN;
        } else if (keyboardMode == KB_HANDAKUTEN) {
          keyboardMode = KB_NORMAL;
        } else {
          keyboardMode = KB_DAKUTEN;
        }
      }
      // Bon niveau
      else if (level >= 10) {
        if (keyboardMode == KB_DAKUTEN) {
          keyboardMode = KB_NORMAL;
        } else {
          keyboardMode = KB_DAKUTEN;
        }
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
        int x0 = getX() + getWidth() + 4;
        int y0 = getY();
        Rectangle* rectMode = new Rectangle(x0, y0, 16, 16);

        if (rectMode->contains(ul_keys.touch.x, ul_keys.touch.y)) {
          if (keyboardMode == KB_DAKUTEN) {
            keyboardMode = KB_NORMAL;
          } else {
            keyboardMode = KB_DAKUTEN;
          }
          displayIdeogram(selectedItem->getX(), selectedItem->getY());
          delete rectMode;
          return CMD_NONE;
        }

        rectMode->setRect(x0, y0 + 32, 16, 16);

        if (rectMode->contains(ul_keys.touch.x, ul_keys.touch.y)) {
          if (keyboardMode == KB_HANDAKUTEN) {
            keyboardMode = KB_NORMAL;
          } else {
            keyboardMode = KB_HANDAKUTEN;
          }
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

void GridKatakana::displayIdeogram(int i, int j) {

  if (keyboardMode == KB_DAKUTEN) {
    if (i == 1 || i == 2 || i == 3) {
      i += 10;
    } else if (i == 5) {
      i += 9;
    }
  } else if (keyboardMode == KB_HANDAKUTEN) {
    if (i == 5) {
      i += 10;
    }
  }

  int level = scoreManager->getLevel(1);
  
  // Niveau pas assez grand  
  if (i > level) {
    displayUnlockMessage("To unlock this katakana ideogram, please go to the game section and choose 'KATA'.\n\n You need to make a perfect at this game to unlock the next column.\n\nMaximum level is Grand Master (15 perfects).");
  }
  // Affichage du caractere selectionne
  else if (katakana_Sprite[i][j] != NULL) {

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

    PA_LoadSpritePal(SCREEN_UP, PALETTE_0,
        (void*)katakana_Pal[i][j]);
    PA_CreateSprite(SCREEN_UP, SPRITE_0,
        (void*)katakana_Sprite[i][j], OBJ_SIZE_64X64,COLOR_256, PALETTE_0, 21 , 53);

    // Lecture du fichier des definitions
    KANA_DATA data;
    std::string filePath = getFilePath("katakana.txt", scoreManager);
    FileReader* fileReader = new FileReader(filePath.c_str(), UNICODE);
    fileReader->open("rb");
    fileReader->seek((i*5 + j)*sizeof(data));
    fileReader->read(&data, sizeof(data), 1);    
    
    const char* txt = fileReader->getAscii(data.syllabus, 10);
    if(!isEmpty(txt)) {
      PA_16cText(SCREEN_UP,95,48, SCREEN_WIDTH, SCREEN_HEIGHT, "Pronunciation : ", BLACK, SIZE_2, 17);
      char kunYomi[5];
      sprintf(kunYomi, "%s", txt);
      PA_16cText(SCREEN_UP,190,46, SCREEN_WIDTH, SCREEN_HEIGHT, kunYomi, BLACK, SIZE_3, 5);
    }

    const u16* sampleKana = fileReader->getKana(data.sampleKana, 18);
    if(!isEmpty(sampleKana)) {
      PA_16cText(SCREEN_UP,95,70, SCREEN_WIDTH, SCREEN_HEIGHT, "Sample : ", BLACK, SIZE_2, 10);
      jis.displayJapaneseString(sampleKana,12,10);
    }

    const char* sampleRomanji = fileReader->getAscii(data.sampleRomanji, 50);
    if(!isEmpty(sampleRomanji)) {
      char romanji[35];
      sprintf(romanji, "Romanji : %s", sampleRomanji);
      PA_16cText(SCREEN_UP,95,112, SCREEN_WIDTH - 20, SCREEN_HEIGHT, romanji, BLACK, SIZE_2, 35);
    }

    const char* sampleTranslated = fileReader->getAscii(data.sampleTranslated, 120);
    if(!isEmpty(sampleTranslated)) {
      char meaning[70];
      sprintf(meaning, "Means : %s", sampleTranslated);
      PA_16cText(SCREEN_UP,20,134, SCREEN_WIDTH - 20, SCREEN_HEIGHT, meaning, BLACK, SIZE_2, 70);
    }
    fileReader->close();
  }
  Grid::displayIdeogram(i, j);
}

void GridKatakana::display(SCREEN scr) {
  Component::display(scr);
  if (visible && screen == scr) {

    if (imgTiles == NULL) {
      show();
    } else {
      int x = getX();
      int y = getY();
      int level = scoreManager->getSelectedRecord().level[1];

      // Dessin des caracteres
      for (int i = 5; i < 10; i++) {
        for (int j = 0; j < 11; j++) {
          ulDrawImageXY(imgKey, x, y);
          if (keyboardMode == KB_NORMAL) {
            drawIdeogram(imgTiles, i, j, x, y, level);
          } else if (keyboardMode == KB_DAKUTEN) {
            if (j != 1 && j != 2 && j != 3 && j != 5) {
              drawIdeogram(imgTiles, i, j, x, y, level);
            }
          } else if (keyboardMode == KB_HANDAKUTEN) {
            if (j != 5) {
              drawIdeogram(imgTiles, i, j, x, y, level);
            }
          }
          x += FONT_TILE_16x16;
        }
        x = getX();
        y += FONT_TILE_16x16;
      }

      if (keyboardMode == KB_DAKUTEN) {

        for (int i = 5; i < 10; i++) {
          int j = 11;
          x = getX() + (j-10)*FONT_TILE_16x16;
          y = getY() + (i-5)*FONT_TILE_16x16;
          drawIdeogram(imgTiles, i, j, x, y, level);
          j = 12;
          x = getX() + (j-10)*FONT_TILE_16x16;
          drawIdeogram(imgTiles, i, j, x, y, level);
          j = 13;
          x = getX() + (j-10)*FONT_TILE_16x16;
          drawIdeogram(imgTiles, i, j, x, y, level);
          j = 14;
          x = getX() + (j-9)*FONT_TILE_16x16;
          drawIdeogram(imgTiles, i, j, x, y, level);
        }
      } else if (keyboardMode == KB_HANDAKUTEN) {
        for (int i = 5; i < 10; i++) {
          x = getX() + 5*FONT_TILE_16x16;
          y = getY() + (i-5)*FONT_TILE_16x16;
          drawIdeogram(imgTiles, i, 15, x, y, level);
        }
      }

      // Dessin de la selection
      int selectedX = getX() + 16*selectedItem->getX();
      int selectedY = getY() + 16*selectedItem->getY();
      drawAnimation_1(selectedX, selectedY, selectedX+16, selectedY+16, RGB15(
          31, 0, 0));

      // Dessin des options : " : ° : small
      int x0 = getX() + getWidth() + 4;
      int x1 = x0 + 16;
      int y0 = getY();
      int y1 = y0 + 16;
      if (level >= 10) {
        ulDrawImageXY(imgKey, x0, y0);
        if (keyboardMode == KB_DAKUTEN) {
          drawAnimation_1(x0, y0, x1, y1, RGB15(31, 0, 0));
        }
        drawShadowedText("\"", x0 + 4, y0 + 6, RGB15(31, 31, 31),
            RGB15(0, 0, 0));
      }

      y0 += 32;
      y1 = y0 + 16;
      if (level >= 14) {
        ulDrawImageXY(imgKey, x0, y0);
        if (keyboardMode == KB_HANDAKUTEN) {
          drawAnimation_1(x0, y0, x1, y1, RGB15(31, 0, 0));
        }
        drawShadowedText("°", x0 + 4, y0 + 6, RGB15(31, 31, 31), RGB15(0, 0, 0));
      }
    }
  }
}
