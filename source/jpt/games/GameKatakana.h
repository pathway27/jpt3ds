#ifndef __GAMEKATAKANA_H__
#define __GAMEKATAKANA_H__

namespace jlpt {

  class GameKatakana : public GameIdeogram {

    public:
      GameKatakana(Component* parent, ScoreManager* s);
      ~GameKatakana();
      std::string readSolution(int rndX, int rndY);
      void* getPalette(int x, int y);
      void* getSprite(int x, int y);
      bool isPaletteOk();
  };
}

#endif // __GAMEKATAKANA_H__
