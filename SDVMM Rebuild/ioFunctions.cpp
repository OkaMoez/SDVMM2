#include "ioFunctions.h"

string getDirectory(FILE* ini)
{
	char iniBuffer[100];
	fgets(iniBuffer, 100, ini);
	string temp_string = string(iniBuffer);
	size_t temp_pos = temp_string.find('=');
	temp_string = temp_string.substr(temp_pos + 1, temp_string.size());
	temp_string.erase(std::remove(temp_string.begin(), temp_string.end(), '"'), temp_string.end());
	return temp_string;
}

bool fileExists(string file_name)
{
	if (FILE * iniFile = fopen(file_name.c_str(), "r")) {
		fclose(iniFile);
		return true;
	}
	else {
		return false;
	}
}