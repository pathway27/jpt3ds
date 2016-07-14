#include <ulib/ulib.h>
#include <PA9.h>
#include "snd_select.h"
#include "snd_scroll.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include "../../gfx/all_gfx.h"
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"
#include "../geometry/Dimension.h"
#include "../Commands.h"
#include "../Tools.h"
#include "../components/Component.h"
#include "../components/TextComponent.h"
#include "../components/Button.h"
#include "../files/File.h"
#include "../files/FileReader.h"
#include "../fonts/Jis.h"
#include "VocabularyList.h"

using namespace jlpt;

const static int kanaToolbar[][2] = { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 }, {
    4, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 }, { 4, 1 }, { 0, 2 },
    { 1, 2 }, { 2, 2 }, { 3, 2 }, { 4, 2 }, { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3,
        3 }, { 4, 3 }, { 0, 4 }, { 1, 4 }, { 2, 4 }, { 3, 4 }, { 4, 4 },
    { 0, 5 }, { 1, 5 }, { 2, 5 }, { 3, 5 }, { 4, 5 }, { 0, 6 }, { 1, 6 }, { 2,
        6 }, { 3, 6 }, { 4, 6 }, { 0, 7 }, { 2, 7 }, { 4, 7 }, { 0, 8 },
    { 1, 8 }, { 3, 8 }, { 4, 8 }, { 0, 9 }, { 1, 7 }, { 1, 7 }, { 1, 7 }, { 1,
        7 }, { 1, 7 }, { 1, 7 }, { 1, 7 } };

VocabularyList::VocabularyList(Component* parent) :
  Component(parent) {
  type = TYPE_VOCAB;
  imgTiles = NULL;
  imgKey = NULL;
  imgHand = NULL;
  imageName = "kanas.gif";
  imageKeyName = "key_4.gif";
  offsetX = 0;
  offsetY = 0;
  selectedKana = 0;
  selectedEntry = 0;
  jis = NULL;
  scoreManager = NULL;
  
  Button* buttonLeft = new Button(this, "bt_left.gif");
  buttonLeft->setMaxDelay(0);
  buttonLeft->setSize(16, 16);
  buttonLeft->setLocation(0, 0);
  buttonLeft->setCommand(VOCAB_LEFT);
  buttonLeft->setSound(snd_select, (u32)snd_select_size);
  this->add(buttonLeft);

  Button* buttonRight = new Button(this, "bt_right.gif");
  buttonRight->setMaxDelay(0);
  buttonRight->setSize(16, 16);
  buttonRight->setLocation(192-16, 0);
  buttonRight->setCommand(VOCAB_RIGHT);
  buttonRight->setSound(snd_select, (u32)snd_select_size);
  this->add(buttonRight);

  buttonUp = new Button(this, "bt_up.gif");
  buttonUp->setMaxDelay(0);
  buttonUp->setSize(16, 16);
  buttonUp->setLocation(192-16, 16);
  buttonUp->setCommand(VOCAB_UP);
  buttonUp->setSound(snd_scroll, (u32)snd_scroll_size);
  this->add(buttonUp);

  buttonDown = new Button(this, "bt_down.gif");
  buttonDown->setMaxDelay(0);
  buttonDown->setSize(16, 16);
  buttonDown->setLocation(192-16, 80);
  buttonDown->setCommand(VOCAB_DOWN);
  buttonDown->setSound(snd_scroll, (u32)snd_scroll_size);
  this->add(buttonDown);

  // Lecture des 'A'
  readIndex();
}

VocabularyList::~VocabularyList() {
  delete buttonUp;
  delete buttonDown;
  delete jis;
}

void VocabularyList::setScoreManager(ScoreManager* s) {
  scoreManager = s;
}

void VocabularyList::readIndex() {
  // Ouverture de l'index
  std::string filePath = getFilePath("vocabulary_index.txt", scoreManager);
  FileReader* fileReader = new FileReader(filePath.c_str(), ASCII);
  fileReader->open("r");
    
  char temp[10];
  for(int i = 0; i < 51; i++) {    
    if(fileReader->get(temp , 10) != NULL) {
      kanaIndex[i] = atoi(temp);
    } else {
      kanaIndex[i] = 0;
    }
  }
  
  // Fermeture de l'index
  fileReader->close();
}

