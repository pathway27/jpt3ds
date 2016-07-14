#include <ulib/ulib.h>
#include <PA9.h>
#include "../../gfx/all_gfx.h"
#include "snd_right.h"
#include "snd_wrong.h"
#include "snd_back.h"
#include <vector>
#include "../Commands.h"
#include "../geometry/Point.h"
#include "../geometry/Dimension.h"
#include "../geometry/Rectangle.h"
#include "../fonts/Ascii.h"
#include "../fonts/Jis.h"
#include "../components/ProgressBar.h"
#include "../components/Component.h"
#include "../components/Panel.h"
#include "../Tools.h"
#include "../scores/ScoreManager.h"
#include "Game.h"
#include "../components/TextComponent.h"
#include "../components/TabbedPanel.h"
#include "../grids/Grid.h"
#include "../grids/GridKanji.h"
#include "../grids/GridHiragana.h"
#include "../grids/GridKatakana.h"
#include "../components/Image.h"
#include "../components/Button.h"
#include "../components/Keyboard.h"
#include "../components/KeyboardAscii.h"
#include "../components/Input.h"
#include "../grids/VocabularyList.h"
#include "../files/File.h"
#include "../files/FileReader.h"
#include "GameIdeogram.h"

using namespace jlpt;

GameIdeogram::GameIdeogram(Component* parent, ScoreManager* s) :
  Game(parent, s) {

  // Barre de progression
  createProgressBar();

  // Voulez-vous rejouer?
  createRetryPanel();

  // DIFFICULTY : HARD
  hardPanel = new Panel(this);
  this->add(hardPanel);

  input = new Input(this, "");
  input->setMaxLength(3);
  input->setSize(100, 21);
  input->setLocation(70, 20);
  input->setBorder(RGB15(0, 0, 0), 1, 31);
  input->setBackgroundColor(RGB15(31, 31, 31), 16);
  input->setShadow(RGB15(0, 0, 0), 2);
  hardPanel->add(input);

  keyboard = new KeyboardAscii(this, KB_SIMPLE);
  hardPanel->add(keyboard);

  hardJokerButton = new Button(this, RGB15(31,18,0), "JOKER");
  hardJokerButton->setSize(50, 21);
  hardJokerButton->setLocation(178, 20);
  hardJokerButton->setCommand(LATER);
  hardJokerButton->setBorder(RGB15(0, 0, 0), 2, 31);
  hardJokerButton->setShadow(RGB15(0, 0, 0), 3);
  hardJokerButton->setTextColor(RGB15(31, 31, 31));
  hardJokerButton->setTextShadow(RGB15(0, 0, 0));
  hardPanel->add(hardJokerButton);

  // DIFFICULTY : NORMAL
  normalPanel = new Panel(this);
  normalPanel->setSize(246, 150);
  normalPanel->setLocation(5, 5);
  normalPanel->setBackgroundColor(RGB15(31, 31, 31), 16);
  normalPanel->setBorder(RGB15(31, 6, 0), 3, 16);
  this->add(normalPanel);

  Button* normalButton1 = new Button(this, RGB15(12,6,12), "shi");
  normalButton1->setSize(40, 40);
  normalButton1->setLocation(58, 51);
  normalButton1->setCommand(ANSWER_1);
  normalButton1->setBorder(RGB15(0, 0, 0), 2, 31);
  normalButton1->setShadow(RGB15(0, 0, 0), 3);
  normalButton1->setTextColor(RGB15(31, 31, 31));
  normalButton1->setTextShadow(RGB15(0, 0, 0));
  normalButton1->setXOffsetForText(7);
  normalButton1->setYOffsetForText(14);
  normalPanel->add(normalButton1);
  normalButtons[0] = normalButton1;

  Button* normalButton2 = new Button(this, RGB15(6,6,12), "ka");
  normalButton2->setSize(40, 40);
  normalButton2->setLocation(108, 51);
  normalButton2->setCommand(ANSWER_2);
  normalButton2->setBorder(RGB15(0, 0, 0), 2, 31);
  normalButton2->setShadow(RGB15(0, 0, 0), 3);
  normalButton2->setTextColor(RGB15(31, 31, 31));
  normalButton2->setTextShadow(RGB15(0, 0, 0));
  normalButton2->setXOffsetForText(7);
  normalButton2->setYOffsetForText(14);
  normalPanel->add(normalButton2);
  normalButtons[1] = normalButton2;

  Button* normalButton3 = new Button(this, RGB15(6,12,12), "tsu");
  normalButton3->setSize(40, 40);
  normalButton3->setLocation(158, 51);
  normalButton3->setCommand(ANSWER_3);
  normalButton3->setBorder(RGB15(0, 0, 0), 2, 31);
  normalButton3->setShadow(RGB15(0, 0, 0), 3);
  normalButton3->setTextColor(RGB15(31, 31, 31));
  normalButton3->setTextShadow(RGB15(0, 0, 0));
  normalButton3->setXOffsetForText(7);
  normalButton3->setYOffsetForText(14);
  normalPanel->add(normalButton3);
  normalButtons[2] = normalButton3;

  Button* normalButton4 = new Button(this, RGB15(12,12,6), "ko");
  normalButton4->setSize(40, 40);
  normalButton4->setLocation(58, 101);
  normalButton4->setCommand(ANSWER_4);
  normalButton4->setBorder(RGB15(0, 0, 0), 2, 31);
  normalButton4->setShadow(RGB15(0, 0, 0), 3);
  normalButton4->setTextColor(RGB15(31, 31, 31));
  normalButton4->setTextShadow(RGB15(0, 0, 0));
  normalButton4->setXOffsetForText(7);
  normalButton4->setYOffsetForText(14);
  normalPanel->add(normalButton4);
  normalButtons[3] = normalButton4;

  Button* normalButton5 = new Button(this, RGB15(6,12,6), "ka");
  normalButton5->setSize(40, 40);
  normalButton5->setLocation(108, 101);
  normalButton5->setCommand(ANSWER_5);
  normalButton5->setBorder(RGB15(0, 0, 0), 2, 31);
  normalButton5->setShadow(RGB15(0, 0, 0), 3);
  normalButton5->setTextColor(RGB15(31, 31, 31));
  normalButton5->setTextShadow(RGB15(0, 0, 0));
  normalButton5->setXOffsetForText(7);
  normalButton5->setYOffsetForText(14);
  normalPanel->add(normalButton5);
  normalButtons[4] = normalButton5;

  Button* normalButton6 = new Button(this, RGB15(12,6,6), "tsu");
  normalButton6->setSize(40, 40);
  normalButton6->setLocation(158, 101);
  normalButton6->setCommand(ANSWER_6);
  normalButton6->setBorder(RGB15(0, 0, 0), 2, 31);
  normalButton6->setShadow(RGB15(0, 0, 0), 3);
  normalButton6->setTextColor(RGB15(31, 31, 31));
  normalButton6->setTextShadow(RGB15(0, 0, 0));
  normalButton6->setXOffsetForText(7);
  normalButton6->setYOffsetForText(14);
  normalPanel->add(normalButton6);
  normalButtons[5] = normalButton6;

  normalJokerButton = new Button(this, RGB15(31,18,0), "JOKER");
  normalJokerButton->setSize(50, 21);
  normalJokerButton->setLocation(103, 20);
  normalJokerButton->setCommand(LATER);
  normalJokerButton->setBorder(RGB15(0, 0, 0), 2, 31);
  normalJokerButton->setShadow(RGB15(0, 0, 0), 3);
  normalJokerButton->setTextColor(RGB15(31, 31, 31));
  normalJokerButton->setTextShadow(RGB15(0, 0, 0));
  normalPanel->add(normalJokerButton);

  // DIFFICULTY : EASY	
  easyPanel = new Panel(this);
  easyPanel->setSize(246, 150);
  easyPanel->setLocation(5, 5);
  easyPanel->setBackgroundColor(RGB15(31, 31, 31), 16);
  easyPanel->setBorder(RGB15(31, 6, 0), 3, 16);
  this->add(easyPanel);

  Button* easyButton1 = new Button(this, RGB15(12,6,12), "shi");
  easyButton1->setSize(50, 50);
  easyButton1->centerY(40);
  easyButton1->setCommand(ANSWER_1);
  easyButton1->setBorder(RGB15(0, 0, 0), 2, 31);
  easyButton1->setShadow(RGB15(0, 0, 0), 3);
  easyButton1->setTextColor(RGB15(31, 31, 31));
  easyButton1->setTextShadow(RGB15(0, 0, 0));
  easyButton1->setXOffsetForText(5);
  easyButton1->setYOffsetForText(20);
  easyPanel->add(easyButton1);
  easyButtons[0] = easyButton1;

  Button* easyButton2 = new Button(this, RGB15(6,6,12), "ka");
  easyButton2->setSize(50, 50);
  easyButton2->centerY(100);
  easyButton2->setCommand(ANSWER_2);
  easyButton2->setBorder(RGB15(0, 0, 0), 2, 31);
  easyButton2->setShadow(RGB15(0, 0, 0), 3);
  easyButton2->setTextColor(RGB15(31, 31, 31));
  easyButton2->setTextShadow(RGB15(0, 0, 0));
  easyButton2->setXOffsetForText(5);
  easyButton2->setYOffsetForText(20);
  easyPanel->add(easyButton2);
  easyButtons[1] = easyButton2;

  Button* easyButton3 = new Button(this, RGB15(6,12,12), "tsu");
  easyButton3->setSize(50, 50);
  easyButton3->centerY(160);
  easyButton3->setCommand(ANSWER_3);
  easyButton3->setBorder(RGB15(0, 0, 0), 2, 31);
  easyButton3->setShadow(RGB15(0, 0, 0), 3);
  easyButton3->setTextColor(RGB15(31, 31, 31));
  easyButton3->setTextShadow(RGB15(0, 0, 0));
  easyButton3->setXOffsetForText(5);
  easyButton3->setYOffsetForText(20);
  easyPanel->add(easyButton3);
  easyButtons[2] = easyButton3;

  easyJokerButton = new Button(this, RGB15(31,18,0), "JOKER");
  easyJokerButton->setSize(50, 21);
  easyJokerButton->setLocation(100, 35);
  easyJokerButton->setCommand(LATER);
  easyJokerButton->setBorder(RGB15(0, 0, 0), 2, 31);
  easyJokerButton->setShadow(RGB15(0, 0, 0), 3);
  easyJokerButton->setTextColor(RGB15(31, 31, 31));
  easyJokerButton->setTextShadow(RGB15(0, 0, 0));
  easyPanel->add(easyJokerButton);
}

