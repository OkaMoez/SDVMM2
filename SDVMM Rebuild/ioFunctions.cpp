#include "IoFunctions.h"

std::string IoFunctions::getIniDirectory(FILE* ini)
{
	char iniBuffer[100];
	fgets(iniBuffer, 100, ini);
	std::string temp_string = std::string(iniBuffer);
	size_t temp_pos = temp_string.find('=');
	temp_string = temp_string.substr(temp_pos + 1, temp_string.size());
	temp_string.erase(std::remove(temp_string.begin(), temp_string.end(), '"'), temp_string.end());
	return temp_string;
}

bool IoFunctions::existsFile(std::string file_path)
{
	if (FILE * iniFile = fopen(file_path.c_str(), "r")) {
		fclose(iniFile);
		return true;
	}
	else {
		return false;
	}
}