void VocabularyList::readDictionnary(int index) {

  int lineOffset = kanaIndex[index];
  int linesToRead = kanaIndex[index+1] - kanaIndex[index];

  // Initialisation des listes
  vocabEntries.clear();
  meaningEntries.clear();
  kanaEntries.clear();

  // Initialisation de la selection
  selectedEntry = 0;
  offsetY = 0;

  // On masque certains boutons au depart
  buttonUp->hide();
  buttonDown->hide();  
  
  if (lineOffset == 0 && linesToRead == 0) {
    return;
  }
  
  // Ouverture du dictionnaire
  std::string filePath = getFilePath("vocabulary_simple.txt", scoreManager);
  FileReader* fileReader = new FileReader(filePath.c_str(), UNICODE);
  fileReader->open("rb");
  VOCAB_DATA data;

  // Positionnement du curseur
  fileReader->seek(lineOffset*sizeof(data));

  int linesRead = 0;

  // Lecture des entrees
  while (linesRead < linesToRead && fileReader->read(&data, sizeof(data), 1)
      == 1) {
    vocabEntries.push_back(std::string(fileReader->getAscii(data.romanji, 40)));
    meaningEntries.push_back(std::string(fileReader->getAscii(data.meaning, 180)));
    kanaEntries.push_back(fileReader->getKana(data.japanese, 30));
    linesRead++;
  }

  // Fermeture du dictionnaire
  fileReader->close();

  if (isScrollerVisible()) {
    buttonUp->show();
    buttonDown->show();
  }
}

void VocabularyList::display(SCREEN scr) {
  Component::display(scr);
  if (visible && screen == scr) {
    // Faut-il montrer le scroller?
    bool showScroller = isScrollerVisible();
    int maxSize = getMaxX();
    if (showScroller) {
      maxSize -= 16;
    }

    // Fond de la liste
    ulDrawFillRect(getX(), getY()+16, maxSize, getMaxY(), RGB15(31, 25, 0));
    ulDrawFillRect(getX()+1, getY()+16+1, maxSize-1, getMaxY()-1, RGB15(25, 12,
        0));

    // Liste des caracteres
    for (int i = 0; i < 10; i++) {
      ulDrawImageXY(imgKey, getX()+16+(16*i), getY());
      if(kanaToolbar[i + offsetX*10][0] == 1 && 
          kanaToolbar[i + offsetX*10][1] == 7) {
        drawShadowedText("?", getX()+20+(16*i), getY()+3, RGB15(31,
                      31, 31), RGB15(0, 0, 0));
      } else {
        drawTile(imgTiles, kanaToolbar[i + offsetX*10][0],
          kanaToolbar[i + offsetX*10][1], getX()+16+(16*i), getY());
      }
    }

    u8 nb = vocabEntries.size();
    if (nb > 0) {
      // Affichage des entrees du dictionnaire
      u8 sel = selectedEntry-offsetY;
      if (nb > 5)
        nb = 5;
      for (u8 i = 0; i < nb; i++) {
        if (i != sel) {
          std::string s1 = vocabEntries.at(i + offsetY);
          drawShadowedText(s1.data(), getX()+5, getY()+16+(16*i)+3, RGB15(31,
              31, 31), RGB15(0, 0, 0));
        }
      }

      // Affichage de l'entree selectionnee
      if (sel < 5) {
        ulDrawFillRect(getX(), getY()+16+16*sel, maxSize, getY()+2*16+16*sel,
            RGB15(31, 25, 0));

        std::string s1 = vocabEntries.at(sel + offsetY);
        drawShadowedText(s1.data(), getX()+5, getY()+16+(16*sel)+3, RGB15(0, 0,
            0), RGB15(31, 31, 31));

        // Affichage de la petite main
        drawHand(sel);
      }
    }

    // Affichage des boutons
    displayChildren(scr);

    // Affichage du scroller
    drawScroller();

    // Affichage du caractere selectionne
    drawAnimation_1(getX()+16+(16*selectedKana), getY(), getX()+2*16+(16
        *selectedKana), getY()+16, RGB15(0, 0, 31));
  }
}

void VocabularyList::drawScroller() {
  if (isScrollerVisible()) {
    ulDrawFillRect(getMaxX()-16, getY()+2*16, getMaxX(), getMaxY()-16, RGB15(
        15, 15, 15));
    if (vocabEntries.size() > 5) {
      float height = getHeight()-3*16;
      float step = (1000*height)/vocabEntries.size();
      float o1 = (offsetY*step)/1000;
      float o2 = ((offsetY+5)*step)/1000;

      ulDrawFillRect(getMaxX()-16, (int)(getY()+2*16+o1), getMaxX(), (int)(getY()+2*16+o2),
          RGB15(0, 0, 0));
    }
  }
}

void VocabularyList::drawHand(int sel) {
  int offset = 0;
  if (nbFrame >= 0 && nbFrame <= 10) {
    offset = 2;
  } else if (nbFrame >= 10 && nbFrame <= 20) {
    offset = 4;
  } else if (nbFrame >= 20 && nbFrame <= 30) {
    offset = 2;
  } else if (nbFrame >= 30 && nbFrame <= 40) {
    offset = 4;
  } else if (nbFrame >= 40 && nbFrame <= 50) {
    offset = 2;
  } else if (nbFrame >= 50 && nbFrame <= 60) {
    offset = 4;
  }
  ulDrawImageXY(imgHand, getX() - 17 + offset, getY()+16+16*sel);
}

