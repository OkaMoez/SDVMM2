#pragma once

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
bool existsFile(string file_name);
bool existsModFolders(fs::path path_in); //TODO
void formatOldVersion(json& manifest);
void refreshModLists(fs::path path_in, wxDataViewListCtrl* mod_list);
void loadModsFromDir(fs::path path_in, string folder_name, wxDataViewListCtrl* mod_list);