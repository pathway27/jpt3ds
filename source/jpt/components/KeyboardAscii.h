#ifndef __KEYBOARD_ASCII_H__
#define __KEYBOARD_ASCII_H__

namespace jlpt {

	typedef enum {
	   KB_SIMPLE = 0,
	   KB_FULL = 1,
	   KB_COMPLEX = 2
	} KB_MODE;
	
	class KeyboardAscii : public Keyboard {
		public:
		  KeyboardAscii(Component* parent, KB_MODE mode);
			~KeyboardAscii();
			int dealEvent(SCREEN scr);
			void pressCaps();
			void pressShift();
			
		protected:
		   bool capsPressed;
		   bool shiftPressed;
	};
}

#endif // __KEYBOARD_ASCII_H__
