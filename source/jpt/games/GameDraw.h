#ifndef __GAMEDRAW_H__
#define __GAMEDRAW_H__

namespace jlpt {

  class GameDraw : public Game {
    public:
      GameDraw(Component* parent, ScoreManager* s);
      virtual ~GameDraw();
      int dealEvent(SCREEN scr);
    
    protected:
      DrawComponent* dc;
  };
}

#endif // __GAMEDRAW_H__
