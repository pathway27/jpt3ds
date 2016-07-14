#include <PA9.h>
#include "snd_welcome.h"
#include <ulib/ulib.h>
#include <vector>
#include "../gfx/all_gfx.h"
#include "Commands.h"
#include "geometry/Point.h"
#include "geometry/Dimension.h"
#include "geometry/Rectangle.h"
#include "Tools.h"
#include "fonts/Ascii.h"
#include "fonts/Jis.h"
#include "components/ProgressBar.h"
#include "components/Component.h"
#include "data/Stroke.h"
#include "data/Gesture.h"
#include "components/TextComponent.h"
#include "components/DrawComponent.h"
#include "components/Input.h"
#include "components/Keyboard.h"
#include "components/KeyboardJis.h"
#include "components/KeyboardAscii.h"
#include "components/Button.h"
#include "components/CheckBox.h"
#include "components/List.h"
#include "components/Panel.h"
#include "scores/ScoreManager.h"
#include "grids/Grid.h"
#include "grids/GridHiragana.h"
#include "grids/GridKatakana.h"
#include "grids/GridKanji.h"
#include "grids/VocabularyList.h"
#include "menus/Menu.h"
#include "menus/MenuStart.h"
#include "menus/MenuProfiles.h"
#include "menus/MenuProfile.h"
#include "menus/MenuMain.h"
#include "menus/MenuLearn.h"
#include "menus/MenuPractice.h"
#include "menus/MenuDifficulty.h"
#include "menus/MenuOptions.h"
#include "games/Game.h"
#include "games/GameIdeogram.h"
#include "games/GameHiragana.h"
#include "games/GameKatakana.h"
#include "games/GameKanji.h"
#include "games/GameDraw.h"
#include "games/GameNumbers.h"
#include "games/GameVocabulary.h"
#include "files/File.h"
#include "files/FileReader.h"
#include "files/FileWriter.h"
#include "App.h"

using namespace jlpt;

typedef enum MENUS {
  MENU_START = 1,
  MENU_PROFILES = 2,
  MENU_PROFILE = 3,
  MENU_MAIN = 4,
  MENU_LEARN = 5,
  MENU_PRACTICE = 6,
  MENU_DIFFICULTY = 7,
  MENU_OPTIONS = 8,
  MENU_GAME_HIRAGANA = 9,
  MENU_GAME_KATAKANA = 10,
  MENU_GAME_KANJI = 11,
  MENU_GAME_DRAW = 12,
  MENU_GAME_NUMBERS = 15,
  MENU_GAME_VOCABULARY = 16
};

App::App() :
  Component(NULL) {
  // Taille et position
  this->setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  this->setLocation(0, 0);

  // L'etat de l'application
  state = MENU_START;
  type = TYPE_APP;
  visible = true;
  debugMode = false;
  
  // Fond d'ecran inferieur
  loadBackgroundImage("bg_bottom_screen.gif", UL_PF_PAL4);

  // Fond d'ecran superieur
  PA_LoadTiledBg(SCREEN_UP, BG_3, bg_home_top_screen);

  // Gestion des scores
  scoreManager = new ScoreManager();
  scoreManager->readProfiles();

  // Creation des menus
  menuStart = new MenuStart(this);
  menuStart->show();
  add(menuStart);

  menuProfiles = new MenuProfiles(this);
  menuProfiles->setScoreManager(scoreManager);
  menuProfiles->hide();
  add(menuProfiles);

  menuProfile = new MenuProfile(this);
  menuProfile->hide();
  add(menuProfile);

  menuMain = new MenuMain(this);
  menuMain->hide();
  add(menuMain);

  menuLearn = new MenuLearn(this, scoreManager);
  menuLearn->hide();
  add(menuLearn);

  menuPractice = new MenuPractice(this);
  menuPractice->hide();
  add(menuPractice);

  menuDifficulty = new MenuDifficulty(this);
  menuDifficulty->setScoreManager(scoreManager);
  menuDifficulty->hide();
  add(menuDifficulty);

  menuOptions = new MenuOptions(this);
  menuOptions->setScoreManager(scoreManager);
  menuOptions->hide();
  add(menuOptions);

  gameHiragana = new GameHiragana(this, scoreManager);
  gameHiragana->hide();
  add(gameHiragana);

  gameKatakana = new GameKatakana(this, scoreManager);
  gameKatakana->hide();
  add(gameKatakana);

  gameKanji = new GameKanji(this, scoreManager);
  gameKanji->hide();
  add(gameKanji);

  gameDraw = new GameDraw(this, scoreManager);
  gameDraw->hide();
  add(gameDraw);

  gameNumbers = new GameNumbers(this, scoreManager);
  gameNumbers->hide();
  add(gameNumbers);
  
  gameVocabulary = new GameVocabulary(this, scoreManager);
  gameVocabulary->hide();
  add(gameVocabulary);
  
  this->playSoundEx0(snd_welcome, (u32)snd_welcome_size);
}

