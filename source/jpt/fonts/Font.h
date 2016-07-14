#ifndef __FONT_H__
#define __FONT_H__

#define PIXEL_SIZE_10 10
#define FONT_FILENAME "/JLPT4/SEVEMFBR.TTF"

namespace jlpt {

  class Font {

    public:
      Font();
      void drawChar(u16 code);
      void drawString(const char *string);
      u8 GetUCS(const char *txt, u16 *code);
      
    private:
      FT_Library library;
      FT_Face face;
      FT_Vector pen;
      u16  *screen;
  };
}

#endif // __FONT_H__
