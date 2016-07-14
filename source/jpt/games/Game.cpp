#include <PA9.h>
#include "snd_back.h"
#include <ulib/ulib.h>
#include <vector>
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"
#include "../geometry/Dimension.h"
#include "../fonts/Ascii.h"
#include "../components/Component.h"
#include "../Tools.h"
#include "../Commands.h"
#include "../components/Panel.h"
#include "../components/ProgressBar.h"
#include "../components/TextComponent.h"
#include "../components/Button.h"
#include "../components/Image.h"
#include "../scores/ScoreManager.h"
#include "Game.h"

using namespace jlpt;

Game::Game(Component* parent, ScoreManager* s) :
  Component(parent) {
  type = TYPE_GAME;
  gameId = -1;
  this->scoreManager = s;
  this->gameOver = false;
  this->retryPanel = NULL;
  this->scoreText = NULL;
  this->minutes = 0;
  this->seconds = 0;

  // Couleurs
  this->textColor = RGB15(0, 0, 0);
  this->shadowColor = RGB15(15, 15, 15);

  // Retour
  createBackButton();
}

Game::~Game() {
  delete ascii;
  delete retryPanel;
  delete progressBar;
  delete scoreText;
}

ScoreManager* Game::getScoreManager() {
  return scoreManager;
}

void Game::setScoreManager(ScoreManager* s) {
  scoreManager = s;
}

void Game::initScore() {
  goodAnswers = 0;
  badAnswers = 0;
  numberOfGuess = getNumberOfGuess();
  remainingGuess = numberOfGuess;
  progressBar->setMaxValue(numberOfGuess);
}

void Game::saveScore() {
  scoreManager->writeProfiles();
}

void Game::comingSoon() {
  Panel* infoPanel = new Panel(this);
  infoPanel->setSize(226, 40);
  infoPanel->setLocation(15, 76);
  infoPanel->setBackgroundColor(RGB15(31, 31, 31), 16);
  infoPanel->setBorder(RGB15(31, 0, 0), 2, 16);
  this->add(infoPanel);

  TextComponent* comingNextLabel = new TextComponent(this, "Coming soon...");
  comingNextLabel->setTextShadow(RGB15(15, 15, 15));
  comingNextLabel->centerX(80);
  this->add(comingNextLabel);
}

void Game::setDifficulty(int d) {
  this->difficulty = d;
}

void Game::setSpeed(int s) {
  this->speed = s;
}

void Game::setJoker(bool j) {
  this->joker = j;
}

int Game::getNumberOfGuess() {
  return 0;
}

void Game::createProgressBar() {
  // Barre de progression
  this->progressBar = new ProgressBar(0);
  this->progressBar->setLocation(28, 160);
}

void Game::createRetryPanel() {
  retryPanel = new Panel(this);
  retryPanel->setSize(246, 150);
  retryPanel->setLocation(5, 5);
  retryPanel->setBackgroundColor(RGB15(31, 31, 31), 16);
  retryPanel->setBorder(RGB15(31, 6, 0), 3, 16);
  this->add(retryPanel);

  Button* m_btn_retry = new Button(retryPanel, RGB15(31,0,0), "RETRY?");
  m_btn_retry->setSize(70, 21);
  m_btn_retry->setLocation(91, 155);
  m_btn_retry->setCommand(RETRY);
  m_btn_retry->setBorder(RGB15(0, 0, 0), 2, 31);
  m_btn_retry->setShadow(RGB15(0, 0, 0), 3);
  m_btn_retry->setTextColor(RGB15(31, 31, 31));
  m_btn_retry->setTextShadow(RGB15(0, 0, 0));
  m_btn_retry->hide();
  retryPanel->add(m_btn_retry);
}

void Game::createBackButton() {
  Button* backButton = new Button(this, RGB15(13,13,13), "BACK");
  backButton->setSize(80, 21);
  backButton->setLocation(171, 160);
  backButton->setCommand(BACK);
  backButton->setBorder(RGB15(0, 0, 0), 2, 31);
  backButton->setShadow(RGB15(0, 0, 0), 3);
  backButton->setTextColor(RGB15(31, 31, 31));
  backButton->setTextShadow(RGB15(0, 0, 0));
  backButton->setSound(snd_back, (u32)snd_back_size);
  this->add(backButton);

  Image* backImage = new Image(backButton, "bt_back.gif");
  backImage->setLocation(5, 5);
  backButton->add(backImage);
}

void Game::animateCountdown() {
  // 3
  animateStart((void*)text_3_Pal, (void*)text_3_Sprite);

  // 2
  animateStart((void*)text_2_Pal, (void*)text_2_Sprite);

  // 1
  animateStart((void*)text_1_Pal, (void*)text_1_Sprite);
}

