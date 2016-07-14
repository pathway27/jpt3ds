#ifndef __GRID_KATAKANA_H__
#define __GRID_KATAKANA_H__

namespace jlpt {

  class GridKatakana : public Grid {

    public:
      GridKatakana(Component* parent, char* imageName, char* imageKeyName);
      void display(SCREEN scr);
      int dealEvent(SCREEN scr);
    private:
      void displayIdeogram(int i, int j);
  };

}

#endif // __GRID_KATAKANA_H__   
