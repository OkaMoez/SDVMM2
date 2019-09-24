#pragma once
#include <string>
using std::string;

class cMod
{
private:
	string modName_ = "";
	string modAuthor_ = "";
	string modVersion_ = "";
	string modDescription_ = "";
	string modUniqueID_ = "";

public:
	cMod();
	cMod(string name, string auth, string ver, string desc, string uId);
	string modName() { return modName_;	}
	string modAuthor() { return modAuthor_; }
	string modVersion() { return modVersion_; }
	string modDescription() { return modDescription_; }
	string modUniqueID() { return modUniqueID_; }

	void set_modName(string name);
	void set_modAuthor(string auth);
	void set_modVersion(string ver);
	void set_modDescription(string desc);
	void set_modUniqueID(string uId);
};