void VocabularyList::displayDictionnaryEntry(bool firstTime) {

  // On affiche l'onglet pour la premiere fois
  if(firstTime) {
    // Reinitialisation du systeme de sprites
    PA_ResetSpriteSysScreen(SCREEN_UP);
  
    // Reinitialisation des fonds d'ecrans
    PA_ResetBgSysScreen(SCREEN_UP);
  
    // Initialisation du fond reserve au texte
    PA_Init16cBg(SCREEN_UP, BG_0);
  
    // Fond d'ecran superieur
    PA_LoadTiledBg(SCREEN_UP, BG_3, bg_top_vocabulary);
  
    // Fond pour ecrire avec les kanas
    jis = new Jis(SCREEN_UP, BG_2);
  } 
  // Sinon on nettoie l'ecran
  else {
    PA_16cErase(SCREEN_UP);
    PA_ClearBg(SCREEN_UP, BG_2);
  }
  
  if(jis == NULL) {
    return;
  }
  
  // Aucune selection
  if (selectedEntry >= meaningEntries.size()) {
    return;
  }

  // Affichage de la signification
  const char* meaning = meaningEntries.at(selectedEntry).c_str();
  if (!isEmpty(meaning)) {
    PA_16cText(SCREEN_UP, 30, 80, SCREEN_WIDTH - 20, SCREEN_HEIGHT,
        "Meaning : ", BLACK, SIZE_2, 100);
    PA_16cText(SCREEN_UP, 30, 90, SCREEN_WIDTH - 20, SCREEN_HEIGHT,
        (char*)meaning, BLACK, SIZE_2, 100);
  }

  const u16* kana = kanaEntries.at(selectedEntry);
  if (!isEmpty(kana)) {
    PA_16cText(SCREEN_UP, 30, 42, SCREEN_WIDTH, SCREEN_HEIGHT,
        "Pronunciation :", BLACK, SIZE_2, 15);
    jis->displayJapaneseString(kana, 4, 7);
  }
}

void VocabularyList::show() {

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
  if (imgHand == NULL) {
    imgHand = loadImageGIF("menu_hand.gif", UL_PF_PAL4);
  } else {
    ulRealizeImage(imgHand);
  }
  readDictionnary(selectedKana + offsetX*10);
  displayDictionnaryEntry(true);
  this->playSoundEx0(snd_select, (u32)snd_select_size);
  Component::show();
}

void VocabularyList::hide() {

  if (imgTiles != NULL) {
    ulUnrealizeImage(imgTiles);
  }
  if (imgKey != NULL) {
    ulUnrealizeImage(imgKey);
  }
  if (imgHand != NULL) {
    ulUnrealizeImage(imgHand);
  }
  Component::hide();
}

bool VocabularyList::isScrollerVisible() {
  if (vocabEntries.size() <= 5) {
    return false;
  }
  return true;
}

