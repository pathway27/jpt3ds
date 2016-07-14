#ifndef __STROKE_H__
#define __STROKE_H__

namespace jlpt {

  class Stroke {
    public:
      Stroke();
      virtual ~Stroke();
      bool empty();
      unsigned int size();
      Point* at(unsigned int i);
      Point* back();
      void push_back(Point* p);
      float getLength();
      float getSegmentLength(unsigned int index);
      
    private:
      std::vector<Point*> points;
  };

}

#endif // __STROKE_H__
