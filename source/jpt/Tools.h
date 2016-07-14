#ifndef __TOOLS_H__
#define __TOOLS_H__

#include "checked.h"
#include "unknown.h"
#include "kanji.h"
#include "kanas.h"
#include "bg_bottom_screen.h"
#include "panel_title.h"
#include "panel_title_1.h"
#include "panel_title_2.h"
#include "panel_title_3.h"
#include "panel_title_4.h"
#include "key_1.h"
#include "key_2.h"
#include "key_3.h"
#include "key_4.h"
#include "bt_back.h"
#include "bt_up.h"
#include "bt_down.h"
#include "bt_left.h"
#include "bt_right.h"
#include "bt_hira.h"
#include "bt_kata.h"
#include "bt_kanji.h"
#include "bt_numbers.h"
#include "bt_draw.h"
#include "bt_vocab.h"
#include "keyboard_del.h"
#include "keyboard_caps.h"
#include "keyboard_shift.h"
#include "keyboard_enter.h"
#include "keyboard_space.h"
#include "menu_hand.h"
#include "title_profile.h"
#include "title_name.h"
#include "title_difficulty.h"
#include "title_options.h"
#include "font_ascii.h"
#include "../gfx/all_gfx.h"
#include <string>
#include "scores/ScoreManager.h"

static const unsigned int NB_JIS_KEYS = 15;
static const unsigned int POINTS_PER_STROKE = 32;
static const unsigned int STROKE_PER_GESTURE = 30;

typedef struct _KANA_DATA_ {
    char syllabus[10];
    char sampleRomanji[50];
    char sampleTranslated[120];
    char sampleKana[18];
} KANA_DATA, *pKANA_DATA;

typedef struct _KANJI_DATA_ {
    char meaning[50];
    char kunYomi[30];
    char onYomi[30];
} KANJI_DATA, *pKANJI_DATA;

typedef struct _GAME_KANJI_DATA_ {
    char meaning[50];
} GAME_KANJI_DATA, *pGAME_KANJI_DATA;

typedef struct _VOCAB_DATA_ {
    char romanji[40];
    char japanese[30];
    char meaning[180];
} VOCAB_DATA, *pVOCAB_DATA;

extern const unsigned char* hiragana_Sprite[16][5];
extern const short unsigned int* hiragana_Pal[16][5];
extern const unsigned char* katakana_Sprite[16][5];
extern const short unsigned int* katakana_Pal[16][5];
extern const unsigned char* kanji_Sprite[30][4];
extern const short unsigned int* kanji_Pal[30][4];

static const int FONT_TILE_16x16 = 16;

static UL_VIRTUALFILENAME ram_names[] = {
  {"checked.gif", (void*)checked, (int)checked_size, &VF_MEMORY},
  {"unknown.gif", (void*)unknown, (int)unknown_size, &VF_MEMORY},
  {"kanji.gif", (void*)kanji, (int)kanji_size, &VF_MEMORY},
  {"kanas.gif", (void*)kanas, (int)kanas_size, &VF_MEMORY},
  {"bg_bottom_screen.gif", (void*)bg_bottom_screen, (int)bg_bottom_screen_size, &VF_MEMORY},
  {"panel_title.gif", (void*)panel_title, (int)panel_title_size, &VF_MEMORY},
  {"panel_title_1.gif", (void*)panel_title_1, (int)panel_title_1_size, &VF_MEMORY},
  {"panel_title_2.gif", (void*)panel_title_2, (int)panel_title_2_size, &VF_MEMORY},
  {"panel_title_3.gif", (void*)panel_title_3, (int)panel_title_3_size, &VF_MEMORY},
  {"panel_title_4.gif", (void*)panel_title_4, (int)panel_title_4_size, &VF_MEMORY},
  {"key_1.gif", (void*)key_1, (int)key_1_size, &VF_MEMORY},
  {"key_2.gif", (void*)key_2, (int)key_2_size, &VF_MEMORY},
  {"key_3.gif", (void*)key_3, (int)key_3_size, &VF_MEMORY},
  {"key_4.gif", (void*)key_4, (int)key_4_size, &VF_MEMORY},
  {"bt_back.gif", (void*)bt_back, (int)bt_back_size, &VF_MEMORY},
  {"bt_up.gif", (void*)bt_up, (int)bt_up_size, &VF_MEMORY},
  {"bt_down.gif", (void*)bt_down, (int)bt_down_size, &VF_MEMORY},
  {"bt_left.gif", (void*)bt_left, (int)bt_left_size, &VF_MEMORY},
  {"bt_right.gif", (void*)bt_right, (int)bt_right_size, &VF_MEMORY},
  {"bt_hira.gif", (void*)bt_hira, (int)bt_hira_size, &VF_MEMORY},
  {"bt_kata.gif", (void*)bt_kata, (int)bt_kata_size, &VF_MEMORY},
  {"bt_kanji.gif", (void*)bt_kanji, (int)bt_kanji_size, &VF_MEMORY},
  {"bt_numbers.gif", (void*)bt_numbers, (int)bt_numbers_size, &VF_MEMORY},
  {"bt_draw.gif", (void*)bt_draw, (int)bt_draw_size, &VF_MEMORY},
  {"bt_vocab.gif", (void*)bt_vocab, (int)bt_vocab_size, &VF_MEMORY},
  {"keyboard_del.gif", (void*)keyboard_del, (int)keyboard_del_size, &VF_MEMORY},
  {"keyboard_enter.gif", (void*)keyboard_enter, (int)keyboard_enter_size, &VF_MEMORY},
  {"keyboard_caps.gif", (void*)keyboard_caps, (int)keyboard_caps_size, &VF_MEMORY},
  {"keyboard_shift.gif", (void*)keyboard_shift, (int)keyboard_shift_size, &VF_MEMORY},
  {"keyboard_space.gif", (void*)keyboard_space, (int)keyboard_space_size, &VF_MEMORY},
  {"menu_hand.gif", (void*)menu_hand, (int)menu_hand_size, &VF_MEMORY},
  {"title_profile.gif", (void*)title_profile, (int)title_profile_size, &VF_MEMORY},
  {"title_name.gif", (void*)title_name, (int)title_name_size, &VF_MEMORY},
  {"title_difficulty.gif", (void*)title_difficulty, (int)title_difficulty_size, &VF_MEMORY},
  {"title_options.gif", (void*)title_options, (int)title_options_size, &VF_MEMORY},
  {"font_ascii.gif", (void*)font_ascii, (int)font_ascii_size, &VF_MEMORY} 
};

