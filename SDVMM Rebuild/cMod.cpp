#include "cMod.h"


cMod::cMod() { cMod("Empty Mod", "Empty Mod", "Empty Mod", "Empty Mod", "Empty Mod"); }
cMod::cMod(string name, string auth, string ver, string desc, string uId)
{
	modName_ = name;
	modAuthor_ = auth;
	modVersion_ = ver;
	modDescription_ = desc;
	modUniqueID_ = uId;
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