int VocabularyList::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {
    // Le scroller est-il visible?
    bool showScroller = isScrollerVisible();

    // Gestion des touches
    // Pagination vers la GAUCHE
    if (ul_keys.pressed.Y) {
      offsetX--;
      if (offsetX < 0)
        offsetX = 0;
      readDictionnary(selectedKana + offsetX*10);
      displayDictionnaryEntry(false);
      this->playSoundEx0(snd_select, (u32)snd_select_size);
      return CMD_NONE;
    } 
    // Pagination vers la DROITE
    else if (ul_keys.pressed.A) {
      offsetX++;
      if (offsetX > 4)
        offsetX = 4;

      readDictionnary(selectedKana + offsetX*10);
      displayDictionnaryEntry(false);
      this->playSoundEx0(snd_select, (u32)snd_select_size);
      return CMD_NONE;
    } 
    // Scroll vers le HAUT
    else if (ul_keys.pressed.up) {
      if (selectedEntry > 0) {
        selectedEntry--;
        if (selectedEntry == offsetY - 1) {
          offsetY--;
        }
        displayDictionnaryEntry(false);
      }
      this->playSoundEx0(snd_scroll, (u32)snd_scroll_size);
      return CMD_NONE;
    } 
    // Scroll vers le BAS
    else if (ul_keys.pressed.down) {
      if (selectedEntry < vocabEntries.size() - 1) {
        selectedEntry++;
        if ((selectedEntry - offsetY) == 5) {
          offsetY++;
        }
        displayDictionnaryEntry(false);
      }
      this->playSoundEx0(snd_scroll, (u32)snd_scroll_size);
      return CMD_NONE;
    } 
    // Selection vers la GAUCHE
    else if (ul_keys.pressed.left) {
      if (selectedKana == 0) {
        if (offsetX > 0) {
          selectedKana = 9;
        }
        // Page precedente
        offsetX--;
        if (offsetX < 0)
          offsetX = 0;
      } else {
        selectedKana--;
      }
      readDictionnary(selectedKana + offsetX*10);
      displayDictionnaryEntry(false);
      this->playSoundEx0(snd_select, (u32)snd_select_size);
      return CMD_NONE;
    } 
    // Selection vers la DROITE
    else if (ul_keys.pressed.right) {
      if (selectedKana == 9) {
        if(offsetX < 4) {
          selectedKana = 0;
          // Page suivante
          offsetX++;
        }
      } else {
        selectedKana++;
      }

      readDictionnary(selectedKana + offsetX*10);
      displayDictionnaryEntry(false);
      this->playSoundEx0(snd_select, (u32)snd_select_size);
      return CMD_NONE;
    }
    // Gestion stylet
    else if (ul_keys.touch.click) {
      Component::dealEvent(scr);
      Rectangle* rect = getBounds();
      int x = ul_keys.touch.x;
      int y = ul_keys.touch.y;
      if (rect->contains(x, y)) {

        // Gestion de la selection d'un caractere
        if (x >= (getX()+16) && x <= (getMaxX()-16) && y >= getY() && y
            <= getY()+16) {
          int selection = (x-getX())/16-1;

          selectedKana = selection;
          readDictionnary(selectedKana + offsetX*10);
          displayDictionnaryEntry(false);
          this->playSoundEx0(snd_select, (u32)snd_select_size);
        }

        // Gestion de la selection d'une entree
        else if (x >= getX() && x <= (getMaxX()-16) && y >= (getY()+16) && y
            <= getMaxY()) {
          u8 selection = (y-getY())/16 - 1 + offsetY;
          if (selection < meaningEntries.size()) {
            selectedEntry = selection;
            displayDictionnaryEntry(false);
          }
          this->playSoundEx0(snd_select, (u32)snd_select_size);
        }

        // Gestion du scrolling vertical
        else if (showScroller && x >= (getMaxX()-16) && x <= getMaxX() && y
            >= (getY() + 32) && y <= (getMaxY() - 16)) {

          if (vocabEntries.size() > 5) {
            float height = getHeight()-3*16;
            float step = (1000*height)/vocabEntries.size();
            float o1 = (offsetY*step)/1000;
            float o2 = ((offsetY+5)*step)/1000;

            int y1 = (int)(getY()+32+o1);
            int y2 = (int)(getY()+32+o2);

            if (y < y1) {
              if (offsetY > 5) {
                offsetY-=5;
              } else {
                offsetY = 0;
              }
              selectedEntry = offsetY + 4;
              displayDictionnaryEntry(false);
            } else if (y > y2) {
              if (offsetY < vocabEntries.size() - 5) {
                offsetY+=5;
              } else {
                offsetY = vocabEntries.size() - 5;
              }
              if (offsetY > (vocabEntries.size()-5)) {
                offsetY = vocabEntries.size()-5;
              }
              selectedEntry = offsetY;
              displayDictionnaryEntry(false);
            }
          }
          this->playSoundEx0(snd_scroll, (u32)snd_scroll_size);
        }
      }
    }
    // Gestion des evenements remontes par les composants     
    else {
      int c = Component::dealEvent(scr);
      // Pagination a GAUCHE
      if (c == VOCAB_LEFT) {
        offsetX--;
        if (offsetX < 0)
          offsetX = 0;
        readDictionnary(selectedKana + offsetX*10);
        displayDictionnaryEntry(false);
        return CMD_NONE;
      }
      // Pagination a DROITE
      else if (c == VOCAB_RIGHT) {
        offsetX++;
        if (offsetX > 4)
          offsetX = 4;

        readDictionnary(selectedKana + offsetX*10);
        displayDictionnaryEntry(false);
        return CMD_NONE;
      }
      // Scroll vers le HAUT
      else if (c == VOCAB_UP) {
        // Montee de la liste
        if (offsetY > 0) {
          offsetY--;
        }
        // Montee de la selection
        if (selectedEntry - offsetY == 5) {
          selectedEntry--;
          displayDictionnaryEntry(false);
        }
        return CMD_NONE;
      }
      // Scroll vers le BAS
      else if (c == VOCAB_DOWN) {
        if (vocabEntries.size() > 5) {
          // Descente de la liste
          offsetY++;
          if (offsetY > (vocabEntries.size()-5)) {
            offsetY = vocabEntries.size()-5;
          }
          // Descente de la selection
          if (offsetY - selectedEntry == 1) {
            selectedEntry++;
            displayDictionnaryEntry(false);
          }
        }
        return CMD_NONE;
      }
    }
  }
  return CMD_NONE;
}