void Game::animateStart(void* palette, void* sprite) {
  PA_LoadSpritePal(SCREEN_UP, PALETTE_0, (void*)palette);
  PA_CreateSprite(SCREEN_UP, SPRITE_0, (void*)sprite, OBJ_SIZE_64X64,
      COLOR_256, PALETTE_0, 60, 32);
  PA_SetSpriteDblsize(SCREEN_UP, SPRITE_0, 1);
  PA_SetSpriteRotEnable(SCREEN_UP, SPRITE_0, 0);
  PA_SetSpriteMode(SCREEN_UP, SPRITE_0, 1);
  PA_EnableSpecialFx(SCREEN_UP, SFX_ALPHA, 0, SFX_BG0 | SFX_BG1 | SFX_BG2
      | SFX_BG3);
  int angle = 256;
  int zoom = 0;
  int transparency = 0;
  for (int i = 0; i < 384; i=i+10) {
    if (angle> 0) {
      angle = angle - 20;
    }
    zoom = 512 - i;
    transparency = 16 - (i/24 + 1);
    PA_SetSFXAlpha(SCREEN_UP, 16, transparency);
    PA_SetRotset(SCREEN_UP, 0, angle, zoom, zoom);
    PA_WaitForVBL();
  }
  PA_DisableSpecialFx(SCREEN_UP);
  PA_DeleteSprite(SCREEN_UP, SPRITE_0);
}

void Game::initTime() {
  int time = numberOfGuess;
  // Gestion de la vitesse
  if (speed == S_SLOW) {
    time *= 9;
  } else if (speed == S_NORMAL) {
    time *= 6;
  } else if (speed == S_FAST) {
    time *= 3;
  }
  int minutes = time/60;
  int seconds = time - minutes*60;
  setRemainingTime(minutes, seconds);
}

void Game::setRemainingTime(s8 min, s8 sec) {
  this->minutes = min;
  this->seconds = sec;
}

bool Game::displayTime() {
  s8 min = (minutes*60 + seconds - PA_VBLCounter[0]/60)/60;
  s8 sec = (minutes*60 + seconds - PA_VBLCounter[0]/60) - 60*min;

  // Decompte non termine
  if (min >= 0 && sec >= 0) {
    char sMinutes[3];
    if (min < 10) {
      sprintf(sMinutes, "0%d:", min);
    } else {
      sprintf(sMinutes, "%d:", min);
    }
    ascii->displayString(sMinutes, 11, 3);
    char sSeconds[3];
    if (sec < 10) {
      sprintf(sSeconds, "0%d", sec);
    } else {
      sprintf(sSeconds, "%d", sec);
    }
    ascii->displayString(sSeconds, 17, 3);
    return true;
  }
  return false;
}

void Game::displayProgressBar() {
  if (ascii != NULL && progressBar != NULL) {
    char progress[5];
    sprintf(progress, "%d/%d", progressBar->getCurrentValue(), numberOfGuess);
    ascii->displayCenteredString(progress, 18);
    progressBar->display();
  }
}

void Game::displayScore() {
  if (retryPanel->isVisible()) {
    RECORDS record = scoreManager->getSelectedRecord();
    char txt[25];

    drawShadowedText("Level reached : ", 25, 20, textColor, shadowColor);
    if (nbFrame > 30 && scoreText != NULL) {
      drawShadowedText(scoreManager->getGameLevel(gameId), 120, 20, textColor,
          shadowColor);
      ascii->displayCenteredString(scoreText, 13);
    } else {
      ascii->displayCenteredString("               ", 13);
    }

    sprintf(txt, "Games played : %d", record.nbGames[gameId]);
    drawShadowedText(txt, 25, 35, textColor, shadowColor);

    sprintf(txt, "Perfects : %d", record.perfects[gameId]);
    drawShadowedText(txt, 25, 50, textColor, shadowColor);

    sprintf(txt, "Good answers : %d", record.goodAnswers[gameId]);
    drawShadowedText(txt, 25, 65, textColor, shadowColor);

    sprintf(txt, "Bad answers : %d", record.badAnswers[gameId]);
    drawShadowedText(txt, 25, 80, textColor, shadowColor);

    sprintf(txt, "Jokers used : %d", record.nbPassed[gameId]);
    drawShadowedText(txt, 25, 95, textColor, shadowColor);

    sprintf(txt, "Games unfinished : %d", record.nbEndOfTime[gameId]);
    drawShadowedText(txt, 25, 110, textColor, shadowColor);

    sprintf(txt, "Games aborted : %d", record.nbAbortions[gameId]);
    drawShadowedText(txt, 25, 125, textColor, shadowColor);
  }
}

