#ifndef __MENUMAIN_H__
#define __MENUMAIN_H__

namespace jlpt {
	
	class MenuMain : public Menu {

		public:
			MenuMain(Component* parent);
			~MenuMain();
			int dealEvent(SCREEN scr);
	};
}

#endif // __MENUMAIN_H__
