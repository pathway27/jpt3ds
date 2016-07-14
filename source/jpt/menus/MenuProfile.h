#ifndef __MENUPROFILE_H__
#define __MENUPROFILE_H__

namespace jlpt {
	
	class MenuProfile : public Menu {

		public:
			MenuProfile(Component* parent);
			~MenuProfile();
			int dealEvent(SCREEN scr);			
			Input* getInput();				
			void show();
		private:
		  void updateOKButton();
		  bool isValidName();
		  int dealOKEvent();
			
		private:
		   Input* nameInput;
		   KeyboardAscii* keyboard;
		   Button* okButton;
	};
}

#endif // __MENUPROFILE_H__
