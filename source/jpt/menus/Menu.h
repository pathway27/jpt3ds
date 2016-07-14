#ifndef __MENU_H__
#define __MENU_H__

namespace jlpt {

	class Button;
	
	class Menu : public Component {

		public:
			Menu(Component* parent);
			Menu(Component* parent, ScoreManager* s);
			Menu(Component* parent, char* imageName);
			virtual ~Menu();
			virtual void setScoreManager(ScoreManager* s);
		protected:
		  std::vector<Button*> getButtons();
      void selectBefore();
      void selectAfter();
      void press();
      void back();
		private:
      void init();
		  void selectFirst();
			
		protected:
		   ScoreManager* scoreManager;
	};
}

#endif // __MENU_H__
