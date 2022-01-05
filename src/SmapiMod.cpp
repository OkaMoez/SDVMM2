#include "SmapiMod.h"

SmapiMod::SmapiMod() : SmapiMod("Empty Mod", "No author", "0.0.0", "An empty mod.", "No ID") {}
SmapiMod::SmapiMod(std::string name, std::string author, std::string version, std::string description, std::string uId)
	: _mName(name)
	, _mAuthor(author)
	, _mVersion(version)
	, _mDescription(description)
	, _mUniqueID(uId) {
	_versionSplitSemvar();
}
SmapiMod::SmapiMod(nlohmann::json& manifest) {
	_mName = manifest["Name"].get<std::string>();
	_mAuthor = manifest["Author"].get<std::string>();
	_mVersion = manifest["Version"].get<std::string>();
	_mDescription = manifest["Description"].get<std::string>();
	_mUniqueID = manifest["UniqueID"].get<std::string>();
	_versionSplitSemvar();	
}

void SmapiMod::setName(std::string name) { _mName = name; }
void SmapiMod::setAuthor(std::string author) { _mAuthor = author; }
void SmapiMod::setVersion(std::string version) { _mVersion = version; }
void SmapiMod::setDescription(std::string description) { _mDescription = description; }
void SmapiMod::setUniqueID(std::string uId) { _mUniqueID = uId; }

void SmapiMod::_versionSplitSemvar() {
	std::string versionTemp = _mVersion;
	size_t position = versionTemp.find('.');
	_mVersionMajor = stoi(versionTemp.substr(0, position));
	versionTemp = versionTemp.erase(0, position + 1);
	position = versionTemp.find('.');
	_mVersionMinor = stoi(versionTemp.substr(0, position));
	if (position != std::string::npos) { // regular length x.x.x
		versionTemp = versionTemp.erase(0, position + 1);
		_mVersionPatch = stoi(versionTemp.substr(0, versionTemp.size()));
	}
	else {
		DPRINT("Unable to parse version number.");
	}
}