extern inline std::string getFilePath(char* fileName, jlpt::ScoreManager* scoreManager) {
  int language = 1; // Langue par defaut = English
  if (scoreManager != NULL) {
    language = scoreManager->getLanguage();
  }
  std::string filePath = "/JLPT4/";  
  if (language == 1) {
    filePath = filePath + "EN/" + fileName;
  } else {
    filePath = filePath+ "FR/" + fileName;
  }
  return filePath;
}

extern inline bool isEmpty(const u16* unicodeTxt) {
  if (unicodeTxt != NULL && unicodeTxt[0] != '\0') {
    return false;
  }
  return true;
}

extern inline bool isEmpty(const char* unicodeTxt) {
  if (unicodeTxt != NULL && unicodeTxt[0] != 0x20 && unicodeTxt[1] != 0x00) {
    return false;
  }
  return true;
}

extern inline UL_IMAGE* loadImageGIF(char* name, int pixelFormat) {
  ulSetVirtualFilenameList(ram_names, ulNumberof(ram_names));
  UL_IMAGE *image = ulLoadImageFileGIF(name, 0, UL_IN_RAM, pixelFormat);
  ulSetImageTileSize(image, 0, 0, image->sizeX, image->sizeY);
  return image;
}

extern inline void drawTransparentRect(int x0, int y0, int x1, int y1,
  UL_COLOR color) {
  ulSetAlpha(UL_FX_ALPHA, 16, 1);
  ulDrawFillRect(x0, y0, x1, y1, color);
  ulSetAlpha(UL_FX_DEFAULT, 0, 0);
}

extern inline void drawTile(UL_IMAGE* img, int i, int j, int x, int y) {
  ulSetImageTile(img, 16*i, 16*j, 16*i + FONT_TILE_16x16, 16*j
      + FONT_TILE_16x16);
  ulDrawImageXY(img, x, y);
}

extern inline std::string& triml(std::string& s) {
  int pos(0);
  for (; s[pos]==' ' || s[pos]=='\t'; ++pos)
    ;
  s.erase(0, pos);
  return s;
}

extern inline std::string& trimr(std::string& s) {
  int pos(s.size());
  for (; pos && s[pos-1]==' ' || s[pos]=='\t'; --pos)
    ;
  s.erase(pos, s.size()-pos);
  return s;
}

extern inline std::string& trim(std::string& s) {
  return triml(trimr(s));
}

extern inline std::string& capitalize(std::string& s) {
  for (unsigned int i = 0; i < s.size(); i++) {
    s[i] = toupper(s[i]);
  }
  return s;
}

extern inline std::string& lowerize(std::string& s) {
  for (unsigned int i = 0; i < s.size(); i++) {
    s[i] = tolower(s[i]);
  }
  return s;
}

#endif // __TOOLS_H__