GameIdeogram::~GameIdeogram() {
  delete input;
  delete keyboard;
  delete easyJokerButton;
  delete normalJokerButton;
  delete hardJokerButton;
  delete hardPanel;
  delete normalPanel;
  delete easyPanel;
}

void GameIdeogram::initScore() {
  Game::initScore();
  answersList.clear();
}

int GameIdeogram::getNumberOfGuess() {
  int level = scoreManager->getLevel(gameId);
  if (level > maxX) {
    level = maxX;
  }
  int guess = (level+1)*(this->maxY + 1);
  // HIRAGANA ou KATAKANA
  if (gameId == 0 || gameId == 1) {
    if (level <= 6) {
      return guess;
    } else if (level == 7 || level == 8) {
      return guess - 2;
    } else if (level == 9) {
      return guess - 5;
    } else {
      return guess - 9;
    }
  }
  // KANJI
  else if (gameId == 2) {
    return guess;
  }
  return 0;
}

bool GameIdeogram::isInList(std::string str, std::vector<std::string> list) {
  if (str.data() == NULL || str.at(0) == ' ') {
    return true;
  }
  for (unsigned int i = 0; i < list.size(); i++) {
    if (list.at(i).compare(str) == 0) {
      return true;
    }
  }
  return false;
}

void GameIdeogram::show() {
  // Traitement generique
  Component::show();
  
  hideRetryPanel();
  this->gameOver = false;
  
  handleDifficulty();

  initBeforeStart();
  
  // Affichage du caractere a deviner
  displayRandomChar();

  initAfterStart();
}

