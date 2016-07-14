#ifndef __MENUSTART_H__
#define __MENUSTART_H__

namespace jlpt {
	
	class MenuStart : public Menu {

		public:
			MenuStart(Component* parent);
			~MenuStart();
			int dealEvent(SCREEN scr);
	};
}

#endif // __MENUSTART_H__
