#ifndef __FILE_READER_H__
#define __FILE_READER_H__

namespace jlpt {
	
	class FileReader : public File {

		public:
			FileReader(const char* name, int type);
			~FileReader();
			size_t read(void * ptr, size_t size, size_t count);
			char* get(char * str, int num);
			const char* getAscii(char* unicodeString, int size);
			u16* getKana(char* unicodeString, int size);
	};
}

#endif // __FILE_READER_H__