void GameIdeogram::handleDifficulty() {
  // Pas de mode hard pour le kanji
  if (difficulty == D_HARD && gameId == 2) {
    difficulty = D_NORMAL;
  }
  // Gestion de la difficulte
  if (difficulty == D_HARD) {
    hardPanel->show();
    normalPanel->hide();
    easyPanel->hide();
    if (!joker) {
      hardJokerButton->hide();
    }
  } else if (difficulty == D_NORMAL) {
    hardPanel->hide();
    normalPanel->show();
    easyPanel->hide();
    if (!joker) {
      normalJokerButton->hide();
    }
  } else if (difficulty == D_EASY) {
    hardPanel->hide();
    normalPanel->hide();
    easyPanel->show();
    if (!joker) {
      easyJokerButton->hide();
    }
  }
}

void* GameIdeogram::getPalette(int x, int y) {
  return NULL;
}

void* GameIdeogram::getSprite(int x, int y) {
  return NULL;
}

void GameIdeogram::displayRandomChar() {
  bool found = false;
  bool disableRandom = false;
  std::string solution;
  int level = scoreManager->getLevel(gameId);
  if (level > maxX) {
    level = maxX;
  }
  int nbTries = 0;
  char position[25];

  while (!found) {
    nbTries++;
    // Selection d'un caractere au hasard
    if (!disableRandom) {
      randomX = rand() % (level + 1);
      randomY = rand() % (maxY + 1);
    } else {
      randomX++;
      if (randomX > level) {
        randomX = 0;
        randomY++;
      }
      if (randomY > maxY) {
        break;
      }
    }

    solution = readSolution(randomX, randomY);

    // Caractere trouve?
    if (isPaletteOk()) {
      found = true;
    }

    // Caractere deja demande?  
    if (found) {
      for (unsigned int i = 0; i < answersList.size(); i++) {
        sprintf(position, "X:%d Y:%d", randomX, randomY);
        if (answersList.at(i).compare(position) == 0) {
          found = false;
        }
      }
    }

    // Si il y a un pb dans la fonction rand()
    if (nbTries >= 20 && !disableRandom) {
      disableRandom = true;
      randomX = -1;
      randomY = 0;
    }

    // Cas de l'emulateur
    if (solution.compare("emu") == 0) {
      break;
    }
  }

  // Affichage du fond contenant le caractere
  PA_DeleteSprite(SCREEN_UP, SPRITE_14);
  PA_LoadSpritePal(SCREEN_UP, PALETTE_10, (void*)window_Pal);
  PA_CreateSprite(SCREEN_UP, SPRITE_14, (void*)window_Sprite, OBJ_SIZE_64X64,
      COLOR_256, PALETTE_10, 64, 25);
  PA_SetSpriteDblsize(SCREEN_UP, SPRITE_14, 1);
  PA_SetSpriteRotEnable(SCREEN_UP, SPRITE_14, 1);
  PA_SetSpriteMode(SCREEN_UP, SPRITE_14, 1);
  PA_SetRotset(SCREEN_UP, 1, 0, 215, 215);

  // Affichage du caractere choisi
  PA_DeleteSprite(SCREEN_UP, SPRITE_13);
  PA_LoadSpritePal(SCREEN_UP, PALETTE_5, getPalette(randomX, randomY));
  PA_CreateSprite(SCREEN_UP, SPRITE_13, getSprite(randomX, randomY),
      OBJ_SIZE_64X64, COLOR_256, PALETTE_5, 96, 57);
  PA_SetSpriteRotEnable(SCREEN_UP, SPRITE_13, 2);
  PA_SetSpriteMode(SCREEN_UP, SPRITE_13, 1);
  for (int i = 20; i >= 0; i=i-2) {
    PA_SetRotsetNoAngle(SCREEN_UP, 2, 256, 256 + i*100);
    displayTime();
    PA_WaitForVBL();
  }

  // Cas de l'emulateur
  if (solution.compare("emu") == 0) {
    return;
  }

  // Choix des textes du bouton
  fillTextButtons(maxX, maxY, solution);
}