App::~App() {
  delete menuStart;
  delete menuProfiles;
  delete menuProfile;
  delete menuMain;
  delete menuLearn;
  delete menuPractice;
  delete menuDifficulty;
  delete menuOptions;
  delete gameHiragana;
  delete gameKatakana;
  delete gameKanji;
  delete gameDraw;
  delete gameNumbers;
  delete gameVocabulary;
  delete scoreManager;
}

void App::display(SCREEN scr) {
  Component::display(scr);
  if(debugMode) {
    drawTransparentRect(10, 10, 246, 182, RGB15(16,16,16));
    char text[40];
    sprintf(text, "TexVramAvailMemory : %d", ulGetTexVramAvailMemory());
    drawShadowedText(text, 20, 20, RGB15(0,0,0), RGB15(31,31,31));
    
    sprintf(text, "TexVramUsedMemory : %d", ulGetTexVramUsedMemory());
    drawShadowedText(text, 20, 30, RGB15(0,0,0), RGB15(31,31,31));

    sprintf(text, "TexVramTotalMemory : %d", ulGetTexVramTotalMemory());
    drawShadowedText(text, 20, 40, RGB15(0,0,0), RGB15(31,31,31));

    sprintf(text, "TexPalAvailMemory : %d", ulGetTexPalAvailMemory());
    drawShadowedText(text, 20, 50, RGB15(0,0,0), RGB15(31,31,31));
    
    sprintf(text, "TexPalUsedMemory : %d", ulGetTexPalUsedMemory());
    drawShadowedText(text, 20, 60, RGB15(0,0,0), RGB15(31,31,31));

    sprintf(text, "TexPalTotalMemory : %d", ulGetTexPalTotalMemory());
    drawShadowedText(text, 20, 70, RGB15(0,0,0), RGB15(31,31,31));

    sprintf(text, "VertexAvailMemory : %d", ulGetVertexAvailMemory());
    drawShadowedText(text, 20, 80, RGB15(0,0,0), RGB15(31,31,31));
    
    sprintf(text, "VertexUsedMemory : %d", ulGetVertexUsedMemory());
    drawShadowedText(text, 20, 90, RGB15(0,0,0), RGB15(31,31,31));

    sprintf(text, "VertexTotalMemory : %d", ulGetVertexTotalMemory());
    drawShadowedText(text, 20, 100, RGB15(0,0,0), RGB15(31,31,31));
  }
}

