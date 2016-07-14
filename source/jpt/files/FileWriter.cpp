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
#include "FileWriter.h"

using namespace jlpt;

FileWriter::FileWriter(const char* name, int type):File(name, type) {
   // NOTHING TO DO
}

FileWriter::~FileWriter() {
   // NOTHING TO DO 
}

void FileWriter::open(char* mode) {
	File::open(mode);
}

size_t FileWriter::write(void * ptr, size_t size, size_t count) {
	if(file != NULL) {
   	return fwrite (ptr, size, count, file);
 	}
	// Fichier inexistant
	else {
		//ulDebug("Cannot read file\n");
	}
	return -1;
}
