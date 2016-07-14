#ifndef __PROGRESSBAR_H__
#define __PROGRESSBAR_H__

namespace jlpt {

  class ProgressBar {
    public:
      ProgressBar(int max);
      virtual ~ProgressBar();
      void setLocation(int x, int y);
      void increment();
      void display();
      void reset();
      void deleteSprites();
      void createSprites(bool wait);
      void init();
      void setMaxValue(int max);
      int getCurrentValue();
      
    private:
      Point* location;
      int maxValue;
      int currentValue;
      int nbSprites;
      int startSpriteNumber;
  };

}

#endif // __PROGRESSBAR_H__
