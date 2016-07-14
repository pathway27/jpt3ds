#include <PA9.h>
#include <ulib/ulib.h>
#include <vector>
#include "../../gfx/all_gfx.h"
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"
#include "../geometry/Dimension.h"
#include "../components/Component.h"
#include "../Tools.h"
#include "Jis.h"

using namespace jlpt;

Jis::Jis(int screen, int bgLayer) {
   this->screen = screen;
   this->bgLayer = bgLayer;
   PA_LoadSimpleBg(screen, bgLayer, bg_kanas_Tiles, Blank, BG_256X256, 0, COLOR_256);
   PA_LoadBgPal(screen, bgLayer, (void*)bg_kanas_Pal);  
}   

void Jis::displayJapaneseChar(u16 numChar, int x, int y) {
	  
   int c = 2*numChar;
   int row = (numChar/16)*32;
   
   PA_SetMapTileEx(screen, bgLayer, x, y, bg_kanas_Map[row + c],0,0,0);
   PA_SetMapTileEx(screen, bgLayer, x+1, y, bg_kanas_Map[row + c + 1],0,0,0);
   PA_SetMapTileEx(screen, bgLayer, x, y+1, bg_kanas_Map[row + 32 + c],0,0,0);
   PA_SetMapTileEx(screen, bgLayer, x+1, y+1, bg_kanas_Map[row + 32 + c + 1],0,0,0);
}

void Jis::displayJapaneseString(const u16* str, int x, int y) {
   int xoffset = x;
   int yoffset = y;
   for(unsigned int i = 0; i < 3*sizeof(str); i++) {
      u16 numChar = str[i];
      
      // Gestion du caractere de fin de sequence
      if(numChar == 0x0000) {
    		return;  
   	}
   	
   	numChar = getCharNumber(numChar);
   	
   	bool isHalfWidth = false;
   	if(numChar == 0 || numChar == 96 ||	numChar == 192 ||	numChar == 193 ||
			numChar == 196 ||	numChar == 197 ||	numChar == 199 ||	numChar == 200) {
			isHalfWidth = true;
		} 
		
		// Position future du caractere
		if(!isHalfWidth && xoffset == 31) {
		  	xoffset = x;
			yoffset += 2;
		}   
		
		// Affichage du caractere
	   displayJapaneseChar(numChar, xoffset, yoffset);
      
		// Calcul de la position du prochain caractere
		if(isHalfWidth) {
       	xoffset += 1;  
      } else {   
		   xoffset += 2;
		}   
	   if(xoffset > 31) {
	    	xoffset = x;
			yoffset += 2;  
	   }
	}   
}

u16 Jis::getCharNumber(u16 numChar) {
	// 0x3040 --> 0x3093 : Hiragana
   if(numChar >= 0x3040 && numChar <= 0x3093) {
      return numChar - 0x3040;
   }
   // 0x30A0 --> 0x30F6 : Katakana
   else if(numChar >= 0x30A0 && numChar <= 0x30F6) {
      return numChar - 0x30A0 + 96;
   }
   // Caracteres special : virgule japonaise
   else if(numChar == 0x3001) {
      return 192;
   }  
   // Caracteres special : point japonais
   else if(numChar == 0x3002) {
      return 193;
   }
   // Caracteres special : - (long)
   else if(numChar == 0x30FC || numChar == 0x2015) {
      return 194;
   }
   // Caracteres special : - (court)
   else if(numChar == 0x2010) {
      return 195;
   }
   // Caracteres special : citation ouvrante
   else if(numChar == 0x300C || numChar == 0x300E) {
      return 196;
   }
   // Caracteres special : citation fermante
   else if(numChar == 0x300D || numChar == 0x300F) {
      return 197;
   }
   // Caracteres special : yen
   else if(numChar == 0xFFE5) {
      return 198;
   }
   // Caracteres special : ?
   else if(numChar == 0xFF1F) {
      return 199;
   }
   // Caracteres special : !
   else if(numChar == 0xFF01) {
      return 200;
   }
   // Caracteres special : ~
   else if(numChar == 0xFF5E || numChar == 0x7E00) {
      return 201;
   }
   // Caracteres special : (
   else if(numChar == 0xFF08 || numChar == 0x0028) {
      return 202;
   }
   // Caracteres special : )
   else if(numChar == 0xFF09 || numChar == 0x0029) {
      return 203;
   }
   // Caracteres special : /
   else if(numChar == 0x002F || numChar == 0xFF0F) {
      return 204;
   }
   // Caracteres special : .
   else if(numChar == 0x002E) {
      return 205;
   } 
   // Par defaut : ?
	return 199;  
}   
