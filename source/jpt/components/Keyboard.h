#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

namespace jlpt {

  typedef enum {
    KEY_DEL = 127,
    KEY_ENTER = 13,
    KEY_CAPS = 14,
    KEY_SHIFT = 15,
    KEY_SPACE = 16
  } KEYBOARD;

  class Keyboard : public Component {
    public:
      Keyboard(Component* parent);
      ~Keyboard();
  };
}

#endif // __KEYBOARD_H__
