#include <ulib/ulib.h>
#include <PA9.h>
#include <fat.h>
#include <vector>
#include <string>
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"
#include "../geometry/Dimension.h"
#include "../components/Component.h"
#include "File.h"

using namespace jlpt;

File::File(const char* name, int type) {
  fileName = name;
  fileType = type;
  file = NULL;
}

File::~File() {
  delete fileName;
  close();
}

void File::close() {
  if (file != NULL) {
    fclose(file);
    file = NULL;
  }
}

int File::seek(int offset) {
  if (file != NULL) {
    if (fileType == UNICODE) {
      return fseek(file, offset+2, SEEK_SET);
    } else {
      return fseek(file, offset, SEEK_SET);
    }
  }
  return -1;
}

void File::open() {
  // Par defaut ouverture en lecture seule
  open("rb");
}

void File::open(char* mode) {
  if (fileName != NULL && strlen(fileName) > 0) {
    file = fopen(fileName, mode);

    if (file != NULL) {
      // Lecture de l'en-tete unicode
      if (fileType == UNICODE) {
        char c[2];
        fread(&c, sizeof(c), 1, file);
      }
    }
    // Fichier inexistant
    else {
      //ulDebug("File %s does not exist\n", fileName);   
    }
  }
  // Nom de fichier vide
  else {
    //ulDebug("File name is empty\n");	   
  }
}

bool File::exists() {
  if (file == NULL) {
    return false;
  }
  return true;
}

long File::size() {
  if(file == NULL) {
    return 0;
  }
  fseek(file, 0, SEEK_END);
  return ftell(file);
}
