#ifndef __TABBEDPANEL_H__
#define __TABBEDPANEL_H__

namespace jlpt {

  typedef enum {
    TAB_HEIGHT = 20
  };

  class TabbedPanel : public Panel {

    public:
      TabbedPanel(Component* parent);
      TabbedPanel(Component* parent, char* title);
      ~TabbedPanel();
      void add(Component* c);
      void showChildren();
      void displayChildren(SCREEN scr);
      void addTitle(Rectangle* r);
      void init();
      int dealEvent(SCREEN scr);
      void loadInactiveTabImage(char* imageName, int pixelFormat);
      void drawTab(UL_IMAGE* img, UL_COLOR color, int x0, int y0, int x1, int y1);
      Panel* getVisiblePanel();
      Panel* getPanel(unsigned int index);
      int getVisiblePanelIndex();

    protected:
      unsigned int visiblePane;
      std::vector<Panel*> panels;
      UL_IMAGE* imgInactiveTab;
  };
}

#endif // __TABBEDPANEL_H__
