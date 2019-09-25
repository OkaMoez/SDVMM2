#pragma once

#include <windows.h>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <fileapi.h>
#include <wx/wupdlock.h>
#include "cMain.h"
#include "wxDirectoriesEnumerator.h"
namespace fs = std::filesystem;
using std::istream;
using std::ifstream;

string getDirectory(FILE* ini);
bool fileExists(string file_name);
void formatOldVersion(json& manifest);
void printDir(wxListBox* ListBox1, fs::path modDir);
void loadModsFromDir(fs::path path_in, wxDataViewListCtrl* mod_list);