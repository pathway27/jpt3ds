#ifndef __GRID_H__
#define __GRID_H__

namespace jlpt {

  typedef enum {
    KB_NORMAL = 0,
    KB_DAKUTEN = 1,
    KB_HANDAKUTEN = 2,
    KB_KANJI_LVL4_1 = 3,
    KB_KANJI_LVL4_2 = 4,
    KB_KANJI_LVL4_3 = 5
  };

  class Grid : public Component {

    public:
      Grid(Component* parent, char* imageName, char* imageKey);
      virtual ~Grid();
      virtual void hide();
      virtual void show();
      virtual void displayIdeogram(int i, int j);
      virtual void drawIdeogram(UL_IMAGE* imgTiles, int i, int j, int x, int y, int level);
      void setScoreManager(ScoreManager* s);
      void displayUnlockMessage(char* sentence);
      
    protected:
      int keyboardMode;
      UL_IMAGE* imgTiles;
      UL_IMAGE* imgKey;
      UL_IMAGE* imgUnknown;
      Point* selectedItem;
      ScoreManager* scoreManager;
    private:
      char* imageName;
      char* imageKeyName;
  };

}

#endif // __GRID_H__
