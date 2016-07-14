#ifndef __ASCII_H__
#define __ASCII_H__

namespace jlpt {
	
	typedef enum {
		PALIB = 0,
		ULIB = 1
	} LIBRARY;
	
	class Ascii {

	   public:
	      Ascii(int screen, int bgLayer);
	      Ascii(int screen);
	      ~Ascii();
	      void displayChar(char numChar, int x, int y);
	      void displayString(const char* str, int x, int y);
	      void displayCenteredString(const char*, int y);
	      
		private:
		   int library;
		   int screen;
		   int bgLayer;
		   UL_IMAGE* imgTiles;
	};
}				

#endif // __ASCII_H__
