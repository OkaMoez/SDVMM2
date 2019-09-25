#include "cMod.h"


cMod::cMod() : cMod("Empty Mod", "No Author", "0.0.0", "An empty mod.", "No ID") {}
cMod::cMod(string name, string auth, string ver, string desc, string uId) :  wxListItem()
{
	set_mod_name(name);
	set_mod_author(auth);
	set_mod_version(ver);
	set_mod_description(desc);
	set_mod_unique_id(uId);
	set_intVersion();
}
cMod::cMod(json& manifest) : wxListItem()
{
	string name, auth, ver, desc, uId;
	manifest["Name"].get_to(name);
	manifest["Author"].get_to(auth);
	manifest["Version"].get_to(ver);
	manifest["Description"].get_to(desc);
	manifest["UniqueID"].get_to(uId);
	set_mod_name(name); // TODO Make pretty
	set_mod_author(auth);
	set_mod_version(ver);
	set_mod_description(desc);
	set_mod_unique_id(uId);
	set_intVersion();	
}

void cMod::set_mod_name(string name) { mod_name_ = name; }
void cMod::set_mod_author(string auth) { mod_author_ = auth; }
void cMod::set_mod_version(string ver) { mod_version_ = ver; }
void cMod::set_mod_description(string desc) { mod_description_ = desc; }
void cMod::set_mod_unique_id(string uId) { mod_unique_id_ = uId; }

void cMod::set_intVersion() // TODO Handle Short Version Nums w/ minimal technical debt
{
	string temp_version = mod_version_;
	size_t temp_pos = temp_version.find('.');
	major_version_ = stoi(temp_version.substr(0, temp_pos));
	temp_version = temp_version.erase(0, temp_pos+1);
	temp_pos = temp_version.find('.');
	minor_version_ = stoi(temp_version.substr(0, temp_pos));
	if (temp_pos = temp_version.size()) // Short version number "x.x"? kinda dumb
	{
		patch_version_ = 0;
	}
	else // regular length x.x.x
	{
		temp_version = temp_version.erase(0, temp_pos + 1);
		patch_version_ = stoi(temp_version.substr(0, temp_version.size()));
	}
}

