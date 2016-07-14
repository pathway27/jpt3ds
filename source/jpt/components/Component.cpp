#include <PA9.h>
#include <ulib/ulib.h>
#include <vector>
#include "../Commands.h"
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"
#include "../geometry/Dimension.h"
#include "../Tools.h"
#include "Component.h"

using namespace jlpt;

Component::Component(Component* parent) {
  init(parent);
}

Component::Component(Component* parent, char* imageName) {
  init(parent);

  // Fond d'ecran inferieur
  loadBackgroundImage(imageName, UL_PF_PAL4);
  setSize(imgBg->sizeX, imgBg->sizeY);
}

void Component::init(Component* parent) {
  this->type = TYPE_COMPONENT;
  this->parent = parent;
  state = STATE_INITIALIZED;
  visible = true;
  isSelectable = false;
  selected = false;
  command = CMD_NONE;
  screen = SCREEN_DOWN;
  m_location = NULL;
  m_dimension = NULL;
  m_bounds = NULL;
  imgBg = NULL;
  imgBgName = NULL;
  hasBorder = false;
  hasShadow = false;
  hasBgColor = false;
  borderSize = 0;
  shadowSize = 0;
  borderAlpha = 31;
  bgAlpha = 31;
  setSize(256, 192);
  setLocation(0, 0);
  nbFrame = 0;
}

Component::~Component() {
  delete m_location;
  delete m_dimension;
  delete m_bounds;
  delete imgBg;
  delete imgBgName;
  deleteChildren();
}

Component* Component::getComponent(int index, TYPE componentId) {
  int nbFoundItems = 0;
  for(unsigned int i = 0; i < this->children.size(); i++) {
    Component* component = this->children.at(i);
    if(component->getType() == componentId) {
      if(nbFoundItems == index) {
        return component;
      } else {
        nbFoundItems++;        
      }
    }
  }
  return NULL;
}

void Component::press() {
  // NOTHING TO DO
}

void Component::selectBefore() {
  bool selectBefore = false;

  for (int i = children.size() - 1; i >= 0; i--) {
    Component* component = children.at(i);
    if (component->getSelected()) {
      component->setSelected(false);
      if (i == 0) {
        selectLast();
        return;
      } else {
        selectBefore = true;
      }
    } else if(component->getSelectable() && selectBefore) {
      component->setSelected(true);
      return;
    }
  }

  selectLast();
}

void Component::selectAfter() {
  bool selectNext = false;
  for (unsigned int i = 0; i < children.size(); i++) {
    Component* component = children.at(i);
    if (component->getSelected() && component->getSelectable()) {
      component->setSelected(false);
      if (i == children.size() - 1) {
        selectFirst();
        return;
      } else {
        selectNext = true;
      }
    } else if(component->getSelectable() && selectNext) {
      component->setSelected(true);
      return;
    }
  }
  // Composant selectionne non trouve : on selectionne le 1er par defaut
  selectFirst();
}

void Component::selectFirst() {
  for (unsigned int i = 0; i < children.size(); i++) {
    Component* component = children.at(i);
    if (component != NULL && component->getSelectable()) {
      component->setSelected(true);
      return;
    }
  }
}

void Component::selectLast() {
  for (int i = children.size()-1; i >= 0; i--) {
    Component* component = children.at(i);
    if (component != NULL && component->getSelectable()) {
      component->setSelected(true);
      return;
    }
  }
}

void Component::deselectAll() {
  for (unsigned int i = 0; i < children.size(); i++) {
    Component* component = children.at(i);
    if (component != NULL && component->getSelectable()) {
      component->setSelected(false);
    }
  }
}

bool Component::getSelectable() {
  return isSelectable;
}

