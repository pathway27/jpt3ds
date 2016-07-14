#ifndef __GAMEVOCABULARY_H__
#define __GAMEVOCABULARY_H__

namespace jlpt {

  class GameVocabulary : public Game {
    public:
      GameVocabulary(Component* parent, ScoreManager* s);
      virtual ~GameVocabulary();
      int dealEvent(SCREEN scr);
      void later();
      void treatAnswer(int cmd);
      void display(SCREEN scr);
      void handleDifficulty();
      void initScore();
      int getNumberOfGuess();
      void endOfGame();;
      void show();
      void displayRandomVocab();
      void computeScore(int cmd);
      void readIndex();
      std::string readSolution(int rndX);
      std::string readQuestion(int rndX);
      void fillTextButtons(std::string solution);
      bool isInList(std::string str, std::vector<std::string> list);
      bool isGoodAnswer(int cmd);
      void loadBgTopScreen();
      void setVocabIndex(int vocabIndex);
      
    private:
      Button* jokerButton;
      Button* buttons[3];
      Panel* panel;
      std::vector<std::string> answersList;
      int randomX;
      int vocabIndexes[51];
      int vocabIndex;
  };

}

#endif // __GAMEVOCABULARY_H__
