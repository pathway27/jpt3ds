#ifndef __CHECKBOX_H__
#define __CHECKBOX_H__

namespace jlpt {

  class CheckBox : public Component {
    public:
      CheckBox(Component* parent);
      ~CheckBox();
      void display(SCREEN scr);
      void setChecked(bool c);
      bool getChecked();
      void hide();
      void show();
      int dealEvent(SCREEN scr);
      void press();
      
    protected:
      bool checked;
      UL_IMAGE* imgChecked;
      char* checkedImageName;
  };
}

#endif // __CHECKBOX_H__
