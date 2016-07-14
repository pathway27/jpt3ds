#ifndef __LIST_H__
#define __LIST_H__

namespace jlpt {

  class List : public Component {

    public:
      List(Component* parent);
      ~List();
      void addEntry(char* s);
      int dealEvent(SCREEN scr);
      void refreshSelectedEntry();
      void setBackgroundColor(UL_COLOR color, int alpha);
      int getSelectedEntry();
      void setSelectedEntry(u8 i);
      void display(SCREEN scr);
      void pressLeft();
      void pressRight();

    protected:
      std::vector<std::string> entries;
      Button* buttonText;
      u8 selectedEntry;
  };
}

#endif // __LIST_H__
