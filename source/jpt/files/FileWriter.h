#ifndef __FILE_WRITER_H__
#define __FILE_WRITER_H__

namespace jlpt {
	
	class FileWriter : public File {

		public:
			FileWriter(const char* name, int type);
			~FileWriter();
			void open(char* mode);
			size_t write(void * ptr, size_t size, size_t count);
	};
}

#endif // __FILE_WRITER_H__
