#include <ulib/ulib.h>
#include <vector>
#include <math.h>
#include "../files/File.h"
#include "../files/FileWriter.h"
#include "../files/FileReader.h"
#include "../geometry/Point.h"
#include "../geometry/Dimension.h"
#include "../geometry/Rectangle.h"
#include "../Commands.h"
#include "../Tools.h"
#include "Component.h"
#include "../data/Stroke.h"
#include "../data/Gesture.h"
#include "DrawComponent.h"

using namespace jlpt;

DrawComponent::DrawComponent(Component* parent) :
  Component(parent) {
  type = TYPE_DRAW;
  gesture = new Gesture(this, false);
  this->add(gesture);
  memorizedGesture = new Gesture(this, true);
  this->add(memorizedGesture);
  drawing = false;
  matchScore = 0.0f;
  this->addColor(RGB15(0, 0, 0));
  this->addColor(RGB15(31, 31, 31));
  selectedGesture = 0;
  read(selectedGesture);
}

DrawComponent::~DrawComponent() {
  delete gesture;
}

void DrawComponent::setSize(int width, int height) {
  Component::setSize(width, height);
  gesture->setSize(width, height);
}

void DrawComponent::clear() {
  matchScore = 0;
  if (!gesture->empty()) {
    gesture->clear();
  } else {
    memorizedGesture->clear();
  }
}

void DrawComponent::normalize() {
  gesture->normalize();
}

void DrawComponent::memorize() {
  // On jete l'ancien dessin
  memorizedGesture->clear();
  Stroke* stroke;
  Point* point;

  // On copie le dessin
  for (unsigned int i = 0; i < gesture->size(); i++) {
    memorizedGesture->addStroke();
    stroke = gesture->at(i);
    for (unsigned int j = 0; j < stroke->size(); j++) {
      point = stroke->at(j);
      memorizedGesture->addPoint(point->getX(), point->getY(), false);
    }
  }

  // On efface le dessin d'origine
  gesture->clear();
}

int DrawComponent::dealEvent(SCREEN scr) {
  if (visible && screen == scr) {
    if (ul_keys.touch.held && this->containsStylus()) {
      if (!drawing) {
        drawing = true;
        gesture->addStroke();
      }
      gesture->addPoint(ul_keys.touch.x - getX(), ul_keys.touch.y - getY(),
          true);
    }
    // Relachement du stylet
    else if (ul_keys.touch.released && drawing) {
      drawing = false;
    }
  }
  return CMD_NONE;
}

void DrawComponent::display(SCREEN scr) {
  Component::display(scr);
  if (visible && screen == scr) {
    ulDrawLine(getX() + getWidth()/2, getY(), getX() + getWidth()/2, getY()
        + getHeight(), RGB15(25, 25, 25));
    ulDrawLine(getX(), getY() + getHeight()/2, getX() + getWidth(), getY()
        + getHeight()/2, RGB15(25, 25, 25));
    memorizedGesture->display();
    gesture->display();
    // Scale + NbStrokes
    char buffer[50];
    if (gesture->size() > 0) {
      sprintf(buffer, "Strokes: %d Points: %d", gesture->size(),
          gesture->getPointsCount());
    } else {
      sprintf(buffer, "Strokes: %d Points: %d", memorizedGesture->size(),
          memorizedGesture->getPointsCount());
    }
    drawShadowedText(buffer, 20, 5, getColor(0), getColor(1));
    // Match score
    if (gesture->size() > 0) {
      int pourcentScore = ((int)(matchScore*1000))/10;
      sprintf(buffer, "Matching score: %d%%", pourcentScore);
      drawShadowedText(buffer, 25, 180, getColor(0), getColor(1));
    }
    // Kanji number
    sprintf(buffer, "%d/%d", selectedGesture+1, getNbGestures());
    drawShadowedText(buffer, 200, 77, getColor(0), getColor(1));
  }
}

float DrawComponent::gestureDotProduct(Gesture* gesture1, Gesture* gesture2) {
  if (gesture1->size() != gesture2->size()) {
    return -1;
  }

  float dotProduct = 0.0f;
  Stroke* stroke1, *stroke2;
  Point* pt1, *pt2;
  for (unsigned int i = 0; i < gesture1->size(); i++) {
    stroke1 = gesture1->at(i);
    stroke2 = gesture2->at(i);

    if (stroke1->size() != stroke2->size()) {
      return -1;
    }

    for (unsigned int j = 0; j < stroke1->size(); j++) {
      pt1 = stroke1->at(j);
      pt2 = stroke2->at(j);
      dotProduct += pt1->getX() * pt2->getX() + pt1->getY() * pt2->getY();
    }
  }

  return dotProduct;
}

