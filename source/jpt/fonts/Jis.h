#ifndef __JIS_H__
#define __JIS_H__

namespace jlpt {

  class Jis {

    public:
      Jis(int screen, int bgLayer);
      void displayJapaneseString(const u16* str, int x, int y);
    private:
      void displayJapaneseChar(u16 numChar, int x, int y);
      u16 getCharNumber(u16 numChar);

    private:
      int screen;
      int bgLayer;
  };
}

#endif // __JIS_H__
