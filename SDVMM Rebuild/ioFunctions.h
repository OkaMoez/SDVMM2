#pragma once
#ifdef _DEBUG 
#define D(x) x
#include "debugConstants.h"
#else 
#define D(x)
#endif

#include <windows.h>
#include <fstream>
#include <iomanip>
#include <fileapi.h>
#include <wx/wupdlock.h>
#include <wx/stdpaths.h>
#include <wx/textfile.h>
#include "cMain.h"
using std::istream;
using std::ifstream;

string GetIniDirectory(FILE* ini);
bool existsFile(string file_path);