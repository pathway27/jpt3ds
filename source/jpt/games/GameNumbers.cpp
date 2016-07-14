#include <PA9.h>
#include "snd_back.h"
#include <ulib/ulib.h>
#include <vector>
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"
#include "../geometry/Dimension.h"
#include "../fonts/Ascii.h"
#include "../components/Component.h"
#include "../components/ProgressBar.h"
#include "../components/Panel.h"
#include "../components/Keyboard.h"
#include "../components/KeyboardJis.h"
#include "../scores/ScoreManager.h"
#include "../Tools.h"
#include "../Commands.h"
#include "../components/TextComponent.h"
#include "../components/Button.h"
#include "../components/Image.h"
#include "Game.h"
#include "GameNumbers.h"

using namespace jlpt;

GameNumbers::GameNumbers(Component* parent, ScoreManager* s) :
  Game(parent, s) {
  this->gameId = 7;
  this->maxLevel = 16;
  
  // Barre de progression
  createProgressBar();

  // Voulez-vous rejouer?
  createRetryPanel();
  
  // Le clavier
  keyboardJis = new KeyboardJis(this);
  keyboardJis->centerX(65);
  this->add(keyboardJis);
}

GameNumbers::~GameNumbers() {
  delete keyboardJis;
}

int GameNumbers::getNumberOfGuess() {
  return 3;
}

void GameNumbers::show() {
  // Traitement generique
  Component::show();
  
  hideRetryPanel();
  this->gameOver = false;

  initBeforeStart();
  keyboardJis->show();
  initAfterStart();
}

void GameNumbers::showRetryPanel() {
  keyboardJis->hide();
  Game::showRetryPanel();
}

void GameNumbers::display(SCREEN scr) {

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
