#pragma once

#include <windows.h>
#include <fstream>
#include <iomanip>
#include <fileapi.h>
#include <wx/wupdlock.h>
#include <wx/textfile.h>
#include "cMod.h"
using std::istream;
using std::ifstream;

string GetIniDirectory(FILE* ini);
bool existsFile(string file_path);