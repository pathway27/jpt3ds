#include <PA9.h>
#include "snd_right.h"
#include "snd_wrong.h"
#include "snd_back.h"
#include <ulib/ulib.h>
#include <vector>
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"
#include "../geometry/Dimension.h"
#include "../fonts/Ascii.h"
#include "../components/Component.h"
#include "../components/Panel.h"
#include "../components/ProgressBar.h"
#include "../scores/ScoreManager.h"
#include "../Tools.h"
#include "../Commands.h"
#include "../components/TextComponent.h"
#include "../components/Button.h"
#include "../components/Image.h"
#include "../files/File.h"
#include "../files/FileReader.h"
#include "Game.h"
#include "GameVocabulary.h"

using namespace jlpt;

GameVocabulary::GameVocabulary(Component* parent, ScoreManager* s) :
  Game(parent, s) {
  
  this->gameId = 3;
  this->maxLevel = 50;
  this->vocabIndex = 0;
  
  // Barre de progression
  createProgressBar();

  // Voulez-vous rejouer?
  createRetryPanel();
  
  // DIFFICULTY  
  panel = new Panel(this);
  panel->setSize(246, 150);
  panel->setLocation(5, 5);
  panel->setBackgroundColor(RGB15(31, 31, 31), 16);
  panel->setBorder(RGB15(31, 6, 0), 3, 16);
  this->add(panel);

  jokerButton = new Button(this, RGB15(31,18,0), "JOKER");
  jokerButton->setSize(50, 21);
  jokerButton->setLocation(100, 15);
  jokerButton->setCommand(LATER);
  jokerButton->setBorder(RGB15(0, 0, 0), 2, 31);
  jokerButton->setShadow(RGB15(0, 0, 0), 3);
  jokerButton->setTextColor(RGB15(31, 31, 31));
  jokerButton->setTextShadow(RGB15(0, 0, 0));
  panel->add(jokerButton);
  
  Button* button1 = new Button(this, RGB15(12,6,12), "shi");
  button1->setSize(210, 21);
  button1->centerX(47);
  button1->setCommand(ANSWER_1);
  button1->setBorder(RGB15(0, 0, 0), 2, 31);
  button1->setShadow(RGB15(0, 0, 0), 3);
  button1->setTextColor(RGB15(31, 31, 31));
  button1->setTextShadow(RGB15(0, 0, 0));
  panel->add(button1);
  buttons[0] = button1;

  Button* button2 = new Button(this, RGB15(6,6,12), "ka");
  button2->setSize(210, 21);
  button2->centerX(81);
  button2->setCommand(ANSWER_2);
  button2->setBorder(RGB15(0, 0, 0), 2, 31);
  button2->setShadow(RGB15(0, 0, 0), 3);
  button2->setTextColor(RGB15(31, 31, 31));
  button2->setTextShadow(RGB15(0, 0, 0));
  panel->add(button2);
  buttons[1] = button2;

  Button* button3 = new Button(this, RGB15(6,12,12), "tsu");
  button3->setSize(210, 21);
  button3->centerX(115);
  button3->setCommand(ANSWER_3);
  button3->setBorder(RGB15(0, 0, 0), 2, 31);
  button3->setShadow(RGB15(0, 0, 0), 3);
  button3->setTextColor(RGB15(31, 31, 31));
  button3->setTextShadow(RGB15(0, 0, 0));
  panel->add(button3);
  buttons[2] = button3;

  readIndex();
}

GameVocabulary::~GameVocabulary() {
}

void GameVocabulary::setVocabIndex(int vocabIndex) {
  this->vocabIndex = vocabIndex;
}

void GameVocabulary::loadBgTopScreen() {
  PA_LoadTiledBg(SCREEN_UP, BG_3, bg_top_game_vocab);
}

void GameVocabulary::readIndex() {
  // Ouverture de l'index
  std::string filePath = getFilePath("vocabulary_index.txt", scoreManager);
  FileReader* fileReader = new FileReader(filePath.c_str(), ASCII);
  fileReader->open("r");
    
  char temp[10];
  for(int i = 0; i < 51; i++) {    
    if(fileReader->get(temp , 10) != NULL) {
      vocabIndexes[i] = atoi(temp);
    } else {
      vocabIndexes[i] = 0;
    }
  }
  
  // Fermeture de l'index
  fileReader->close();
}

void GameVocabulary::displayRandomVocab() {
  bool found = false;
  bool disableRandom = false;
  std::string solution;
  int level = this->vocabIndex; 
  int nbTries = 0;
  char position[25];
  
  while (!found) {
    nbTries++;
    
    // Selection d'un caractere au hasard
    if (!disableRandom) {
      randomX = rand() % (vocabIndexes[level+1] - vocabIndexes[level]);
      randomX = randomX + vocabIndexes[level];
    } else {
      randomX++;
      if (randomX >= vocabIndexes[level+1]) {
        randomX = vocabIndexes[level];
      }
    }

    solution = readSolution(randomX);

    if (!solution.empty() && solution.compare("emu") != 0) {
      found = true;
    }
        
    // Vocabulaire deja demande?  
    for (unsigned int i = 0; i < answersList.size(); i++) {
      sprintf(position, "X:%d", randomX);
      if (answersList.at(i).compare(position) == 0) {
        found = false;
        break;
      }
    }

    // Si il y a un pb dans la fonction rand()
    if (nbTries >= 20 && !disableRandom && !found) {
      disableRandom = true;
      randomX = vocabIndexes[level] - 1;
    }
  }
  
  PA_16cErase(SCREEN_UP);

  // Affichage du vocabulaire choisi
  std::string question = readQuestion(randomX);
  
  PA_16cText(SCREEN_UP, 30, 55, SCREEN_WIDTH - 20, SCREEN_HEIGHT,
          (char*)question.data(), BLACK, SIZE_2, 100);

  // Cas de l'emulateur
  if (solution.compare("emu") == 0) {
    return;
  }

  // Choix des textes du bouton
  fillTextButtons(solution);
}