void Component::drawAnimation_1(int x, int y, int maxX, int maxY, UL_COLOR color) {
  int offset = 0;
  if (nbFrame == 0) {
    offset = 0;
  } else if (nbFrame <= 5) {
    offset = 1;
  } else if (nbFrame <= 10) {
    offset = 2;
  } else if (nbFrame <= 15) {
    offset = 3;
  } else if (nbFrame <= 20) {
    offset = 2;
  } else if (nbFrame <= 25) {
    offset = 1;
  } else if (nbFrame <= 30) {
    offset = 0;
  } else if (nbFrame <= 35) {
    offset = 1;
  } else if (nbFrame <= 40) {
    offset = 2;
  } else if (nbFrame <= 45) {
    offset = 3;
  } else if (nbFrame <= 50) {
    offset = 2;
  } else if (nbFrame <= 55) {
    offset = 1;
  }
  // TOP_LEFT
  ulDrawFillRect(x-offset, y-offset, x+5-offset, y+2-offset, color);
  ulDrawFillRect(x-offset, y+2-offset, x+2-offset, y+5-offset, color);
  // TOP_RIGHT
  ulDrawFillRect(maxX-5+offset, y-offset, maxX+offset, y+2-offset, color);
  ulDrawFillRect(maxX-2+offset, y+2-offset, maxX+offset, y+5-offset, color);
  // BOTTOM_LEFT
  ulDrawFillRect(x-offset, maxY-5+offset, x+2-offset, maxY+offset, color);
  ulDrawFillRect(x+2-offset, maxY-2+offset, x+5-offset, maxY+offset, color);
  // BOTTOM_RIGHT
  ulDrawFillRect(maxX-5+offset, maxY-2+offset, maxX+offset, maxY+offset, color);
  ulDrawFillRect(maxX-2+offset, maxY-5+offset, maxX+offset, maxY-2+offset,
      color);
}

void Component::drawText(const char* text, int x, int y, UL_COLOR textColor) {
  ulSetTextColor(textColor);
  ulDrawString(x, y, text);
}

void Component::drawShadowedText(const char* text, int x, int y,
  UL_COLOR textColor, UL_COLOR shadowColor) {
  // Ombre du texte
  ulSetAlpha(UL_FX_ALPHA, 16, 0);
  ulSetTextColor(shadowColor);
  ulDrawString(x + 1, y + 1, text);
  ulSetAlpha(UL_FX_DEFAULT, 0, 0);
  // Texte
  drawText(text, x, y, textColor);
}

void Component::setSelectable(bool b) {
  this->isSelectable = b;
}

void Component::setSelected(bool selected) {
  this->selected = selected;
}

void Component::setSelectedChildren(bool selected) {
  for (unsigned int i = 0; i < children.size(); i++) {
    Component* component = children.at(i);
    component->setSelected(selected);
  }
}

void Component::drawSelection() {
  if (selected && isSelectable) {
    drawAnimation_1(getX(), getY(), getMaxX(), getMaxY(), RGB15(0, 0, 31));
  }
}

void Component::addColor(UL_COLOR color) {
  colors.push_back(color);
}

UL_COLOR Component::getColor(int i) {
  return colors.at(i);
}

void Component::setColor(UL_COLOR color, int i) {
  colors.at(i) = color;
}

void Component::setBackgroundImage(UL_IMAGE* img) {
  imgBg = img;
  hasBgColor = false;
}

UL_COLOR Component::getBackgroundColor() {
  return bgColor;
}

void Component::loadBackgroundImage(char* imgName, int pixelFormat) {
  if (imgName != NULL && imgBg == NULL) {
    imgBgName = imgName;
    imgBg = loadImageGIF(imgName, pixelFormat);
    hasBgColor = false;
  }
}

char* Component::getBackgroundImageName() {
  return imgBgName;
}

void Component::setLocation(int x, int y) {
  int oldX = this->getX();
  int oldY = this->getY();

  if (m_location == NULL) {
    m_location = new Point(0, 0);
  }

  if (parent == NULL) {
    m_location->setLocation(x, y);
  }
  // Position relative au parent
  else {
    int px = parent->getX();
    int py = parent->getY();
    m_location->setLocation(px + x, py + y);
  }

  // Mise a jour du rectangle contenant le composant
  if (m_bounds == NULL) {
    m_bounds = new Rectangle(m_location->getX(), m_location->getY(), 0, 0);
  } else {
    m_bounds->setX(m_location->getX());
    m_bounds->setY(m_location->getY());
  }

  // Mise a jour des enfants
  for (unsigned int i = 0; i < children.size(); i++) {
    Component* component = children.at(i);
    if (component != NULL) {
      component->setLocation(component->getX() - oldX, component->getY() - oldY);
    }
  }
}

