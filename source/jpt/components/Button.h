#ifndef __BUTTON_H__
#define __BUTTON_H__

namespace jlpt {

	class Button : public TextComponent {
		public:
		   Button(Component* parent, char* imageName);
			Button(Component* parent, UL_COLOR color, char* text);
			~Button();
			virtual void display(SCREEN scr);
			int dealEvent(SCREEN scr);
			void init();
			void press();
			void setMaxDelay(int d);
			
		protected:
			bool pressed;
			int delay;
			int maxDelay;
	};
}

#endif // __BUTTON_H__
