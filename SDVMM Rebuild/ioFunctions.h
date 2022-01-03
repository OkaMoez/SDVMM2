#pragma once
#include <fstream>

namespace IoFunctions {
	std::string getIniDirectory(FILE* ini);
	bool existsFile(std::string file_path);
}