Point* Component::getLocation() {
  return m_location;
}

void Component::center() {
  setLocation(128 - m_dimension->getWidth()/2, 96 - m_dimension->getHeight()/2);
}

void Component::centerX(int y) {
  setLocation(128 - m_dimension->getWidth()/2, y);
}

void Component::centerY(int x) {
  setLocation(x, 96 - m_dimension->getHeight()/2);
}

void Component::setSize(int width, int height) {
  if (m_dimension == NULL) {
    m_dimension = new Dimension(width, height);
  } else {
    m_dimension->setSize(width, height);
  }

  // Mise a jour du rectangle contenant le composant
  if (m_bounds == NULL) {
    m_bounds = new Rectangle(0, 0, m_dimension->getWidth(), m_dimension->getHeight());
  } else {
    m_bounds->setWidth(m_dimension->getWidth());
    m_bounds->setHeight(m_dimension->getHeight());
  }
}

int Component::getState() {
  return state;
}

TYPE Component::getType() {
  return type;
}

bool Component::containsStylus() {
  if (ul_keys.touch.x > getX()
&&    ul_keys.touch.x < getMaxX() &&
    ul_keys.touch.y> getY() &&
    ul_keys.touch.y < getMaxY()) {
      return true;
    }
    return false;
  }

bool Component::getSelected() {
  return selected;
}

bool Component::isVisible() {
  return visible;
}
int Component::dealEvent(SCREEN scr) {
  if (screen == scr && visible) {
    if (ul_keys.touch.click) {
      if (this->containsStylus()) {
        int c = this->getCommand();
        if (c != CMD_NONE) {
          return c;
        } else {
          return dealEventChildren(scr);
        }
      }
      // Ne contient pas le stylet
      else {
        this->setSelected(false);
      }
    }
    return dealEventChildren(scr);
  }
  return CMD_NONE;
}

int Component::consumeCommand() {
  int c = command;
  command = CMD_NONE;
  return c;
}

int Component::dealEventChildren(SCREEN scr) {

  for (unsigned int i = 0; i < children.size(); i++) {
    Component* component = children.at(i);
    if (component != NULL) {
      int c = component->dealEvent(scr);
      if (c != CMD_NONE) {
        return c;
      }
    }
  }

  return CMD_NONE;
}

void Component::setVisibility(bool b) {
  if (b) {
    show();
  } else {
    hide();
  }
}

void Component::show() {
  if (!visible) {
    visible = true;
    showChildren();
  }
}

void Component::showChildren() {
  for (unsigned int i = 0; i < children.size(); i++) {
    Component* component = children.at(i);
    if (component != NULL) {
      component->show();
    }
  }
}

void Component::hide() {
  if (visible) {
    visible = false;
    hideChildren();
  }
}

void Component::hideChildren() {
  for (unsigned int i = 0; i < children.size(); i++) {
    Component* component = children.at(i);
    if (component != NULL) {
      component->hide();
    }
  }
}

void Component::add(Component* c) {
  children.push_back(c);
}

void Component::removeComponent(Component* c) {
  for(size_t i = 0; i < children.size(); i++) {
    if(children.at(i) == c) {
      delete c;
      children.erase(children.begin()+i);   
    }
  }  
}

void Component::setCommand(int c) {
  command = c;
}

int Component::getCommand() {
  return command;
}

void Component::countFps() {
  nbFrame++;
  if (nbFrame > 59) {
    nbFrame = 0;
  }
}

void Component::setBorder(UL_COLOR color, int size, int alpha) {
  if (!hasBorder) {
    hasBorder = true;
    borderColor = color;
    borderSize = size;
    borderAlpha = alpha;
  }
}

void Component::setShadow(UL_COLOR color, int size) {
  if (!hasShadow) {
    hasShadow = true;
    shadowColor = color;
    shadowSize = size;
  }
}