void GameVocabulary::fillTextButtons(std::string solution) {
  // Nombre de boutons
  int nbButtons = 3;

  int rndPosition = rand() % nbButtons;
  std::vector<std::string> rndStrList;
  rndStrList.push_back(solution);

  for (int i = 0; i < nbButtons; i++) {
    if (i == rndPosition) {
      solution = capitalize(solution);
      buttons[i]->setText(trimr(solution).data());
    } else {
      bool found = false;
      int level = this->vocabIndex;
      int indexMin = vocabIndexes[level];
      int indexMax = vocabIndexes[level+1];
      while (!found) {
        int rndX = rand() % (indexMax-indexMin);
        rndX = rndX + indexMin;
        std::string rndString = readSolution(rndX);
        if (!isInList(rndString, rndStrList)) {
          rndStrList.push_back(rndString);
          rndString = capitalize(rndString);
          buttons[i]->setText(trimr(rndString).data());
          found = true;
        }
      }
    }
  }
}

bool GameVocabulary::isInList(std::string str, std::vector<std::string> list) {
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

std::string GameVocabulary::readSolution(int rndX) {
  VOCAB_DATA data;
  std::string filePath = getFilePath("vocabulary_simple.txt", scoreManager);
  FileReader* fileReader = new FileReader(filePath.c_str(), UNICODE);
  fileReader->open("rb");
  if (fileReader->exists()) {
    fileReader->seek(rndX*sizeof(data));
    fileReader->read(&data, sizeof(data), 1);
    fileReader->close();
    return std::string(fileReader->getAscii(data.romanji, 40));
  }
  return std::string("emu");
}

std::string GameVocabulary::readQuestion(int rndX) {
  VOCAB_DATA data;
  std::string filePath = getFilePath("vocabulary_simple.txt", scoreManager);
  FileReader* fileReader = new FileReader(filePath.c_str(), UNICODE);
  fileReader->open("rb");
  if (fileReader->exists()) {
    fileReader->seek(rndX*sizeof(data));
    fileReader->read(&data, sizeof(data), 1);
    fileReader->close();
    return std::string(fileReader->getAscii(data.meaning, 180));
  }
  return std::string("emu");
}

void GameVocabulary::computeScore(int cmd) {
  // Recuperation de la solution
  std::string solution = readSolution(randomX);

  // Memorisation de la question posee
  char position[25];
  sprintf(position, "X:%d", randomX);
  answersList.push_back(position);

  // Petit pb : suppression des espaces lus
  if (solution.find(" ", 0) != std::string::npos) {
    solution = solution.substr(0, solution.find(" ", 0));
  }

  // Comparaison avec la reponse
  bool goodAnswer = isGoodAnswer(cmd);

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

bool GameVocabulary::isGoodAnswer(int cmd) {

  std::string answer = std::string(buttons[cmd - ANSWER_1]->getText());
  std::string solution = readSolution(randomX);

  // Bonne reponse
  if (trimr(lowerize(solution)).compare(trimr(lowerize(answer))) == 0) {
    return true;
  }
  // Mauvaise reponse
  else {
    return false;
  }
}

void GameVocabulary::initScore() {
  Game::initScore();
  answersList.clear();
}

int GameVocabulary::getNumberOfGuess() {
  int level = this->vocabIndex;
  return vocabIndexes[level+1] - vocabIndexes[level];
}

void GameVocabulary::show() {
  // Traitement generique
  Component::show();
  
  hideRetryPanel();
  
  this->gameOver = false;
  
  handleDifficulty();

  initBeforeStart();
  
  // Affichage du vocabulaire a deviner
  displayRandomVocab();

  initAfterStart();
}

void GameVocabulary::handleDifficulty() {
  panel->show();
  if (!joker) {
    jokerButton->hide();
  }
}

void GameVocabulary::endOfGame() {
  panel->hide();
  Game::endOfGame();  
}

void GameVocabulary::display(SCREEN scr) {

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

void GameVocabulary::treatAnswer(int cmd) {

  // Comparaison de la reponse avec la solution
  computeScore(cmd);

  // Decompte des reponses restantes
  remainingGuess--;
  progressBar->increment();

  // Affichage de la progression
  displayProgressBar();

  // On verifie que la partie n'est pas terminee
  if (remainingGuess == 0) {
    endOfGame();
  }
  // Affichage du vocabulaire suivant
  else {
    displayRandomVocab();
  }
}

void GameVocabulary::later() {
  scoreManager->incNbPassed(gameId); // Joker+1

  // Affichage du caractere suivant
  displayRandomVocab();
}

int GameVocabulary::dealEvent(SCREEN scr) {
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
      else if (cmd >= ANSWER_1 && cmd <= ANSWER_3) {
        treatAnswer(cmd);
      }
      // Bouton JOKER
      else if (cmd == LATER) {
        later();
      }
      return CMD_NONE;
    }
  }
  return CMD_NONE;
}
