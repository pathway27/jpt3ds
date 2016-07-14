#ifndef __GESTURE_H__
#define __GESTURE_H__

namespace jlpt {

  class Gesture : public Component {

    public:
      Gesture(Component* parent, bool bShowSteps);
      virtual ~Gesture();
      void clear();
      void normalize();
      void display();
      void addPoint(signed short x, signed short y, bool checkDoublon);
      bool addStroke();
      unsigned int size();
      Stroke* at(int i);
      bool empty();
      int getPointsCount();
    private:
      void normalizeSize();
      void normalizeCenter();
      void normalizeSpacing(Stroke* newStroke, Stroke* oldStroke);
      //float getScale();
      void affineTransform(float xBase, float yBase, float tx, float ty,
        float theta);
      void drawLine(float x1, float y1, float x2, float y2, float thickness,
        UL_COLOR color);

    private:
      std::vector<Stroke*> strokes;
      float scale;
      bool showSteps;
  };

}

#endif // __GESTURE_H__
