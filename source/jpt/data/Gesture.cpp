#include <ulib/ulib.h>
#include <vector>
#include <math.h>
#include <nds.h>
#include "../geometry/Point.h"
#include "../geometry/Dimension.h"
#include "../geometry/Rectangle.h"
#include "../components/Component.h"
#include "../Tools.h"
#include "Stroke.h"
#include "Gesture.h"

using namespace jlpt;

Gesture::Gesture(Component* parent, bool bShowSteps) :
  Component(parent) {
  scale = 1.0f;
  showSteps = bShowSteps;
  this->addColor(RGB15(0, 0, 0));
  this->addColor(RGB15(0, 0, 31));
}

Gesture::~Gesture() {
}

void Gesture::clear() {
  strokes.clear();
  scale = 1.0f;
}

bool Gesture::empty() {
  return strokes.empty();
}

unsigned int Gesture::size() {
  return strokes.size();
}

Stroke* Gesture::at(int i) {
  return strokes.at(i);
}

void Gesture::normalize() {
  normalizeSize();
  normalizeCenter();
  std::vector<Stroke*> newStrokes;
  Stroke* newStroke;
  for (unsigned int i = 0; i < strokes.size(); i++) {
    newStroke = new Stroke();
    normalizeSpacing(newStroke, strokes.at(i));
    newStrokes.push_back(newStroke);
  }
  strokes.swap(newStrokes);
  newStrokes.clear();
}

void Gesture::normalizeSize() {
  if (strokes.empty()) {
    return;
  }

  int minX = 10000;
  int maxX = -10000;
  int minY = 10000;
  int maxY = -10000;

  // Calcul des limites du caractere
  Stroke* stroke;
  Point* pt;
  for (unsigned int i = 0; i < strokes.size(); i++) {
    stroke = strokes.at(i);
    for (unsigned int j = 0; j < stroke->size(); j++) {
      pt = stroke->at(j);
      if (minX > pt->getX())
        minX = pt->getX();
      if (minY > pt->getY())
        minY = pt->getY();
      if (maxX < pt->getX())
        maxX = pt->getX();
      if (maxY < pt->getY())
        maxY = pt->getY();
    }
  }

  // Calcul des dimensions 
  int width = maxX - minX;
  int height = maxY - minY;

  // Pas la peine de redimensionner 
  // si le caractere est suffisamment grand
  if (width >= getWidth() || height >= getHeight()) {
    return;
  }

  // Calcul de la proportion
  scale = (width > height) ? width : height;

  // Vide ou un simple point
  if (scale <= 0.0f)
    return;
  scale = (getWidth())/scale;
  scale = floor(scale*10)/10;

  // Redimensionnement du caractere
  int x, y;
  for (unsigned int i = 0; i < strokes.size(); i++) {
    stroke = strokes.at(i);
    for (unsigned int j = 0; j < stroke->size(); j++) {
      pt = stroke->at(j);
      x = (int)(pt->getX()*scale);
      y = (int)(pt->getY()*scale);
      // Pour ne pas sortir du cadre
      if (x < 0) {
        x = 0;
      }
      if (y < 0) {
        y = 0;
      }
      pt->setX(x);
      pt->setY(y);
    }
  }
}

void Gesture::normalizeCenter() {
  if (strokes.empty()) {
    return;
  }

  // Recherche des limites du dessin
  int minX = 10000;
  int maxX = -10000;
  int minY = 10000;
  int maxY = -10000;

  Stroke* stroke;
  Point* pt;
  for (unsigned int i = 0; i < strokes.size(); i++) {
    stroke = strokes.at(i);
    for (unsigned int j = 0; j < stroke->size(); j++) {
      pt = stroke->at(j);
      if (minX > pt->getX())
        minX = pt->getX();
      if (minY > pt->getY())
        minY = pt->getY();
      if (maxX < pt->getX())
        maxX = pt->getX();
      if (maxY < pt->getY())
        maxY = pt->getY();
    }
  }

  int width = maxX - minX;
  int height = maxY - minY;
  int centerX = minX + (width-getWidth())/2;
  int centerY = minY + (height-getHeight())/2;

  int x, y;
  for (unsigned int i = 0; i < strokes.size(); i++) {
    stroke = strokes.at(i);
    for (unsigned int j = 0; j < stroke->size(); j++) {
      pt = stroke->at(j);
      x = pt->getX() - centerX;
      y = pt->getY() - centerY;
      pt->setX(x);
      pt->setY(y);
    }
  }
}

