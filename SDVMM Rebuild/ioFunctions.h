#include "cMain.h"
#include "wxDirectoriesEnumerator.h"

string getDirectory(FILE* ini);
bool fileExists(string file_name);
void formatOldVersion(json& manifest);