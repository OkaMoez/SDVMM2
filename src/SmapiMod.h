#pragma once
#include "DebugTools.h"
#include "nlohmann/json.hpp" // There is a way to forward declare this, but I couldn't get it working
#include "neargye/semver.hpp"
#include <string>
#include <wx/listctrl.h>

class SmapiMod
{
private:
	std::string _mName;
	std::string _mAuthor;
	semver::version _mVersion;
	std::string _mDescription;
	std::string _mUniqueID;

	semver::version _tryParseVersion(std::string version);

public:
	SmapiMod();
	SmapiMod(std::string name, std::string author, std::string version, std::string description, std::string uId);
	SmapiMod(std::string name, std::string author, semver::version version, std::string description, std::string uId);
	SmapiMod(nlohmann::json& manifest);
	~SmapiMod() {}

	std::string name() const { return _mName; }
	std::string author() const { return _mAuthor; }
	semver::version version() const { return _mVersion; }
	std::string description() const { return _mDescription; }
	std::string uniqueID() const { return _mUniqueID; }
	std::string infoString() const {
		return (_mName + ", " + _mAuthor + ", "
			+ _mVersion.to_string() + ", " + _mDescription + ", "
			+ _mUniqueID + "\n"); 
	}

	void setName(std::string name);
	void setAuthor(std::string author);
	void setVersion(std::string version);
	void setVersion(semver::version version);
	void setDescription(std::string description);
	void setUniqueID(std::string uId);
};