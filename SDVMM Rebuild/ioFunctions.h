#pragma once
#ifdef _DEBUG 
#define D(x) x
#include "debugConstants.h"
#else 
#define D(x)
#endif

#include <windows.h>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <fileapi.h>
#include <wx/wupdlock.h>
#include "cMain.h"
namespace fs = std::filesystem;
using std::istream;
using std::ifstream;

string getDirectory(FILE* ini);
bool existsFile(string file_path);