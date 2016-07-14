#include <ulib/ulib.h>
#include <vector>
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"
#include "../geometry/Dimension.h"
#include "Component.h"
#include "../Tools.h"
#include "Panel.h"

using namespace jlpt;

Panel::Panel(Component* parent) :
  Component(parent) {
  type = TYPE_PANE;
  m_title = NULL;
  imgTab = NULL;
}

Panel::Panel(Component* parent, char* title) :
  Component(parent) {
  type = TYPE_PANE;
  m_title = title;
  imgTab = NULL;
}

Panel::~Panel() {
  delete m_title;
  delete imgTab;
}

char* Panel::getTitle() {
  return m_title;
}

void Panel::setTabImage(UL_IMAGE* image) {
  imgTab = image;
}

UL_IMAGE* Panel::getTabImage() {
  return imgTab;
}

void Panel::loadTabImage(char* imageName, int pixelFormat) {
  if (imgTab == NULL) {
    imgTab = loadImageGIF(imageName, pixelFormat);
  }
}
