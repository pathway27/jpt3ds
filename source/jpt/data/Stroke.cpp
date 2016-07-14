#include <vector>
#include <math.h>
#include "../geometry/Point.h"
#include "Stroke.h"

using namespace jlpt;

Stroke::Stroke() {
}

Stroke::~Stroke() {
}

bool Stroke::empty() {
  return points.empty();
}

unsigned int Stroke::size() {
  return points.size();
}

Point* Stroke::at(unsigned int i) {
  return points.at(i);
}

Point* Stroke::back() {
  return points.back();
}

void Stroke::push_back(Point* p) {
  points.push_back(p);
}

float Stroke::getLength() {
  if (points.size() <= 1)
    return 0;
  
  float len = 0.0f;

  for (unsigned int i = 0; i < points.size()-2; i++) {
    len += getSegmentLength(i);
  }
  return len;
}

float Stroke::getSegmentLength(unsigned int index) {
  if(index >= (points.size()-1)) {
    return 0.0f;
  }
  Point* startPt = points.at(index);
  Point* endPt = points.at(index+1);
  float dx = endPt->getX() - startPt->getX();
  float dy = endPt->getY() - startPt->getY();
  return sqrtf(dx * dx + dy * dy);
}
