#ifndef __MENU_OPTIONS_H__
#define __MENU_OPTIONS_H__

namespace jlpt {
	
	class MenuOptions : public Menu {

		public:
			MenuOptions(Component* parent);
			~MenuOptions();
			int dealEvent(SCREEN scr);
			void show();
		private:
      void saveOptions();		  
			void displayScores(int gameIndex);
			
		private:
		   List* listDifficulty;
		   List* listSpeed;
		   List* listScore;
		   List* listLanguage;
		   CheckBox* checkJoker;
		   Panel* scorePane;
	};
}

#endif // __MENU_OPTIONS_H__
