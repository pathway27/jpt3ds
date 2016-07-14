#include <ulib/ulib.h>
#include <vector>
#include "../geometry/Point.h"
#include "../geometry/Dimension.h"
#include "../geometry/Rectangle.h"
#include "Component.h"
#include "Image.h"

using namespace jlpt;

Image::Image(Component* parent, char* imageName):Component(parent, imageName) {
 	type = TYPE_IMAGE;
}
   
Image::~Image() {
   // NOTHING TO DO
}
