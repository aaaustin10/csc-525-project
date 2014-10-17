#include "filereader.h"

FileReader::FileReader(char* filepath)
{
	path = filepath;
}

FileReader::~FileReader()
{
	file.close();
}

bool FileReader::init()
{
	file.open(path, std::ios::in | std::ios::binary);
	if (!file.good())
	{
		return false;
	}
	return true;
}

void FileReader::get_array(void* item, int req_size)
{
	file.seekg(0, std::ios::end);
	int real_size = file.tellg();
	if (req_size != real_size)
	{
		std::cout << "File read requested is not correct size" << std::endl;
		exit(0);
	}
	file.seekg(0, std::ios::beg);
	file.read((char*)item, req_size);
}