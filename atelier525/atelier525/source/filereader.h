#ifndef FILEREADER_H
	#define FILEREADER_H
	#include "includes.h"

	class FileReader{
	public:
		FileReader(char* filepath);
		~FileReader();
		bool init();
		void get_array(void* item, int req_size);

	private:
		char* path;
		std::fstream file;
	};
#endif // FILEREADER_H