void Game::showRetryPanel() {
  if (retryPanel != NULL) {
    retryPanel->show();
  }
}

void Game::hideRetryPanel() {
  if (retryPanel != NULL) {
    retryPanel->hide();
  }
}

void Game::initBeforeStart() {

  // Reinitialisation des scores
  initScore();
  if (scoreManager != NULL) {
    scoreManager->incNbGames(gameId); // NbGames+1
  }

  // Gestion de la vitesse
  initTime();

  // Reinitialisation du systeme de sprites
  PA_ResetSpriteSysScreen(SCREEN_UP);

  // Reinitialisation des fonds d'ecrans
  PA_ResetBgSysScreen(SCREEN_UP);

  // Initialisation du fond reserve au texte
  PA_Init16cBg(SCREEN_UP, BG_0);
  
  // Fond d'ecran superieur
  loadBgTopScreen();

  // Texte
  ascii = new Ascii(SCREEN_UP, BG_2);

  // 3,2,1
  animateCountdown();

  // Progress bar
  if (progressBar != NULL) {
    progressBar->init();
  }

  // Temps restant
  PA_LoadSpritePal(SCREEN_UP, PALETTE_4, (void*)clock_Pal);
  PA_CreateSprite(SCREEN_UP, SPRITE_12, (void*)clock_Sprite, OBJ_SIZE_32X32,
      COLOR_256, PALETTE_4, 112, 0);

  // Bonnes reponses
  PA_LoadSpritePal(SCREEN_UP, PALETTE_2, (void*)answer_right_Pal);
  PA_CreateSprite(SCREEN_UP, SPRITE_10, (void*)answer_right_Sprite,
      OBJ_SIZE_32X32, COLOR_256, PALETTE_2, 0, 0);
  if (ascii != NULL) {
    char right[3];
    sprintf(right, ":0%d", goodAnswers);
    ascii->displayString(right, 4, 1);
  }

  // Mauvaises reponses
  PA_LoadSpritePal(SCREEN_UP, PALETTE_3, (void*)answer_wrong_Pal);
  PA_CreateSprite(SCREEN_UP, SPRITE_11, (void*)answer_wrong_Sprite,
      OBJ_SIZE_32X32, COLOR_256, PALETTE_3, 176, 0);
  if (ascii != NULL) {
    char wrong[3];
    sprintf(wrong, ":0%d", badAnswers);
    ascii->displayString(wrong, 26, 1);
  }
}

void Game::loadBgTopScreen() {
  PA_LoadTiledBg(SCREEN_UP, BG_3, bg_top_screen_game);
}

void Game::initAfterStart() {
  // Affichage de la progressbar
  displayProgressBar();

  // Timer
  PA_VBLCounterStart(0);
}

void Game::endOfGame() {
  gameOver = true;
  int pourcent = (goodAnswers*100)/numberOfGuess;
  if (pourcent == 100) {
    scoreText = "PERFECT!!!";
    scoreManager->incPerfects(gameId); // NbPerfect+1
    scoreManager->incLevel(gameId, maxLevel); // Level+1
  } else if (pourcent >= 90) {
    scoreText = "WONDERFULL!!";
  } else if (pourcent >= 80) {
    scoreText = "VERY GOOD!";
  } else if (pourcent >= 70) {
    scoreText = "GOOD";
  } else if (pourcent >= 60) {
    scoreText = "NOT BAD";
  } else if (pourcent >= 50) {
    scoreText = "NOT TOO BAD";
  } else if (pourcent >= 40) {
    scoreText = "OK";
  } else if (pourcent >= 30) {
    scoreText = "NOT OK";
  } else if (pourcent >= 20) {
    scoreText = "BAD";
  } else if (pourcent >= 10) {
    scoreText = "VERY BAD";
  } else {
    scoreText = "AWFULL";
  }
  // Nettoyage de l'ecran
  PA_16cErase(SCREEN_UP);
  // Affichage du score
  ascii->displayCenteredString("YOUR SCORE :", 10);
  // On efface les messages Good job/Bad answer
  ascii->displayCenteredString("               ", 16);

  PA_VBLCounterPause(0);

  showRetryPanel();

  // Enregistrement des scores
  saveScore();
}

void Game::tooLate() {
  scoreManager->incNbEndOfTime(gameId); // EndOfTime+1
  badAnswers += remainingGuess;
  remainingGuess = 0;
  ascii->displayCenteredString("TIME IS UP !", 7);
  char sBadAnswers[3];
  if (badAnswers < 10) {
    sprintf(sBadAnswers, ":0%d  ", badAnswers);
  } else {
    sprintf(sBadAnswers, ":%d  ", badAnswers);
  }
  ascii->displayString(sBadAnswers, 26, 1);
  endOfGame();
}
