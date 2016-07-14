#ifndef __TEXTCOMPONENT_H__
#define __TEXTCOMPONENT_H__

namespace jlpt {

  class TextComponent : public Component {
    public:
      TextComponent(Component* parent, char* text);
      TextComponent(Component* parent, char* text, char* imageName);
      ~TextComponent();
      void setTextColor(UL_COLOR color);
      void setTextShadow(UL_COLOR color);
      void setXOffsetForText(int offset);
      void setYOffsetForText(int offset);
      void drawText();
      virtual void display(SCREEN scr);
      const char* getText();
      void setText(const char* txt);
      void init(char* text);
      void capitalize();
      void lower();
      void del();
      void addChar(int i);
      void setMaxLength(int i);
      void clear();
      int size();

    protected:
      std::string* text;
      UL_COLOR textColor;
      bool hasTextShadow;
      UL_COLOR textShadowColor;
      int xOffsetForText;
      int yOffsetForText;
      unsigned int maxLength;
  };
}

#endif // __TEXTCOMPONENT_H__