bool GameIdeogram::isPaletteOk() {
  return false;
}

void GameIdeogram::display(SCREEN scr) {

  if (visible && screen == scr) {
    if (!gameOver) {
      // Decompte non termine
      if (displayTime()) {
        // NOTHING TO DO
      }
      // Fin du temps reglementaire
      else if (!retryPanel->isVisible()) {
        tooLate();
      }
    }
  }

  // Traitement generique
  Component::display(scr);

  // Affichage des scores de la partie
  displayScore();
}

void GameIdeogram::endOfGame() {
  PA_DeleteSprite(SCREEN_UP, SPRITE_14); // WINDOW
  PA_DeleteSprite(SCREEN_UP, SPRITE_13); // HIRA-KATA-KANJI  
  easyPanel->hide();
  normalPanel->hide();
  hardPanel->hide();
  Game::endOfGame();  
}

void GameIdeogram::treatAnswer(int cmd) {

  // Comparaison de la reponse avec la solution
  computeScore(cmd);

  // Decompte des reponses restantes
  remainingGuess--;
  progressBar->increment();

  // Affichage de la progression
  displayProgressBar();

  // On reinitialise le champ de saisie
  input->clear();

  // On verifie que la partie n'est pas terminee
  if (remainingGuess == 0) {
    endOfGame();
  }
  // Affichage du caractere suivant
  else {
    displayRandomChar();
  }
}