int App::dealEvent(SCREEN scr) {
  // Gestion clavier : start
  if (ul_keys.pressed.start && state == MENU_START) {
    Button* btn = (Button*)menuStart->getComponent(0, TYPE_BUTTON);
    btn->press();
  } 
  // Gestion debug : select
  else if(ul_keys.pressed.select) {
    if(debugMode) {
      debugMode = false;
    } else {
      debugMode = true;
    }
  } 
  // Autres
  else {
    int c = dealEventChildren(scr);

    if (c == START) {
      menuStart->hide();
      menuProfiles->show();
      state = MENU_PROFILES;
    } 
    // BACK
    else if (c == BACK) {
      // A partir du menu MAIN
      if (state == MENU_MAIN) {
        menuMain->hide();
        menuProfiles->show();
        state = MENU_PROFILES;
      }
      // A partir du menu PROFILE
      else if (state == MENU_PROFILE) {
        menuProfile->hide();
        menuProfiles->show();
        state = MENU_PROFILES;
      }
      // A partir du menu DIFFICULTY
      else if (state == MENU_DIFFICULTY) {
        menuDifficulty->hide();
        menuPractice->show();
        state = MENU_PRACTICE;
      }
      // A partir du menu OPTIONS
      else if (state == MENU_OPTIONS) {
        menuOptions->hide();
        menuMain->show();
        state = MENU_MAIN;
        refreshTopScreen();
      }
      // A partir du menu LEARN
      else if (state == MENU_LEARN) {
        menuLearn->hide();
        menuMain->show();
        state = MENU_MAIN;
        refreshTopScreen();
      }
      // A partir du menu PRACTICE
      else if (state == MENU_PRACTICE) {
        menuPractice->hide();
        menuMain->show();
        state = MENU_MAIN;
        refreshTopScreen();
      }
      // A partir du jeu HIRAGANA
      else if (state == MENU_GAME_HIRAGANA) {
        gameHiragana->hide();
        menuPractice->show();
        state = MENU_PRACTICE;
        refreshTopScreen();
      }
      // A partir du jeu KATAKANA
      else if (state == MENU_GAME_KATAKANA) {
        gameKatakana->hide();
        menuPractice->show();
        state = MENU_PRACTICE;
        refreshTopScreen();
      }
      // A partir du jeu KANJI
      else if (state == MENU_GAME_KANJI) {
        gameKanji->hide();
        menuPractice->show();
        state = MENU_PRACTICE;
        refreshTopScreen();
      }
      // A partir du jeu DRAW
      else if (state == MENU_GAME_DRAW) {
        gameDraw->hide();
        menuPractice->show();
        state = MENU_PRACTICE;
        refreshTopScreen();
      }
      // A partir du jeu NUMBERS
      else if (state == MENU_GAME_NUMBERS) {
        gameNumbers->hide();
        menuPractice->show();
        state = MENU_PRACTICE;
        refreshTopScreen();
      }
      // A partir du jeu VOCABULARY
      else if (state == MENU_GAME_VOCABULARY) {
        gameVocabulary->hide();
        menuPractice->show();
        state = MENU_PRACTICE;
        refreshTopScreen();
      }      
    } else if (c == MAIN) {
      menuProfiles->hide();
      menuMain->show();
      state = MENU_MAIN;
    }
    // Nouveau profil
    else if (c == NEW_PROFILE) {
      menuProfiles->hide();
      menuProfile->show();
      state = MENU_PROFILE;
    }
    // Suppression d'un profil
    else if (c == DELETE_PROFILE) {
      menuOptions->hide();
      menuProfiles->getProfileButton()->setText("-- EMPTY --");
      menuProfiles->getProfileButton()->setCommand(NEW_PROFILE);
      menuProfiles->show();
      state = MENU_PROFILES;
      refreshTopScreen();
    }
    // Changement du nom du profil
    else if (c == CHANGE_NAME) {
      menuOptions->hide();
      menuProfile->getInput()->setText(scoreManager->getSelectedRecord().name);
      menuProfile->show();
      state = MENU_PROFILE;
    }
    // Sauvegarde d'un profil
    else if (c == OK) {
      menuProfile->hide();
      menuProfiles->show();
      state = MENU_PROFILES;
      saveProfile();
    }
    // Menu 'Learn'
    else if (c == LEARN) {
      menuMain->hide();
      menuLearn->show();
      state = MENU_LEARN;
    }
    // Menu 'Practice'
    else if (c == PRACTICE) {
      menuMain->hide();
      menuPractice->show();
      state = MENU_PRACTICE;
    }
    // Menu 'Options'
    else if (c == OPTIONS) {
      menuMain->hide();
      menuOptions->show();
      state = MENU_OPTIONS;
    }
    // Menu 'Difficulty'
    else if (state == MENU_PRACTICE) {
      if(c == GAME_HIRA || c == GAME_KATA || 
          c == GAME_KANJI || c == GAME_NUMBERS ||
          c == GAME_VOCAB) {
        menuPractice->hide();
        menuDifficulty->show();
      
        if(c == GAME_NUMBERS) {
          menuDifficulty->hideJoker();
        } 
        if(c == GAME_VOCAB) {
          menuDifficulty->showVocabIndex();
        } else {
          menuDifficulty->hideVocabIndex();
        }
        menuDifficulty->setCommand(c);
        state = MENU_DIFFICULTY;
      } else {
        // Game 'Draw'
        if (c == GAME_DRAW) {
          menuPractice->hide();
          gameDraw->show();
          state = MENU_GAME_DRAW;
        }
      }
    }
    // Game 'Hiragana'
    else if (c == GAME_HIRA && state == MENU_DIFFICULTY) {
      menuDifficulty->hide();
      gameHiragana->setDifficulty(menuDifficulty->getDifficulty());
      gameHiragana->setSpeed(menuDifficulty->getSpeed());
      gameHiragana->setJoker(menuDifficulty->getJoker());
      gameHiragana->show();
      state = MENU_GAME_HIRAGANA;
    }
    // Game 'Katakana'
    else if (c == GAME_KATA && state == MENU_DIFFICULTY) {
      menuDifficulty->hide();
      gameKatakana->setDifficulty(menuDifficulty->getDifficulty());
      gameKatakana->setSpeed(menuDifficulty->getSpeed());
      gameKatakana->setJoker(menuDifficulty->getJoker());
      gameKatakana->show();
      state = MENU_GAME_KATAKANA;
    }
    // Game 'Kanji'
    else if (c == GAME_KANJI && state == MENU_DIFFICULTY) {
      menuDifficulty->hide();
      gameKanji->setDifficulty(menuDifficulty->getDifficulty());
      gameKanji->setSpeed(menuDifficulty->getSpeed());
      gameKanji->setJoker(menuDifficulty->getJoker());
      gameKanji->show();
      state = MENU_GAME_KANJI;
    }
    // Game 'Vocabulary'
    else if (c == GAME_VOCAB) {
      menuDifficulty->hide();
      gameVocabulary->setVocabIndex(menuDifficulty->getVocabIndex());
      gameVocabulary->setSpeed(menuDifficulty->getSpeed());
      gameVocabulary->setJoker(menuDifficulty->getJoker());
      gameVocabulary->show();
      state = MENU_GAME_VOCABULARY;      
    }
    // Game 'Numbers'
    else if (c == GAME_NUMBERS) {
      menuDifficulty->hide();
      gameNumbers->setDifficulty(menuDifficulty->getDifficulty());
      gameNumbers->setSpeed(menuDifficulty->getSpeed());
      gameNumbers->show();
      state = MENU_GAME_NUMBERS;      
    }
    // Retry
    else if (c == RETRY) {
      if (state == MENU_GAME_HIRAGANA) {
        gameHiragana->show();
      } else if (state == MENU_GAME_KATAKANA) {
        gameKatakana->show();
      } else if (state == MENU_GAME_KANJI) {
        gameKanji->show();
      } else if (state == MENU_GAME_VOCABULARY) {
        gameVocabulary->show();
      } else if (state == MENU_GAME_NUMBERS) {
        gameNumbers->show();
      }
    }
  }
  return CMD_NONE;
}

void App::refreshTopScreen() {
  // Reinitialisation du systeme de sprites
  PA_ResetSpriteSysScreen(SCREEN_UP);

  // Reinitialisation des fonds d'ecrans
  PA_ResetBgSysScreen(SCREEN_UP);

  // Initialisation du fond reserve au texte
  PA_Init16cBg(SCREEN_UP, BG_0);

  // Fond d'ecran superieur
  PA_LoadTiledBg(SCREEN_UP, BG_3, bg_home_top_screen);
}

void App::saveProfile() {

  // Recuperation de l'indice du bouton selectionne
  int profileIndex = menuProfiles->getProfileIndex();
  if (profileIndex != -1) {

    // Lecture du profile
    RECORDS* records = scoreManager->getRecords();

    Button* button = menuProfiles->getProfileButton();
    Input* input = menuProfile->getInput();
    input->getText();
    records[profileIndex].isNew = false;
    sprintf(records[profileIndex].name, "%s", input->getText());

    // Ecriture du profile
    scoreManager->writeProfiles();

    // Changement du texte du bouton
    button->setText(input->getText());
    button->setCommand(MAIN);

    // Reinitialisation du champ texte
    input->clear();
  }
}
