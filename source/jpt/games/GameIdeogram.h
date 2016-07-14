#ifndef __GAMEIDEOGRAM_H__
#define __GAMEIDEOGRAM_H__

namespace jlpt {

  class GameIdeogram : public Game {

    public:
      GameIdeogram(Component* parent, ScoreManager* s);
      ~GameIdeogram();
      int dealEvent(SCREEN scr);
      void show();
      void display(SCREEN scr);
      void initScore();
      int getNumberOfGuess();
      
    private:
      bool isInList(std::string str, std::vector<std::string> list);
      void treatAnswer(int cmd);
      void displayRandomChar();
      void computeScore(int cmd);
      void endOfGame();
      void fillTextButtons(int maxX, int maxY, std::string str);
      bool isGoodAnswer(int cmd);
      void later();
      void handleDifficulty();
      virtual std::string readSolution(int rndX, int rndY);
      virtual bool isPaletteOk();
      virtual void* getPalette(int x, int y);
      virtual void* getSprite(int x, int y);
      
    protected:
      Input* input;
      KeyboardAscii* keyboard;
      Button* easyJokerButton;
      Button* normalJokerButton;
      Button* hardJokerButton;
      Panel* easyPanel;
      Panel* normalPanel;
      Panel* hardPanel;
      Button* easyButtons[3];
      Button* normalButtons[6];
      std::vector<std::string> answersList;
      int randomX;
      int randomY;
      int maxX;
      int maxY;
  };
}

#endif // __GAMEIDEOGRAM_H__
