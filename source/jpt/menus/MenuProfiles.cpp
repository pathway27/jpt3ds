#include <ulib/ulib.h>
#include <vector>
#include "../Commands.h"
#include "../geometry/Point.h"
#include "../geometry/Dimension.h"
#include "../geometry/Rectangle.h"
#include "../components/Component.h"
#include "../components/TextComponent.h"
#include "../Tools.h"
#include "../scores/ScoreManager.h"
#include "Menu.h"
#include "../components/Panel.h"
#include "../components/TabbedPanel.h"
#include "../fonts/Jis.h"
#include "../grids/Grid.h"
#include "../grids/GridKanji.h"
#include "../grids/GridHiragana.h"
#include "../grids/GridKatakana.h"
#include "../components/Button.h"
#include "../grids/VocabularyList.h"
#include "../files/File.h"
#include "../files/FileWriter.h"
#include "../files/FileReader.h"
#include "../Tools.h"
#include "MenuProfiles.h"

using namespace jlpt;

MenuProfiles::MenuProfiles(Component* parent):Menu(parent, "title_profile.gif") {

	buttonProfile1 = new Button(this, RGB15(31, 25, 0), "-- EMPTY --");
	buttonProfile1->setSize(100, 21);
	buttonProfile1->setCommand(NEW_PROFILE);
	buttonProfile1->centerX(60);
	buttonProfile1->setBorder(RGB15(0, 0, 0), 2, 31);
	buttonProfile1->setShadow(RGB15(0, 0, 0), 3);
	buttonProfile1->setTextShadow(RGB15(15,15,15));
	buttonProfile1->setSelectable(true);
	buttonProfile1->setSelected(true);
	add(buttonProfile1);
	
	buttonProfile2 = new Button(this, RGB15(31, 25, 0), "-- EMPTY --");
	buttonProfile2->setSize(100, 21);
	buttonProfile2->setCommand(NEW_PROFILE);
	buttonProfile2->centerX(100);
	buttonProfile2->setBorder(RGB15(0, 0, 0), 2, 31);
	buttonProfile2->setShadow(RGB15(0, 0, 0), 3);
	buttonProfile2->setTextShadow(RGB15(15,15,15));
	buttonProfile2->setSelectable(true);
	add(buttonProfile2);
	
	buttonProfile3 = new Button(this, RGB15(31, 25, 0), "-- EMPTY --");
	buttonProfile3->setSize(100, 21);
	buttonProfile3->setCommand(NEW_PROFILE);
	buttonProfile3->centerX(140);
	buttonProfile3->setBorder(RGB15(0, 0, 0), 2, 31);
	buttonProfile3->setShadow(RGB15(0, 0, 0), 3);
	buttonProfile3->setTextShadow(RGB15(15,15,15));
	buttonProfile3->setSelectable(true);
	add(buttonProfile3);				 	
}

MenuProfiles::~MenuProfiles() {
	delete buttonProfile1;
	delete buttonProfile2;
	delete buttonProfile3;	
}   

void MenuProfiles::setScoreManager(ScoreManager* s) {
   Menu::setScoreManager(s);
	RECORDS* records = s->getRecords();
	for(int i = 0; i < 3; i++) {
	   if(!records[i].isNew) {
		   if(i == 0) {
		      buttonProfile1->setText(records[i].name);
		      buttonProfile1->setCommand(MAIN);
		   }
			else if(i == 1) {
		      buttonProfile2->setText(records[i].name);
		      buttonProfile2->setCommand(MAIN);
		   }
			else if(i == 2) {
		      buttonProfile3->setText(records[i].name);
		      buttonProfile3->setCommand(MAIN);
		   }
		}   
	}   
}   

int MenuProfiles::dealEvent(SCREEN scr) {
   if(visible && screen == scr) {
		if(ul_keys.pressed.up) {
			selectBefore();   
		}
		else if(ul_keys.pressed.down) {
			selectAfter();
		}
		else if(ul_keys.pressed.A) {
		   press();
		   selectProfile();
		}
		else if(ul_keys.touch.click) {
		   this->setSelectedChildren(false);		   
	      int cmd = Component::dealEvent(scr);
	      selectProfile();
	      return cmd;
		}					
		else {
			return Component::dealEvent(scr);
		}
	}
	return CMD_NONE;
}

void MenuProfiles::selectProfile() {
   int profile = getProfileIndex();
   scoreManager->setSelectedProfile(profile);
}

void MenuProfiles::display(SCREEN scr) {

   if (visible && screen == scr) {
      Component::display(scr);
   }
}

Button* MenuProfiles::getProfileButton() {
 	if(buttonProfile1->getSelected()) {
 	 	return buttonProfile1;
 	}
  	else if(buttonProfile2->getSelected()) {
 	 	return buttonProfile2;
 	}
 	else if(buttonProfile3->getSelected()) {
 	 	return buttonProfile3;
 	}
 	return NULL;
}

int MenuProfiles::getProfileIndex() {
 	if(buttonProfile1->getSelected()) {
 	 	return 0;
 	}
  	else if(buttonProfile2->getSelected()) {
 	 	return 1;
 	}
 	else if(buttonProfile3->getSelected()) {
 	 	return 2;
 	}
 	return -1;
} 