std::string GameIdeogram::readSolution(int rndX, int rndY) {
  return NULL;
}

void GameIdeogram::computeScore(int cmd) {
  // Recuperation de la solution
  std::string solution = readSolution(randomX, randomY);

  // Memorisation de la question posee
  char position[25];
  sprintf(position, "X:%d Y:%d", randomX, randomY);
  answersList.push_back(position);

  // Petit pb : suppression des espaces lus
  if (solution.find(" ", 0) != std::string::npos) {
    solution = solution.substr(0, solution.find(" ", 0));
  }

  // Comparaison avec la reponse
  bool goodAnswer = isGoodAnswer(cmd);
  std::string answer = std::string(input->getText());

  // Bonne reponse
  if (goodAnswer) {
    scoreManager->incGoodAnswers(gameId); // GoodAnswers+1
    goodAnswers++;
    char right[3];
    if (goodAnswers > 9) {
      sprintf(right, ":%d", goodAnswers);
    } else {
      sprintf(right, ":0%d", goodAnswers);
    }
    ascii->displayString(right, 4, 1);
    ascii->displayCenteredString("GOOD JOB !", 16);
    PA_PlaySimpleSound(snd_right);
  }
  // Mauvaise reponse
  else {
    scoreManager->incBadAnswers(gameId); // BadAnswers+1
    badAnswers++;
    char wrong[3];
    if (badAnswers > 9) {
      sprintf(wrong, ":%d", badAnswers);
    } else {
      sprintf(wrong, ":0%d", badAnswers);
    }
    ascii->displayString(wrong, 26, 1);
    if (solution.size() <= 9) {
      char sSolution[9];
      sprintf(sSolution, "Answer:%s", solution.data());
      ascii->displayCenteredString(sSolution, 16);
    } else {
      ascii->displayCenteredString("BAD ANSWER !", 16);
    }

    PA_PlaySimpleSound(snd_wrong);

    // Petite pause
    for (int i = 0; i < 90; i++) {
      displayTime();
      PA_WaitForVBL();
    }

    // On efface la solution
    ascii->displayCenteredString("                ", 16);
  }
}

