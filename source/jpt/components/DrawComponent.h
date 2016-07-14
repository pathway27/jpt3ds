#ifndef __DRAWCOMPONENT_H__
#define __DRAWCOMPONENT_H__

namespace jlpt {
  typedef struct POINT {
     signed short x;
     signed short y;
  }; 
  
  typedef struct STROKE {
    POINT points[32];
  };

  typedef struct GESTURE {
     STROKE strokes[30];
  };
  
  class DrawComponent : public Component {
    public:
      DrawComponent(Component* parent);
      virtual ~DrawComponent();
      int dealEvent(SCREEN scr);
      void display(SCREEN scr);
      void clear();
      void normalize();
      void setSize(int width, int height);
      float gestureDotProduct(Gesture* gesture1, Gesture* gesture2);
      float match(Gesture* gesture1, Gesture* gesture2);
      void memorize();
      void compare();
      void write(int index);
      void read(int index);
      void append();
      void replace();
      void left(u8 increment);
      void right(u8 increment);
      int getNbGestures();
      
    protected:
      Gesture* gesture;
      Gesture* memorizedGesture;
      bool drawing;
      float matchScore;
      int selectedGesture;
  };

}

#endif // __DRAWCOMPONENT_H__