void Gesture::normalizeSpacing(Stroke* newStroke, Stroke* oldStroke) {
  float totalLength = oldStroke->getLength();

  // Unique point ou distance nulle
  if (oldStroke->size() <= 2 || totalLength <= 0.0f) {
    return;
  }

  float segmentLength = totalLength/(POINTS_PER_STROKE - 1);

  // Ajout du premier point
  unsigned int index = 0;
  newStroke->push_back(oldStroke->at(index));
  Point* startPt = oldStroke->at(index);
  Point* endPt = oldStroke->at(index+1);

  // Distance along the old stroke at the beginning of the current segment
  float startOldDist = 0.0f;
  // Distance along old stroke at the end of the current segment
  float endOldDist = oldStroke->getSegmentLength(index);
  // Distance along new stroke
  float newDist = 0.0f;
  // Length of the current segment (on the old stroke)
  float currSegmentLen = oldStroke->getSegmentLength(index);

  for (;;) {

    float excess = endOldDist - newDist;
    // we have accumulated enough length, add a point
    if (excess >= segmentLength) {
      newDist += segmentLength;
      float ratio = (newDist - startOldDist)/currSegmentLen;
      Point* newPt = new Point(0, 0);
      int x = (int)((endPt->getX() - startPt->getX() ) * ratio
          + startPt->getX());
      int y = (int)((endPt->getY() - startPt->getY() ) * ratio
          + startPt->getY());
      if (x != 0 && y != 0) {
        newPt->setX(x);
        newPt->setY(y);
      } else {
        /*ulDebug(" ratio : %f \n", ratio);
         ulDebug(" newDist : %f \n", newDist);
         ulDebug(" startOldDist : %f \n", startOldDist);
         ulDebug(" currSegmentLen : %f \n", currSegmentLen);*/
        newPt->setX(startPt->getX());
        newPt->setY(startPt->getY());
      }
      newStroke->push_back(newPt);

      if (newStroke->size() >= POINTS_PER_STROKE) {
        return;
      }
    } else {
      if (index == (oldStroke->size()-1))
        break; // No more data

      // Store the start of the current segment
      index++;
      startPt = oldStroke->at(index);
      endPt = oldStroke->at(index+1);

      // Start accumulated distance (along the old stroke)
      // at the beginning of the segment
      startOldDist = endOldDist;
      // Add the length of the current segment to the
      // total accumulated length
      currSegmentLen = oldStroke->getSegmentLength(index);
      endOldDist+=currSegmentLen;
    }
  }

  //Due to floating point errors we may miss the last
  //point of the stroke
  if (newStroke->size() < POINTS_PER_STROKE) {
    newStroke->push_back(oldStroke->at(oldStroke->size()-1));
  }
}

bool Gesture::addStroke() {
  // On limite le nombre de stroke a 30 volontairement
  // Pour ne pas exploser la memoire de la DS
  if (strokes.size() < STROKE_PER_GESTURE) {
    strokes.push_back(new Stroke());
    return true;
  }
  return false;
}

