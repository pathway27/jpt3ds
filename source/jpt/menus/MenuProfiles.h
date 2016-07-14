#ifndef __MENUPROFILES_H__
#define __MENUPROFILES_H__

namespace jlpt {
	
	class MenuProfiles : public Menu {

		public:
			MenuProfiles(Component* parent);
			~MenuProfiles();
			int dealEvent(SCREEN scr);
			void display(SCREEN scr);
			Button* getProfileButton();
			int getProfileIndex();
			void setScoreManager(ScoreManager* s);
		private:
			void selectProfile();
			
		private:
		   Button* buttonProfile1;
		   Button* buttonProfile2;
		   Button* buttonProfile3;
	};
}

#endif // __MENUPROFILES_H__
