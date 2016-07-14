#ifndef __APP_H__
#define __APP_H__

namespace jlpt {

  class App : public Component {
    public:
      App();
      ~App();
      int dealEvent(SCREEN scr);
      void display(SCREEN scr);
    private:
      void refreshTopScreen();
      void saveProfile();
      
    private:
      MenuStart* menuStart;
      MenuProfiles* menuProfiles;
      MenuProfile* menuProfile;
      MenuMain* menuMain;
      MenuLearn* menuLearn;
      MenuPractice* menuPractice;
      MenuDifficulty* menuDifficulty;
      MenuOptions* menuOptions;
      GameHiragana* gameHiragana;
      GameKatakana* gameKatakana;
      GameKanji* gameKanji;
      GameDraw* gameDraw;
      GameNumbers* gameNumbers;
      GameVocabulary* gameVocabulary;      
      ScoreManager* scoreManager;
      bool debugMode;
  };
}

#endif // __APP_H__
