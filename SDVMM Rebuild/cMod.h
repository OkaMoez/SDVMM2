#pragma once
#include <string>
#include <wx/listctrl.h>
#include "json.hpp"
using json = nlohmann::json;
using std::string;
using std::stoi;

class cMod
{
private:
	string mod_name_;
	string mod_author_;
	string mod_version_;
	int major_version_;
	int minor_version_;
	int patch_version_;
	string mod_description_;
	string mod_unique_id_;

	void set_intVersion();

public:
	cMod();
	cMod(string name, string auth, string ver, string desc, string uId);
	cMod(json& manifest);
	~cMod() {}

	string mod_name() const { return mod_name_; }
	string mod_author() const { return mod_author_; }
	string mod_version() const { return mod_version_; }
	int major_version() const { return major_version_; }
	int minor_version() const { return minor_version_; }
	int patch_version() const { return patch_version_; }
	string mod_description() const { return mod_description_; }
	string mod_unique_id() const { return mod_unique_id_; }
	string infoString() const {
		return (mod_name_ + " / " + mod_author_ + " / "
			+ mod_version_ + " / " + mod_description_ + " / "
			+ mod_unique_id_); }

	void set_mod_name(string name);
	void set_mod_author(string auth);
	void set_mod_version(string ver);
	void set_mod_description(string desc);
	void set_mod_unique_id(string uId);
};