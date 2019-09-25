#pragma once

#include <filesystem>
#include "cMain.h"
#include "wxDirectoriesEnumerator.h"
namespace fs = std::filesystem;

string getDirectory(FILE* ini);
bool fileExists(string file_name);
void formatOldVersion(json& manifest);
void printDir(wxListBox* ListBox1, fs::path modDir);