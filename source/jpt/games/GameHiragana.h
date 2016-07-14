#ifndef __GAMEHIRAGANA_H__
#define __GAMEHIRAGANA_H__

namespace jlpt {

  class GameHiragana : public GameIdeogram {

    public:
      GameHiragana(Component* parent, ScoreManager* s);
      ~GameHiragana();
      std::string readSolution(int rndX, int rndY);
      bool isPaletteOk();
      void* getPalette(int x, int y);
      void* getSprite(int x, int y);
  };
}

#endif // __GAMEHIRAGANA_H__
