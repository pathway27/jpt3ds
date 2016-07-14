#ifndef __FILE_H__
#define __FILE_H__

namespace jlpt {
	
	typedef enum {
	 ASCII = 0,
	 UNICODE = 1
	};
	
	class File {

		public:
			File(const char* name, int type);
			virtual ~File();
			virtual void open();
			void open(char* mode);
			void close();
			int seek(int offset);
			bool exists();
			long size();
			
		protected:
		   int fileType;
		   FILE* file;
		private:
		   const char* fileName;
	};
}

#endif // __FILE_H__
