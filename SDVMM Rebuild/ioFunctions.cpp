#include "IoFunctions.h"

std::string IoFunctions::getIniDirectory(FILE* ini) {
	char iniBuffer[100];
	fgets(iniBuffer, 100, ini);
	std::string tempString = std::string(iniBuffer);
	size_t tempPos = tempString.find('=');
	tempString = tempString.substr(tempPos + 1, tempString.size());
	tempString.erase(std::remove(tempString.begin(), tempString.end(), '"'), tempString.end());
	return tempString;
}

bool IoFunctions::existsFile(std::string filePath) {
	if (FILE * iniFile = fopen(filePath.c_str(), "r")) {
		fclose(iniFile);
		return true;
	}
	else {
		return false;
	}
}