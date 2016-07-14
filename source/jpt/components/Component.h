#ifndef __COMPONENT_H__
#define __COMPONENT_H__

namespace jlpt {

  typedef enum SCREEN {
    SCREEN_UP = 1,
    SCREEN_DOWN = 0
  };

  typedef enum BG_ORDER {
    BG_0 = 0,
    BG_1 = 1,
    BG_2 = 2,
    BG_3 = 3
  };

  typedef enum COLOR {
    WHITE = 1,
    RED = 2,
    GREEN = 3,
    DARK_BLUE = 4,
    PURPLE = 5,
    LIGHT_BLUE = 6,
    YELLOW = 7,
    GREY = 8,
    DARK_GREY = 9,
    BLACK = 10
  };

  typedef enum COLOR_MODE {
    COLOR_16 = 0,
    COLOR_256 = 1
  };

  typedef enum FONT_SIZE {
    SIZE_0 = 0,
    SIZE_1 = 1,
    SIZE_2 = 2,
    SIZE_3 = 3,
    SIZE_4 = 4
  };

  typedef enum PALETTE_NUMBER {
    PALETTE_0 = 0,
    PALETTE_1 = 1,
    PALETTE_2 = 2,
    PALETTE_3 = 3,
    PALETTE_4 = 4,
    PALETTE_5 = 5,
    PALETTE_6 = 6,
    PALETTE_7 = 7,
    PALETTE_8 = 8,
    PALETTE_9 = 9,
    PALETTE_10 = 10,
    PALETTE_11 = 11,
    PALETTE_12 = 12,
    PALETTE_13 = 13,
    PALETTE_14 = 14,
    PALETTE_15 = 15
  };

  typedef enum SPRITE_NUMBER {
    SPRITE_0 = 0,
    SPRITE_1 = 1,
    SPRITE_2 = 2,
    SPRITE_3 = 3,
    SPRITE_4 = 4,
    SPRITE_5 = 5,
    SPRITE_6 = 6,
    SPRITE_7 = 7,
    SPRITE_8 = 8,
    SPRITE_9 = 9,
    SPRITE_10 = 10,
    SPRITE_11 = 11,
    SPRITE_12 = 12,
    SPRITE_13 = 13,
    SPRITE_14 = 14,
    SPRITE_15 = 15
  };

  typedef enum STATE {
    STATE_INITIALIZED = 0
  };

  typedef enum TYPE {
    TYPE_COMPONENT = 0,
    TYPE_BUTTON = 1,
    TYPE_MENU = 2,
    TYPE_TABPANE = 3,
    TYPE_PANE = 4,
    TYPE_GRID = 5,
    TYPE_VOCAB = 6,
    TYPE_APP = 7,
    TYPE_GAME = 8,
    TYPE_INPUT = 9,
    TYPE_IMAGE = 10,
    TYPE_LIST = 11,
    TYPE_CHECKBOX = 12,
    TYPE_DRAW = 13
  };

  class Component {

    public:
      Component(Component* parent);
      Component(Component* parent, char* imageName);
      void init(Component* parent);
      virtual ~Component();
      virtual void setLocation(int x, int y);
      Point* getLocation();
      void center();
      void centerX(int y);
      void centerY(int x);
      virtual void setSize(int width, int height);
      virtual int dealEvent(SCREEN scr);
      int dealEventChildren(SCREEN scr);
      bool containsStylus();
      bool containsStylusChildren();
      int getState();
      void setVisibility(bool b);
      virtual void show();
      virtual void showChildren();
      virtual void hide();
      virtual void hideChildren();
      virtual void add(Component* c);
      void removeComponent(Component* c);
      virtual void display(SCREEN scr);
      virtual void displayChildren(SCREEN scr);
      virtual void countFps();
      int getCommand();
      void setCommand(int c);
      int consumeCommand();
      void deleteChildren();
      TYPE getType();
      int getX();
      int getY();
      int getWidth();
      int getHeight();
      int getMaxX();
      int getMaxY();
      int getMidX();
      int getMidY();
      Rectangle* getBounds();
      void setBackgroundImage(UL_IMAGE* img);
      void loadBackgroundImage(char* imgName, int pixelFormat);
      void setBorder(UL_COLOR color, int size, int alpha);
      void setShadow(UL_COLOR color, int size);
      virtual void setBackgroundColor(UL_COLOR color, int alpha);
      void setSelected(bool selected);
      void setSelectable(bool b);
      void setSelectedChildren(bool selected);
      bool getSelected();
      bool getSelectable();
      void selectBefore();
      void selectAfter();
      void selectFirst();
      void selectLast();
      void deselectAll();
      void drawSelection();
      UL_COLOR getBackgroundColor();
      void drawShadowedText(const char* text, int x, int y, UL_COLOR textColor,
        UL_COLOR shadowColor);
      void drawText(const char* text, int x, int y, UL_COLOR textColor);
      void drawAnimation_1(int x, int y, int maxX, int maxY, UL_COLOR color);
      char* getBackgroundImageName();
      bool isVisible();
      void drawBackground(UL_COLOR color);
      virtual void press();
      Component* getComponent(int index, TYPE componentId);
      void addColor(UL_COLOR color);
      UL_COLOR getColor(int i);
      void setColor(UL_COLOR color, int i);
      const void* getSound();
      void setSound(const void* s, u32 sound_size);
      void playSound();
      void playSoundEx0(const void* snd, u32 snd_size);
      
    protected:
      void drawBackground();
      void drawShadow();
      void drawBorder();
      bool selected;
      bool isSelectable;
      bool visible;
      int state;
      int command;
      TYPE type;
      SCREEN screen;
      Point* m_location;
      Dimension* m_dimension;
      Rectangle* m_bounds;
      Component* parent;
      UL_IMAGE* imgBg;
      char* imgBgName;
      std::vector<Component*> children;
      int borderSize;
      int shadowSize;
      int borderAlpha;
      int bgAlpha;
      bool hasBorder;
      bool hasShadow;
      bool hasBgColor;
      UL_COLOR bgColor;
      UL_COLOR shadowColor;
      UL_COLOR borderColor;
      int nbFrame;
      std::vector<UL_COLOR> colors;
      const void* sound;
      u32 sound_size;
  };
}

#endif // __COMPONENT_H__
