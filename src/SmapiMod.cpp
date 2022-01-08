#include "SmapiMod.h"

SmapiMod::SmapiMod() : SmapiMod("Empty Mod", "No author", "0.0.0", "An empty mod.", "No ID") {}

SmapiMod::SmapiMod(std::string name, std::string author, std::string version, std::string description, std::string uId)
	: SmapiMod(name, author, semver::from_string(version), description, uId) {
}

SmapiMod::SmapiMod(std::string name, std::string author, semver::version version, std::string description, std::string uId)
	: _mName(name)
	, _mAuthor(author)
	, _mVersion(version)
	, _mDescription(description)
	, _mUniqueID(uId) {
}

SmapiMod::SmapiMod(nlohmann::json& manifest) {
	using Index = Manifest::Index;
	const std::unordered_map<Manifest::Index, const char*>& key = Manifest::key;

	_mName = manifest[key.at(Index::name)].get<std::string>();
	_mAuthor = manifest[key.at(Index::author)].get<std::string>();
	_mVersion = _tryParseVersion(manifest[key.at(Index::version)].get<std::string>());
	_mDescription = manifest[key.at(Index::description)].get<std::string>();
	_mUniqueID = manifest[key.at(Index::uniqueId)].get<std::string>();
}

void SmapiMod::setName(std::string name) { _mName = name; }
void SmapiMod::setAuthor(std::string author) { _mAuthor = author; }
void SmapiMod::setVersion(std::string version) { _mVersion = _tryParseVersion(version); }
void SmapiMod::setVersion(semver::version version) { _mVersion = version; }
void SmapiMod::setDescription(std::string description) { _mDescription = description; }
void SmapiMod::setUniqueID(std::string uId) { _mUniqueID = uId; }

semver::version SmapiMod::_tryParseVersion(std::string versionString) {
	semver::version version;
	try {
		version = semver::from_string(versionString);
	}
	catch (std::invalid_argument const& ex) {
		DPRINT(ex.what());
		_mUsingSemver = false;
	}
	return version;
}
