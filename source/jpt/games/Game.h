#ifndef __GAME_H__
#define __GAME_H__

namespace jlpt {

	typedef enum {
		D_EASY = 0,
		D_NORMAL = 1,
		D_HARD = 2 
	} DIFFICULTY;

	typedef enum {
		S_SLOW = 0,
		S_NORMAL = 1,
		S_FAST = 2 
	} SPEED;

	class Game : public Component {

		public:
		  // Constructeur/Destructeur
			Game(Component* parent, ScoreManager* s);
			~Game();
			// Gestion des scores
			ScoreManager* getScoreManager();
			void setScoreManager(ScoreManager* s);
      virtual void initScore();
      void saveScore();
			void displayScore();
      // Gestion du temps
      void initTime();
      void setRemainingTime(s8 min, s8 sec);
      bool displayTime();
      // Gestion de la progression
      void createProgressBar();
      void displayProgressBar();
      void comingSoon();
      void setDifficulty(int d);
      void setSpeed(int s);
      void setJoker(bool j);
      void animateCountdown();
      void animateStart(void* palette, void* sprite);
      void createBackButton();
      void createRetryPanel();
      void hideRetryPanel();
      virtual void showRetryPanel();
      virtual int getNumberOfGuess();
      void initBeforeStart();
      void initAfterStart();
      virtual void endOfGame();
      void tooLate();
      virtual void loadBgTopScreen();
      
		protected:
		   ScoreManager* scoreManager;
       ProgressBar* progressBar;
       Panel* retryPanel;
       Ascii* ascii;
       UL_COLOR textColor;
       UL_COLOR shadowColor;
       int gameId;
		   int maxLevel;
	     int difficulty;
	     int speed;
	     bool joker;
	     int numberOfGuess;
	     int goodAnswers;
	     int badAnswers;
	     int remainingGuess;
	     bool gameOver;
	     char* scoreText;
       s8 minutes;
       s8 seconds;
	};
}

#endif // __GAME_H__