void Component::setBackgroundColor(UL_COLOR color, int alpha) {
  hasBgColor = true;
  bgColor = color;
  bgAlpha = alpha;
}

void Component::display(SCREEN scr) {

  if (visible && screen == scr) {

    countFps();

    // Image de fond
    if (imgBg != NULL) {
      ulDrawImageXY(imgBg, getX(), getY());
    }
    // Couleur de fond
    else {
      drawBackground();
      drawBorder();
      drawShadow();
    }
    // Affichage des enfants   
    displayChildren(scr);
  }
}

void Component::drawBackground(UL_COLOR color) {
  ulDrawFillRect(getX() + borderSize, getY() + borderSize, getMaxX()
      - borderSize, getMaxY() - borderSize, color);
}

void Component::drawBackground() {
  if (hasBgColor) {
    if (bgAlpha < 31) {
      ulSetAlpha(UL_FX_ALPHA, bgAlpha, 0);
    }
    ulDrawFillRect(getX() + borderSize, getY() + borderSize, getMaxX()
        - borderSize, getMaxY() - borderSize, bgColor);
    if (bgAlpha < 31) {
      ulSetAlpha(UL_FX_DEFAULT, 0, 0);
    }
  }
}

void Component::drawShadow() {
  if (hasShadow) {
    ulSetAlpha(UL_FX_ALPHA, 16, 0);
    ulDrawFillRect(getX() + shadowSize, getMaxY(), getMaxX() + shadowSize,
        getMaxY() + shadowSize, shadowColor);
    ulDrawFillRect(getMaxX(), getY() + shadowSize, getMaxX() + shadowSize,
        getMaxY(), shadowColor);
    ulSetAlpha(UL_FX_DEFAULT, 0, 0);
  }
}

void Component::drawBorder() {
  if (hasBorder) {
    if (borderAlpha < 31) {
      ulSetAlpha(UL_FX_ALPHA, borderAlpha, 0);
    }
    ulDrawFillRect(getX(), getY(), getMaxX(), getY() + borderSize, borderColor);
    ulDrawFillRect(getX(), getMaxY() - borderSize, getMaxX(), getMaxY(),
        borderColor);
    ulDrawFillRect(getX(), getY() + borderSize, getX() + borderSize, getMaxY()
        - borderSize, borderColor);
    ulDrawFillRect(getMaxX() - borderSize, getY() + borderSize, getMaxX(),
        getMaxY() - borderSize, borderColor);
    if (borderAlpha < 31) {
      ulSetAlpha(UL_FX_DEFAULT, 0, 0);
    }
  }
}

void Component::displayChildren(SCREEN scr) {
  for (unsigned int i = 0; i < children.size(); i++) {
    Component* component = children.at(i);
    if (component != NULL) {
      component->display(scr);
    }
  }
}

void Component::deleteChildren() {
  children.clear();
}

bool Component::containsStylusChildren() {
  for (unsigned int i = 0; i < children.size(); i++) {
    Component* component = children.at(i);
    if (component != NULL) {
      if (component->containsStylus()) {
        return true;
      }
    }
  }
  return false;
}

int Component::getX() {
  return m_location->getX();
}

int Component::getY() {
  return m_location->getY();
}

int Component::getWidth() {
  return m_dimension->getWidth();
}

int Component::getHeight() {
  return m_dimension->getHeight();
}

int Component::getMaxX() {
  return m_bounds->getMaxX();
}

int Component::getMaxY() {
  return m_bounds->getMaxY();
}

int Component::getMidX() {
  return m_bounds->getMidX();
}

int Component::getMidY() {
  return m_bounds->getMidY();
}

Rectangle* Component::getBounds() {
  return m_bounds;
}

const void* Component::getSound() {
  return sound;
}

void Component::setSound(const void* s, u32 size) {
  sound = s;
  sound_size = size;
}

void Component::playSound() {
  if(sound != NULL) {
    PA_PlaySimpleSound(sound);
  }
}

void Component::playSoundEx0(const void* snd, u32 snd_size) {
  if(snd != NULL) {
    PA_PlaySimpleSound(snd);
  }
}
