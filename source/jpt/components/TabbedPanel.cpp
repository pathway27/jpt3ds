#include <ulib/ulib.h>
#include <vector>
#include "../Commands.h"
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"
#include "../geometry/Dimension.h"
#include "Component.h"
#include "Panel.h"
#include "../Tools.h"
#include "TabbedPanel.h"

using namespace jlpt;

TabbedPanel::TabbedPanel(Component* parent) :
  Panel(parent) {
  init();
}

TabbedPanel::TabbedPanel(Component* parent, char* title) :
  Panel(parent, title) {
  init();
}

void TabbedPanel::init() {
  type = TYPE_TABPANE;
  visiblePane = 0;
  imgInactiveTab = NULL;
}

TabbedPanel::~TabbedPanel() {
  delete &panels;
  delete imgInactiveTab;
}

void TabbedPanel::loadInactiveTabImage(char* imageName, int pixelFormat) {
  if (imgInactiveTab == NULL) {
    imgInactiveTab = loadImageGIF(imageName, pixelFormat);
  }
}

int TabbedPanel::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {
    // Gestion du stylet
    if (ul_keys.touch.click) {
      // Partie superieure avec les titres de chaque panel
      Rectangle* rTitle = new Rectangle(m_bounds->getX(), m_bounds->getY(), m_bounds->getWidth(), TAB_HEIGHT);

      if (rTitle->contains(ul_keys.touch.x, ul_keys.touch.y)) {
        int x0 = 0;
        int y0 = getY();
        int x1 = getX() - 1;
        Panel* p = NULL;
        char* title = NULL;

        for (u8 i = 0; i < panels.size(); i++) {
          p = panels.at(i);
          title = p->getTitle();
          x0 = x1;
          x1 = x0 + ulGetStringWidth(title) + 6;
          rTitle->setRect(x0, y0, x1 - x0, TAB_HEIGHT);

          if (rTitle->contains(ul_keys.touch.x, ul_keys.touch.y)) {
            Panel* visPane = panels.at(visiblePane);
            visPane->hide();
            visiblePane = i;
            p->show();
          }
        }
      }
      // Partie autre
      else {
        delete rTitle;
        return Component::dealEvent(scr);
      }
      delete rTitle;
    }
    // Gestion du clavier
    else if (ul_keys.pressed.L) {
      panels.at(visiblePane)->hide();
      if (visiblePane == 0) {
        visiblePane = panels.size() - 1;
      } else {
        visiblePane--;
      }
      panels.at(visiblePane)->show();
    } else if (ul_keys.pressed.R) {
      panels.at(visiblePane)->hide();
      if (visiblePane == panels.size() - 1) {
        visiblePane = 0;
      } else {
        visiblePane++;
      }
      panels.at(visiblePane)->show();
    } else {
      return panels.at(visiblePane)->dealEvent(scr);
    }
  }
  return CMD_NONE;
}

void TabbedPanel::add(Component* c) {
  if (c->getType() == TYPE_PANE) {
    // Heritage des dimensions du TabPane
    c->setSize(getWidth(), getHeight() - TAB_HEIGHT);
    c->setLocation(0, TAB_HEIGHT);

    // Seul le premier onglet est visible
    if (children.size() > 1) {
      c->hide();
    }

    // Ajout du panel dans une liste speciale
    Panel* p = (Panel*)c;
    panels.push_back(p);
  }
  Component::add(c);
}

void TabbedPanel::displayChildren(SCREEN scr) {
  if (visible && screen == scr) {
    int x0 = 0;
    int y0 = m_location->getY();
    int x1 = m_location->getX();
    int y1 = y0 + TAB_HEIGHT - 1;
    Component* component = NULL;
    char* title = NULL;
    UL_IMAGE* tabImg = NULL;

    // Affichage des onglets
    for (unsigned int i = 0; i < children.size(); i++) {
      component = children.at(i);
      if (component != NULL) {
        if (component->getType() == TYPE_PANE) {
          title = ((Panel*)component)->getTitle();
          x0 = x1;
          x1 = x0 + ulGetStringWidth(title) + 6;

          // Dessin de l'onglet actif
          if (visiblePane == i) {
            tabImg = ((Panel*)component)->getTabImage();
            drawTab(tabImg, component->getBackgroundColor(), x0, y0, x1, y1);
          } else {
            drawTab(imgInactiveTab, component->getBackgroundColor(), x0, y0,
                x1, y1);
          }

          // Ombre du titre
          ulSetAlpha(UL_FX_ALPHA, 16, 0);
          ulSetTextColor(RGB15(0, 0, 0));
          ulDrawString(x0 + 3 + 1, y0 + 5 + 1, title);
          ulSetAlpha(UL_FX_DEFAULT, 0, 0);
          // Dessin du titre
          ulSetTextColor(RGB15(31, 31, 31));
          ulDrawString(x0 + 3, y0 + 5, title);
        } else {
          component->display(scr);
        }
      }
    }

    // Recuperation du panel actif
    if (!panels.empty()) {
      Panel* p = panels.at(visiblePane);
      p->display(scr);
    }
  }
}

void TabbedPanel::drawTab(UL_IMAGE* img, UL_COLOR color, int x0, int y0,
  int x1, int y1) {
  // Dessin de l'onglet - image repetee sur X
  if (img != NULL) {
    ulSetImageTile(img, 0, 0, 1, 20);
    for (int i = 0; i < (x1-1-x0); i++) {
      ulDrawImageXY(img, x0 + i, y0);
    }
  }
  // Dessin de l'onglet - couleur de fond
  else {
    ulDrawFillRect(x0, y0, x1-1, y1, color);
  }
}

void TabbedPanel::showChildren() {
  panels.at(visiblePane)->show();
}

Panel* TabbedPanel::getVisiblePanel() {
  return panels.at(visiblePane);
}

int TabbedPanel::getVisiblePanelIndex() {
  return visiblePane;
}

Panel* TabbedPanel::getPanel(unsigned int index) {
  if(index < 0 || index > (panels.size() - 1)) {
    return NULL;
  }
  return panels.at(index);
}
