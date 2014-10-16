#ifndef FILEREADER
#define FILEREADER
#include <string>
#include <fstream>
class FileReader{
public:
	FileReader(std::string filepath) :
		path(filepath){}
	~FileReader(){
		fin.close();
	}
	bool init(){
		fin.open(path);
		if (!fin.is_open()){
			return false;
		}
		return true;
	}
	template <class T>
	void getItem(T &item){
		fin >> item;
	}

private:
	std::string path;
	std::ifstream fin;

	FileReader(const FileReader&) = delete;
	FileReader& operator=(const FileReader&) = delete;

};
#endif