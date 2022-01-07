#pragma once
#include "DebugTools.h"

#include <filesystem>
#include "nlohmann/json.hpp" // There is a way to forward declare this, but I couldn't get it working
#include <string>
#include <unordered_map>

class MainFrame;

enum class ModErrors {
	json,
	semver,
	format,
	formatLocal,
	smapi
};

enum class ModStatus {
	total,
	errored,
	loaded
};

class ManifestParser {
public:
	std::string mErrorLocations = "Errors at: ";

	std::unordered_map<ModErrors, bool> mErrorChecks
	{
		{ModErrors::json, false},
		{ModErrors::semver, false},
		{ModErrors::format, false},
		{ModErrors::formatLocal, false},
		{ModErrors::smapi, false}
	};

	std::unordered_map<ModErrors, int> mErrorCount
	{
		{ModErrors::json, 0},
		{ModErrors::semver, 0},
		{ModErrors::format, 0}
	};

	std::unordered_map<ModStatus, int> mModCount
	{
		{ModStatus::total, 0},
		{ModStatus::errored, 0},
		{ModStatus::loaded, 0}
	};

public:
	ManifestParser(MainFrame* main);
	~ManifestParser() = default;
	bool existsModFolders();
	void refreshModLists(); // TODO give some indication of the refresh

private:
	MainFrame* _mMainWindow = nullptr;

	void _cleanManifest(nlohmann::json& manifest, std::filesystem::path error_path);
	void _cleanJson(); // TODO tranfer code to function
	void _loadModsFromDir(std::string folderName);
	void _checkSmapiVersion();
	void _resetRefreshErrors(); // TODO format and move to getters/setters?
	void _showRefreshErrors();
};
