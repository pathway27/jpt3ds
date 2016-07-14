#ifndef __MENUDIFFICULTY_H__
#define __MENUDIFFICULTY_H__

namespace jlpt {

  class MenuDifficulty : public Menu {

    public:
      MenuDifficulty(Component* parent);
      ~MenuDifficulty();
      void setCommand(int c);
      void display(SCREEN scr);
      int getDifficulty();
      int getSpeed();
      int getVocabIndex();
      bool getJoker();
      void show();
      int dealEvent(SCREEN scr);
      void hideJoker();
      void showVocabIndex();
      void hideVocabIndex();
      
    private:
      Button* goButton;
      Button* backButton;
      Ascii* fontAscii;
      List* listDifficulty;
      List* listSpeed;
      List* listVocabIndex;
      CheckBox* checkJoker;
  };
}

#endif // __MENUDIFFICULTY_H__