bool GameIdeogram::isGoodAnswer(int cmd) {

  Button** buttonsList;
  std::string answer;
  if (difficulty == D_NORMAL) {
    buttonsList = normalButtons;
    answer = std::string(buttonsList[cmd - ANSWER_1]->getText());
  } else if (difficulty == D_EASY) {
    buttonsList = easyButtons;
    answer = std::string(buttonsList[cmd - ANSWER_1]->getText());
  } else {
    answer = std::string(input->getText());
  }

  std::string solution = readSolution(randomX, randomY);

  // Bonne reponse
  if (trimr(lowerize(solution)).compare(trimr(lowerize(answer))) == 0) {
    return true;
  }
  // Mauvaise reponse
  else {
    return false;
  }
}

void GameIdeogram::fillTextButtons(int maxX, int maxY, std::string solution) {
  // Nombre de boutons
  int nbButtons = 0;
  Button** buttonsList;
  if (difficulty == D_NORMAL) {
    nbButtons = 6;
    buttonsList = normalButtons;
  } else if (difficulty == D_EASY) {
    nbButtons = 3;
    buttonsList = easyButtons;
  } else {
    return;
  }
  int rndPosition = rand() % nbButtons;
  std::vector<std::string> rndStrList;
  rndStrList.push_back(solution);

  for (int i = 0; i < nbButtons; i++) {
    if (i == rndPosition) {
      solution = capitalize(solution);
      buttonsList[i]->setText(solution.data());
    } else {
      bool found = false;
      while (!found) {
        int rndX = rand() % (maxX + 1);
        int rndY = rand() % (maxY + 1);
        std::string rndString = readSolution(rndX, rndY);
        if (!isInList(rndString, rndStrList)) {
          rndStrList.push_back(rndString);
          rndString = capitalize(rndString);
          buttonsList[i]->setText(rndString.data());
          found = true;
        }
      }
    }
  }
}

void GameIdeogram::later() {
  scoreManager->incNbPassed(gameId); // Joker+1

  // On reinitialise le champ de saisie
  input->clear();

  // Affichage du caractere suivant
  displayRandomChar();
}

int GameIdeogram::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {

    if (ul_keys.pressed.B) {
      Button* button = (Button*)this->getComponent(0, TYPE_BUTTON);
      button->press();
    } else if (ul_keys.pressed.A && retryPanel->isVisible()) {
      return RETRY;
    } else {
      int cmd = Component::dealEvent(scr);
      // Bouton back
      if (cmd == BACK) {
        if (remainingGuess > 0) {
          scoreManager->incAbortions(gameId); // Abort+1
        }
        scoreManager->writeProfiles();
        return BACK;
      }
      // Bouton retry
      else if (cmd == RETRY) {
        return RETRY;
      }
      // Boutons ANSWER
      else if (cmd >= ANSWER_1 && cmd <= ANSWER_6) {
        treatAnswer(cmd);
      }
      // Bouton JOKER
      else if (cmd == LATER) {
        later();
      }
      // Gestion clavier
      else if (cmd == KEY_DEL) {
        input->del();
      } else if (cmd == KEY_ENTER) {
        treatAnswer(cmd);
      } else if (cmd == KEY_SPACE) {
        input->addChar(' ');
      } else if (cmd >= 32 && cmd <= 126) {
        input->addChar(cmd);
      }
      return CMD_NONE;
    }
  }
  return CMD_NONE;
}
