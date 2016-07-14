#ifndef __MENUPRACTICE_H__
#define __MENUPRACTICE_H__

namespace jlpt {

	class MenuPractice : public Menu {

		public:
			MenuPractice(Component* parent);
			~MenuPractice();
			int dealEvent(SCREEN scr);
		private:
			void selectDown();
			void selectUp();
			void updateTitle();
			Button* m_title;
	};
}

#endif // __MENUPRACTICE_H__
