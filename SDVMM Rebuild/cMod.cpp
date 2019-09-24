#include "cMod.h"


cMod::cMod() { cMod("Empty Mod", "Empty Mod", "Empty Mod", "Empty Mod", "Empty Mod"); }
cMod::cMod(string name, string auth, string ver, string desc, string uId)
{
	modName_ = name;
	modAuthor_ = auth;
	modVersion_ = ver;
	modDescription_ = desc;
	modUniqueID_ = uId;
	set_intVersion();
}
cMod::cMod(json manifest)
{
	cMod(string(manifest["Name"]), string(manifest["Author"]),
		string(manifest["Version"]), string(manifest["Description"]),
		string(manifest["UniqueID"]));
}

cMod::~cMod()
{

}

void cMod::set_intVersion()
{
	string temp_version = modVersion_;
	size_t temp_pos = temp_version.find('.');
	majorVersion_ = stoi(temp_version.substr(0, temp_pos));
	temp_version = temp_version.erase(0, temp_pos+1);
	temp_pos = temp_version.find('.');
	minorVersion_ = stoi(temp_version.substr(0, temp_pos));
	temp_version = temp_version.erase(0, temp_pos + 1);
	patchVersion_ = stoi(temp_version.substr(0, temp_version.size()));
}

void cMod::set_modName(string name)
{
	modName_ = name;
}

void cMod::set_modAuthor(string auth)
{
	modAuthor_ = auth;
}

void cMod::set_modVersion(string ver)
{
	modVersion_ = ver;
}

void cMod::set_modDescription(string desc)
{
	modDescription_ = desc;
}

void cMod::set_modUniqueID(string uId)
{
	modUniqueID_ = uId;
}
