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
	string tmp1, tmp2, tmp3, tmp4, tmp5;
	manifest["Name"].get_to(tmp1);
	manifest["Author"].get_to(tmp2);
	manifest["Version"].get_to(tmp3);
	manifest["Description"].get_to(tmp4);
	manifest["UniqueID"].get_to(tmp5);
	cMod(tmp1, tmp2, tmp3, tmp4, tmp5);
}

cMod::~cMod()
{

}

void cMod::set_intVersion() // TODO Handle Short Version Nums w/ minimal technical debt
{
	string temp_version = modVersion_;
	size_t temp_pos = temp_version.find('.');
	majorVersion_ = stoi(temp_version.substr(0, temp_pos));
	temp_version = temp_version.erase(0, temp_pos+1);
	temp_pos = temp_version.find('.');
	minorVersion_ = stoi(temp_version.substr(0, temp_pos));
	if (temp_pos = temp_version.size()) // Short version number "x.x"? kinda dumb
	{
		patchVersion_ = 0;
	}
	else // regular length x.x.x
	{
		temp_version = temp_version.erase(0, temp_pos + 1);
		patchVersion_ = stoi(temp_version.substr(0, temp_version.size()));
	}
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
