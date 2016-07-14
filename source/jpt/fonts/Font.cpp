#include <ft2build.h>
#include FT_FREETYPE_H
#include <PA9.h>
#include <ulib/ulib.h>
#include <vector>
#include "../../gfx/all_gfx.h"
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"
#include "../geometry/Dimension.h"
#include "../components/Component.h"
#include "../Tools.h"
#include "Font.h"

using namespace jlpt;

Font::Font() {
  FT_Init_FreeType(&library);
  FT_New_Face(library, FONT_FILENAME, 0, &face);
  FT_Select_Charmap(face, FT_ENCODING_NONE);
  FT_Set_Pixel_Sizes(face, 0, PIXEL_SIZE_10);
  screen = (u16*)BG_BMP_RAM_SUB(0);
  pen.x = 12;
  pen.y = 10 + (face->size->metrics.height >> 6);
}   

void Font::drawString(const char *string) {
  u8 i;
  for (i=0;i<strlen((char *)string);i++) {
    u16 c = string[i];
    //if (c == '\n') PrintNewLine();
    //else {
      if (c > 127) {
        /** this guy is multibyte UTF-8. **/
        i+=GetUCS(&(string[i]),&c);
        i--;
      }
      drawChar(c);
    //}
  }
}

u8 Font::GetUCS(const char *txt, u16 *code) {
  if (txt[0] > 0xc1 && txt[0] < 0xe0) {
    *code = ((txt[0]-192)*64) + (txt[1]-128);
    return 2;

  } else if (txt[0] > 0xdf && txt[0] < 0xf0) {
    *code = (txt[0]-224)*4096 + (txt[1]-128)*64 + (txt[2]-128);
    return 3;

  } else if (txt[0] > 0xef) {
    return 4;

  }
  *code = txt[0];
  return 1;
}

void Font::drawChar(u16 code) {
  FT_Load_Char(face, code, FT_LOAD_RENDER | FT_LOAD_TARGET_NORMAL);
  FT_GlyphSlot glyph = face->glyph;
  FT_Bitmap bitmap = glyph->bitmap;
  bool invert = false;
  
  u16 bx = glyph->bitmap_left;
  u16 by = glyph->bitmap_top;
  u16 gx, gy;
  for (gy=0; gy<bitmap.rows; gy++) {
    for (gx=0; gx<bitmap.width; gx++) {
      /* get antialiased value */
      u16 a = bitmap.buffer[gy*bitmap.width+gx];
      if (a) {
        u16 sx = (pen.x+gx+bx);
        u16 sy = (pen.y+gy-by);
        int l;
        if (invert) l = a >> 3;
        else l = (255-a) >> 3;
        screen[sy*SCREEN_WIDTH+sx] = RGB15(l,l,l) | BIT(15);
      }
    }
  }
  pen.x += glyph->advance.x >> 6;
}
