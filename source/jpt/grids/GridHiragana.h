#ifndef __GRID_HIRAGANA_H__
#define __GRID_HIRAGANA_H__

namespace jlpt {

  class GridHiragana : public Grid {

    public:
      GridHiragana(Component* parent, char* imageName, char* imageKeyName);
      void display(SCREEN scr);
      int dealEvent(SCREEN scr);
    private:
      void displayIdeogram(int i, int j);
  };

}

#endif // __GRID_HIRAGANA_H__   
