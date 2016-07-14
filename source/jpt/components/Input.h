#ifndef __INPUT_H__
#define __INPUT_H__

namespace jlpt {

	class Input : public TextComponent {
		public:
			Input(Component* parent, char* txt);
			~Input();
			void display(SCREEN scr);
			void drawCursor();
	};
}

#endif // __INPUT_H__
