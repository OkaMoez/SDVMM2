#pragma once
#include "DebugTools.h"
#include "nlohmann/json.hpp" // There is a way to forward declare this, but I couldn't get it working
#include <string>
#include <wx/listctrl.h>

class SmapiMod
{
private:
	std::string _mName;
	std::string _mAuthor;
	std::string _mVersion;
	std::string _mDescription;
	std::string _mUniqueID;
	int _mVersionMajor;
	int _mVersionMinor;
	int _mVersionPatch;

	void _versionSplitSemvar();

public:
	SmapiMod();
	SmapiMod(std::string name, std::string author, std::string version, std::string description, std::string uId);
	SmapiMod(nlohmann::json& manifest);
	~SmapiMod() {}

	std::string name() const { return _mName; }
	std::string author() const { return _mAuthor; }
	std::string version() const { return _mVersion; }
	int versionMajor() const { return _mVersionMajor; }
	int versionMinor() const { return _mVersionMinor; }
	int versionPatch() const { return _mVersionPatch; }
	std::string description() const { return _mDescription; }
	std::string uniqueID() const { return _mUniqueID; }
	std::string infoString() const {
		return (_mName + ", " + _mAuthor + ", "
			+ _mVersion + ", " + _mDescription + ", "
			+ _mUniqueID + "\n"); 
	}

	void setName(std::string name);
	void setAuthor(std::string author);
	void setVersion(std::string version);
	void setDescription(std::string description);
	void setUniqueID(std::string uId);
};