#ifndef __GRID_KANJI_H__
#define __GRID_KANJI_H__

namespace jlpt {

  class GridKanji : public Grid {

    public:
      GridKanji(Component* parent, char* imageName, char* imageKeyName);
      void display(SCREEN scr);      
      int dealEvent(SCREEN scr);
    private:
      void displayIdeogram(int i, int j);
      void drawIdeogram(UL_IMAGE* imgTiles, int i, int j, int x, int y,
        int level);
  };

}

#endif // __GRID_KANJI_H__