float DrawComponent::match(Gesture* gesture1, Gesture* gesture2) {
  float score = gestureDotProduct(gesture1, gesture2);
  if (score <= 0.0f)
    return 0.0f; //No match for sure
  //at this point our gesture-vectors are not quite normalized
  //yet - their dot product with themselves is not 1.
  //we normalize the score itself
  //this is basically a version of a famous formula for a cosine of the 
  //angle between 2 vectors:
  //cos a = (u.v) / (sqrt(u.u) * sqrt(v.v)) = (u.v) / sqrt((u.u) * (v.v))
  score /= sqrtf(gestureDotProduct(gesture1, gesture1) * gestureDotProduct(
      gesture2, gesture2));
  return score;
}

void DrawComponent::compare() {
  matchScore = match(gesture, memorizedGesture);
}

void DrawComponent::write(int index) {
  // Liberation de la memoire
  gesture->clear();

  // Y a-t-il qqchose a sauvegarder?
  if (memorizedGesture->size() > 0) {
    // Ouverture du fichier de sauvegarde
    FileWriter* fileWriter = new FileWriter("/JLPT4/drawings.db", ASCII);
    // Append
    if (index == -1) {
      fileWriter->open("ab+");
    }
    // Replace
    else {
      fileWriter->open("rb+");
      if (!fileWriter->exists()) {
        // Si le fichier n'existe pas, on le cree
        fileWriter->open("ab+");
      } else {
        fileWriter->seek(index*sizeof(GESTURE));
      }
    }

    // Copie des donnees
    GESTURE gesture;
    Stroke* memStroke = NULL;
    Point* memPoint = NULL;
    for (unsigned int i = 0; i < STROKE_PER_GESTURE; i++) {
      STROKE stroke;
      if (i < memorizedGesture->size()) {
        memStroke = memorizedGesture->at(i);
        for (unsigned int j = 0; j < POINTS_PER_STROKE; j++) {
          POINT point;
          if (j < memStroke->size()) {
            memPoint = memStroke->at(j);
            point.x = memPoint->getX();
            point.y = memPoint->getY();
          } else {
            point.x = -1;
            point.y = -1;
          }
          stroke.points[j] = point;
        }
      } else {
        for (unsigned int j = 0; j < POINTS_PER_STROKE; j++) {
          POINT point;
          point.x = -1;
          point.y = -1;
          stroke.points[j] = point;
        }
      }
      gesture.strokes[i] = stroke;
    }

    // Ecriture des donnees
    fileWriter->write(&gesture, sizeof(GESTURE), 1);

    // Fermeture du fichier
    fileWriter->close();
  }
}

void DrawComponent::append() {
  if (memorizedGesture->size() > 0) {
    write(-1);
    // On se positionne sur le caractere 
    // Fraichement ajoute en fin de fichier
    selectedGesture = getNbGestures() - 1;
  }
}

void DrawComponent::replace() {
  if (memorizedGesture->size() > 0) {
    write(selectedGesture);
  }
}

void DrawComponent::left(u8 increment) {
  if (selectedGesture > increment - 1) {
    selectedGesture = selectedGesture - increment;
  } else {
    selectedGesture = 0;
  }
  read(selectedGesture);
}

void DrawComponent::right(u8 increment) {
  int nbGestures = getNbGestures();
  if (selectedGesture < nbGestures - increment) {
    selectedGesture = selectedGesture + increment;
  } else {
    selectedGesture = nbGestures - 1;
  }
  read(selectedGesture);
}

void DrawComponent::read(int index) {
  // Liberation de la memoire
  gesture->clear();
  memorizedGesture->clear();

  // Ouverture du fichier de sauvegarde
  FileReader* fileReader = new FileReader("/JLPT4/drawings.db", ASCII);
  fileReader->open("rb");

  // Libfat ok
  if (fileReader->exists()) {
    GESTURE gesture;
    STROKE stroke;
    POINT point;

    // Recherche du bloc de donnees dans le fichier
    if (fileReader->seek(index*sizeof(GESTURE))) {
      // Fermeture du fichier
      fileReader->close();
      return;
    }

    // Lecture des donnees
    fileReader->read(&gesture, sizeof(GESTURE), 1);

    // Fermeture du fichier
    fileReader->close();

    for (unsigned int i = 0; i < STROKE_PER_GESTURE; i++) {
      stroke = gesture.strokes[i];
      for (unsigned int j = 0; j < POINTS_PER_STROKE; j++) {
        point = stroke.points[j];
        // Faut-il creer la ligne?
        if (j == 0) {
          if (point.x == -1 || point.y == -1) {
            return;
          } else {
            memorizedGesture->addStroke();
          }
        }
        memorizedGesture->addPoint(point.x, point.y, false);
      }
    }
  }
}

int DrawComponent::getNbGestures() {
  int nbGestures = 0;
  FileReader* fileReader = new FileReader("/JLPT4/drawings.db", ASCII);
  fileReader->open("rb");
  if (fileReader->exists()) {
    long fileSize = fileReader->size();
    nbGestures = fileSize/sizeof(GESTURE);
    fileReader->close();
  }
  return nbGestures;
}
