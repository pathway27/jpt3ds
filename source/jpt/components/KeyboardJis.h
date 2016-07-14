#ifndef __KEYBOARD_JIS_H__
#define __KEYBOARD_JIS_H__

namespace jlpt {

	class KeyboardJis : public Keyboard {
	  
	  
		public:
		  KeyboardJis(Component* parent);
			~KeyboardJis();
			int dealEvent(SCREEN scr);
			void display(SCREEN scr);
			void show();
			void hide();
			
		private:
		  UL_IMAGE* imgTiles;
	};
}

#endif // __KEYBOARD_JIS_H__
