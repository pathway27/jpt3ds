#ifndef __GAMENUMBERS_H__
#define __GAMENUMBERS_H__

namespace jlpt {

  class GameNumbers : public Game {
    public:
      GameNumbers(Component* parent, ScoreManager* s);
      virtual ~GameNumbers();
      void show();
      void display(SCREEN scr);
      int getNumberOfGuess();
      void showRetryPanel();
      
    private:
      KeyboardJis* keyboardJis;
  };

}

#endif // __GAMENUMBERS_H__
