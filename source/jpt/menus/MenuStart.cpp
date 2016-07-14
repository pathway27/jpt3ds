#include <ulib/ulib.h>
#include <vector>
#include "../Commands.h"
#include "../geometry/Point.h"
#include "../geometry/Dimension.h"
#include "../geometry/Rectangle.h"
#include "../components/Component.h"
#include "../data/Stroke.h"
#include "../data/Gesture.h"
#include "../components/DrawComponent.h"
#include "../components/TextComponent.h"
#include "../Tools.h"
#include "../scores/ScoreManager.h"
#include "../files/File.h"
#include "../files/FileReader.h"
#include "Menu.h"
#include "../components/Panel.h"
#include "../components/TabbedPanel.h"
#include "../fonts/Jis.h"
#include "../grids/Grid.h"
#include "../grids/GridHiragana.h"
#include "../grids/GridKatakana.h"
#include "../components/Button.h"
#include "../components/List.h"
#include "MenuStart.h"

using namespace jlpt;

MenuStart::MenuStart(Component* parent) :
  Menu(parent) {

  Button* m_button = new Button(this, RGB15(31, 25, 0), "PRESS START");
  m_button->center();
  m_button->setCommand(START);
  m_button->setBorder(RGB15(0, 0, 0), 2, 31);
  m_button->setShadow(RGB15(0, 0, 0), 3);
  m_button->setTextShadow(RGB15(15, 15, 15));
  m_button->setSelected(true);
  this->add(m_button);

  // Affichage d'un message si
  // L'initialisation de LIBFAT a echouee
  FileReader* fileReader = new FileReader("/JLPT4/drawings.db", ASCII);
  fileReader->open("rb");
  if (fileReader->exists()) {
    fileReader->close();
  } else {
    Panel* errorPanel = new Panel(this);
    errorPanel->setSize(226, 40);
    errorPanel->setLocation(15, 10);
    errorPanel->setBackgroundColor(RGB15(31, 0, 0), 16);
    errorPanel->setBorder(RGB15(31, 31, 31), 2, 31);
    this->add(errorPanel);

    TextComponent* errorLabel = new TextComponent(this, "Error:Could not initialize libfat!");
    errorLabel->setTextColor(RGB15(31, 31, 31));
    errorLabel->setTextShadow(RGB15(0, 0, 0));
    errorLabel->centerX(20);
    this->add(errorLabel);
  }

  Panel* infoPanel = new Panel(this);
  infoPanel->setSize(226, 40);
  infoPanel->setLocation(15, 142);
  infoPanel->setBackgroundColor(RGB15(31, 31, 31), 16);
  infoPanel->setBorder(RGB15(31, 0, 0), 2, 16);
  this->add(infoPanel);

  TextComponent* emailLabel = new TextComponent(this, "by cuicui666, olimin & altarfinch");
  emailLabel->setTextShadow(RGB15(15, 15, 15));
  emailLabel->centerX(145);
  this->add(emailLabel);

  TextComponent* versionLabel = new TextComponent(this, "version : 0.8");
  versionLabel->setTextShadow(RGB15(15, 15, 15));
  versionLabel->centerX(160);
  this->add(versionLabel);
}

MenuStart::~MenuStart() {
  // NOTHING TO DO
}

int MenuStart::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {
    if (ul_keys.pressed.A) {
      press();
    } else {
      return Component::dealEvent(scr);
    }
  }
  return CMD_NONE;
}