void Gesture::addPoint(signed short x, signed short y, bool checkDoublon) {
  if (strokes.empty()) {
    strokes.push_back(new Stroke());
  }

  // On limite volontairement le nombre TOTAL de points
  // Pour ne pas exploser la memoire de la DS
  if (ulGetVertexUsedMemory() > (6144 - 500)) {
    return;
  }

  Stroke* stroke = strokes.back();

  // Points suivants
  if (!stroke->empty()) {
    Point* p = stroke->back();
    // On verifie que l'on ne rentre pas plusieurs fois le meme point
    if (checkDoublon) {
      if (p->getX() != x || p->getY() != y) {
        stroke->push_back(new Point(x, y));
      }
    }
    // Sauf dans le cas de la recopie
    else {
      stroke->push_back(new Point(x, y));
    }
  }
  // Premier point
  else {
    stroke->push_back(new Point(x, y));
  }
}

void Gesture::display() {
  int x = getX();
  int y = getY();
  Stroke* stroke = NULL;
  Point* startPt = NULL;
  Point* p = NULL;
  for (unsigned int i = 0; i < strokes.size(); i++) {
    stroke = strokes.at(i);

    if (!stroke->empty()) {
      // Dessin du premier point
      startPt = stroke->at(0);

      // Dessin des suivants avec dessin d'une ligne reliant chaque point
      for (unsigned int j = 1; j < stroke->size(); j++) {
        p = stroke->at(j);
        // Dessin en degrade rouge-jaune pour les dessins memorises
        if (showSteps) {
          drawLine( (float)(startPt->getX()+x), (float)(startPt->getY()+y),
              (float)(p->getX()+x), (float)(p->getY()+y), 3, RGB15(31, 31*j
                  /stroke->size(), 10*j/stroke->size()));
        }
        // Dessin en degrade noir-bleu pour les dessins utilisateur
        else {
          drawLine( (float)(startPt->getX()+x), (float)(startPt->getY()+y),
              (float)(p->getX()+x), (float)(p->getY()+y), 3, RGB15(0, 0, 31*j
                  /stroke->size()));
        }
        startPt = p;
      }
    }
  }
  // Dessin des numéros
  for (unsigned int i = 0; i < strokes.size(); i++) {
    stroke = strokes.at(i);

    if (!stroke->empty()) {
      // Dessin du premier point
      startPt = stroke->at(0);

      // Dessin du numero du trait
      if (showSteps) {
        char text[5];
        sprintf(text, "%d", i+1);
        ulDrawFillRect(startPt->getX(), startPt->getY()+15, startPt->getX()+7, startPt->getY()+22, RGB15(31, 31, 31));
        drawText(text, startPt->getX(), startPt->getY()+15, RGB15(31, 0, 0));
      }
    }
  }
}

void Gesture::drawLine(float x1, float y1, float x2, float y2, float thickness,
  UL_COLOR color) {
  //ulDrawLine(x1, y1, x2, y2, color);
  GFX_BEGIN = GL_QUADS;
  GFX_COLOR = color;
  GFX_TEX_FORMAT = 0;

  float theta = atan((y2-y1)/(x2-x1));
  affineTransform(0, -thickness/2, x1, y1, theta);
  affineTransform(0, -thickness/2, x2, y2, theta);
  affineTransform(0, thickness/2, x2, y2, theta);
  affineTransform(0, thickness/2, x1, y1, theta);

  GFX_END = 0;
  //Incrémentation auto de la profondeur  
  ul_currentDepth += ul_autoDepth;
}

void Gesture::affineTransform(float xBase, float yBase, float tx, float ty,
  float theta) {
  float px = tx + (cos(theta) * xBase) - (sin(theta) * yBase);
  float py = ty + (sin(theta) * xBase) + (cos(theta) * yBase);
  GFX_VERTEX16 = ((u16)py << 16) | (u16)px;
  GFX_VERTEX16 = ul_currentDepth;
}

/*float Gesture::getScale() {
  return scale;
}*/

int Gesture::getPointsCount() {
  int pointsCount = 0;
  for (unsigned int i = 0; i < strokes.size(); i++) {
    pointsCount += strokes.at(i)->size();
  }
  return pointsCount;
}
