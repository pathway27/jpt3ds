#include <PA9.h>
#include <ulib/ulib.h>
#include <vector>
#include <string>
#include "../../gfx/all_gfx.h"
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"
#include "../geometry/Dimension.h"
#include "../components/Component.h"
#include "../Tools.h"
#include "Ascii.h"

using namespace jlpt;

Ascii::Ascii(int screen, int bgLayer) {
   this->screen = screen;
   this->bgLayer = bgLayer;
   this->imgTiles = NULL;
   this->library = PALIB;
   PA_LoadSimpleBg(screen, bgLayer, bg_ascii_Tiles, Blank, BG_256X256, 0, COLOR_256);
   PA_LoadBgPal(screen, bgLayer, (void*)bg_ascii_Pal);  
}   

Ascii::Ascii(int screen) {
   this->screen = screen;
   this->library = ULIB;
   imgTiles = loadImageGIF("font_ascii.gif", UL_PF_PAL4);
}

Ascii::~Ascii() {
   if(this->imgTiles != NULL) {
	   ulRealizeImage(imgTiles);
	}   
}   
   
void Ascii::displayChar(char numChar, int i, int j) {
   // 0x32 --> 0x126 : Ascii
   if(numChar >= 0x20 && numChar <= 0x7E) {
      numChar = numChar - 0x20;
   }
   // Caracteres inconnu : ?
   else {
      numChar = 31;
   }

   if(library == PALIB) {
	   int c = 2*numChar;
	   int row = (numChar/16)*32;
	   PA_SetMapTileEx(screen, bgLayer, i, j, bg_ascii_Map[row + c],0,0,PALETTE_0);
	   PA_SetMapTileEx(screen, bgLayer, i+1, j, bg_ascii_Map[row + c + 1],0,0,PALETTE_0);
	   PA_SetMapTileEx(screen, bgLayer, i, j+1, bg_ascii_Map[row + 32 + c],0,0,PALETTE_0);
	   PA_SetMapTileEx(screen, bgLayer, i+1, j+1, bg_ascii_Map[row + 32 + c + 1],0,0,PALETTE_0);
	} else {
	   int row = numChar/16;
	   int col = numChar - row*16;
	 	drawTile(imgTiles, col, row, i*8, j*8);
	}   
}

void Ascii::displayString(const char* str, int x, int y) {
   int xoffset = x;
   std::string s = std::string(str);
   for(unsigned int i = 0; i < s.size(); i++) {
	   displayChar(str[i], xoffset, y);
	   xoffset+=2;
	}   
}

void Ascii::displayCenteredString(const char* str, int y) {
  displayString(str, 16 - strlen(str), y);
}
