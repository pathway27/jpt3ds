#include <ulib/ulib.h>
#include <PA9.h>
#include <fat.h>
#include <vector>
#include <string>
#include <cstdio>
#include "../geometry/Point.h"
#include "../geometry/Rectangle.h"
#include "../geometry/Dimension.h"
#include "../components/Component.h"
#include "File.h"
#include "FileReader.h"

using namespace jlpt;

FileReader::FileReader(const char* name, int type):File(name, type) {
   // NOTHING TO DO
}

FileReader::~FileReader() {
   // NOTHING TO DO 
}

size_t FileReader::read(void * ptr, size_t size, size_t count) {
	if(file != NULL) {
   	return fread (ptr, size, count, file);
 	}
	// Fichier inexistant
	else {
		//ulDebug("Cannot read file\n");
	}
	return -1;
}

char* FileReader::get(char * str, int num) {
  if(file != NULL) {
    return fgets(str, num, file);
  }
  return NULL;
}

const char* FileReader::getAscii(char* unicodeString, int size) {
   if(fileType == UNICODE) {
		// On prend en compte 1 caractere sur 2
		char ascii[size/2];
		for(int i = 0; i < size; i=i+2) {
			ascii[i/2] = unicodeString[i];
		}
		// Indique la fin de la chaine
		ascii[(size/2)-1] = '\0';
		
		std::string* asciiCopy = new std::string("");
		asciiCopy->append(ascii);
		return asciiCopy->data();
	}
	return NULL;
}

u16* FileReader::getKana(char* unicodeString, int size) {

	u16* kana = new u16[size/2];

   if(fileType == UNICODE) {
		for(int i = 0; i < size; i=i+2) {
		   if(unicodeString[i] != 0x20 && unicodeString[i+1] != 0x00) {
				// On inverse l'ordre des caracteres
				kana[i/2] = (unicodeString[i+1] << 8);
				kana[i/2] = kana[i/2] | unicodeString[i];
			} else {
				kana[i/2] = '\0';   
			}						
		}
		// Indique la fin de la chaine
		//kana[(size/2)-1] = '\0';
		
		return kana;
	}
	return NULL;
}
