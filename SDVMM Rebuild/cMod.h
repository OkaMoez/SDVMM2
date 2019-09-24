#pragma once
#include <string>
#include "json.hpp"
using json = nlohmann::json;
using std::string;
using std::stoi;

class cMod
{
private:
	string modName_ = "";
	string modAuthor_ = "";
	string modVersion_ = "";
	int majorVersion_ = NULL;
	int minorVersion_ = NULL;
	int patchVersion_ = NULL;
	string modDescription_ = "";
	string modUniqueID_ = "";

	void set_intVersion();

public:
	cMod();
	cMod(string name, string auth, string ver, string desc, string uId);
	cMod(json manifest);
	~cMod();

	string modName() { return modName_; }
	string modAuthor() { return modAuthor_; }
	string modVersion() { return modVersion_; }
	int majorVersion() { return majorVersion_; }
	int minorVersion() { return minorVersion_; }
	int patchVersion() { return patchVersion_; }
	string modDescription() { return modDescription_; }
	string modUniqueID() { return modUniqueID_; }

	void set_modName(string name);
	void set_modAuthor(string auth);
	void set_modVersion(string ver);
	void set_modDescription(string desc);
	void set_modUniqueID(string uId);
};