#include "ManifestParser.h"

#include <fstream>
#include "JsonCleaner.h"
#include "MainFrame.h"
#include "ModBrowserPanel.h"
#include "SettingsPanel.h"
#include "SmapiMod.h"
#include "StatusBar.h"
#include <wx/wupdlock.h>
#include <wx/wx.h>

ManifestParser::ManifestParser(MainFrame* main)
	: _mMainWindow(main) {
}

void ManifestParser::_cleanManifest(nlohmann::json& manifest, std::filesystem::path errorPath) { // TODO move check to refresh and make flag

	if (!manifest.contains("Name")) {
		mErrorChecks[ModErrors::format] = true;
		mErrorChecks[ModErrors::formatLocal] = true;
		mErrorCount[ModErrors::format]++;
		std::string temp = "";
		if (manifest.contains("name")) {
			manifest["name"].get_to(temp);
			manifest["Name"] = temp;
			manifest.erase("name");
		}
		else {
			manifest["Name"] = temp;
		}
		DPRINT(errorPath.string() + " Manifest Error - Name\n");
	}
	if (!manifest.contains("Author")) {
		mErrorChecks[ModErrors::format] = true;
		mErrorChecks[ModErrors::formatLocal] = true;
		mErrorCount[ModErrors::format]++;
		std::string temp = "";
		if (manifest.contains("author")) {
			manifest["author"].get_to(temp);
			manifest["Author"] = temp;
			manifest.erase("author");
		}
		else
		{
			manifest["Author"] = temp;
		}
		DPRINT(errorPath.string() + " Manifest Error - Author\n");
	}
	if (!manifest.contains("Version")) {
		mErrorChecks[ModErrors::format] = true;
		mErrorChecks[ModErrors::formatLocal] = true;
		mErrorCount[ModErrors::format]++;
		std::string temp = "";
		if (manifest.contains("version")) {
			manifest["version"].get_to(temp);
			manifest["Version"] = temp;
			manifest.erase("version");
		}
		else
		{
			manifest["Version"] = temp;
		}
		DPRINT(errorPath.string() + " Manifest Error - Version\n");
	}
	else if (manifest["Version"].is_object()) {
		// flag outdated version object and make readable
		mErrorChecks[ModErrors::semver] = true;
		mErrorCount[ModErrors::semver]++;
		mErrorLocations += "\n" + errorPath.string() + " - Depreciated Versioning";
		std::string versionString = "";
		int majorVersion = manifest["Version"]["MajorVersion"].get<int>();
		int minorVersion = manifest["Version"]["MinorVersion"].get<int>();
		int patchVersion = manifest["Version"]["PatchVersion"].get<int>();
		versionString = std::to_string(majorVersion)
			+ "." + std::to_string(minorVersion)
			+ "." + std::to_string(patchVersion);
		manifest.erase("Version");
		manifest["Version"] = versionString;
	}
	if (!manifest.contains("Description")) {
		mErrorChecks[ModErrors::format] = true;
		mErrorChecks[ModErrors::formatLocal] = true;
		mErrorCount[ModErrors::format]++;
		std::string temp = "";
		if (manifest.contains("description")) {
			manifest["description"].get_to(temp);
			manifest["Description"] = temp;
			manifest.erase("description");
		}
		else
		{
			manifest["Description"] = temp;
		}
		DPRINT(errorPath.string() + " Manifest Error - Description\n");
	}
	if (!manifest.contains("UniqueID")) {
		mErrorChecks[ModErrors::format] = true;
		mErrorChecks[ModErrors::formatLocal] = true;
		mErrorCount[ModErrors::format]++;
		std::string temp = "";
		if (manifest.contains("uniqueID")) {
			// if bad case, fix case (more work needed)
		}
		else
		{
			manifest["UniqueID"] = temp;
		}
		DPRINT(errorPath.string() + " Manifest Error - UniqueID\n");
	}
	if (mErrorChecks[ModErrors::formatLocal] == true) {
		mModCount[ModStatus::errored]++;
		mErrorLocations += "\n" + errorPath.string() + " - Manifest Formatting";
	}
}

void ManifestParser::refreshModLists() {
	_resetRefreshErrors();
	wxWindowUpdateLocker noUpdates(_mMainWindow->mModBrowserPanel->mModBrowserDataviewlistctrl);
	_mMainWindow->mModBrowserPanel->mModBrowserDataviewlistctrl->DeleteAllItems();

	try { _loadModsFromDir("\\Mods\\"); }
	catch (...) {
		wxMessageDialog* errorLoadMods = new wxMessageDialog(NULL,
			wxT("Fatal error attempting to refresh active mods."),
			wxT("Refresh Error"), wxOK, wxDefaultPosition);
		errorLoadMods->ShowModal();
		delete errorLoadMods;
	}

	try { _loadModsFromDir("\\Mods_disabled\\"); }
	catch (...) {
		wxMessageDialog* errorLoadModsD = new wxMessageDialog(NULL,
			wxT("Fatal error attempting to refresh inactive mods."),
			wxT("Refresh Error"), wxOK, wxDefaultPosition);
		errorLoadModsD->ShowModal();
		delete errorLoadModsD;
	}

	_mMainWindow->mModBrowserPanel->mModBrowserDataviewlistctrl->GetModel()->Resort();
	_mMainWindow->mStatusBar->setModLoadingStatus(mModCount[ModStatus::loaded], mModCount[ModStatus::total]); // TODO: swap to proper accessor
	_showRefreshErrors();
}

void ManifestParser::_loadModsFromDir(std::string folderName) {
	// TODO group and report errors in scrollable dialogue (bad jsons, incompatible mods, etc.)
	// TODO replace custom ioFunctions with filesystem?
	std::filesystem::path targetDirectory = (_mMainWindow->mSettingsPanel->gameDirectory());
	targetDirectory += folderName;
	std::filesystem::path tempPath;
	std::filesystem::path errorPath;
	bool isActive = (folderName == "\\Mods\\");
	//int errorJson = 0; // 0 = no error, 1 = bad comma, 2 = other

	DPRINT("mLoadModsFromDir - Begin Iterator at:\n" + _mMainWindow->mSettingsPanel->gameDirectory().string() + "\n");
	for (auto& directoryIterator : std::filesystem::recursive_directory_iterator(targetDirectory)) {
		mErrorChecks[ModErrors::json] = false;
		mErrorChecks[ModErrors::formatLocal] = false;
		errorPath = directoryIterator.path().filename();
		tempPath = directoryIterator.path();
		DPRINTIF(REPORT_MOD_DIRECTORY, tempPath.string() + "\n");

		if (!std::filesystem::is_directory(tempPath)) {
			DPRINTIF(REPORT_MOD_DIRECTORY & REPORT_IDENTIFY_DIRECTORIES, " - Is NOT Directory\n");
			continue;
		}
		DPRINTIF(REPORT_MOD_DIRECTORY & REPORT_IDENTIFY_DIRECTORIES, " - Is Directory\n");

		tempPath += "\\manifest.json";
		if (!std::filesystem::exists(tempPath)) {
			continue;
		}
		//DPRINTIF(???, " - Manifest found.\n");

		mModCount[ModStatus::total]++;
		std::ifstream jsonStream(tempPath.c_str(), std::ios::in | std::ios::binary);
		nlohmann::json jsonManifest;
		try	{
			try	{ // Parse json
				jsonManifest = nlohmann::json::parse(jsonStream, nullptr, true, true); // TODO handle trailing commas
				// Handle some minor typos and missing fields in manifest
				_cleanManifest(jsonManifest, errorPath);
			}
			catch (nlohmann::json::parse_error& e) { // On fail, output error and skip to next mod
				mErrorChecks[ModErrors::json] = true;
				++mErrorCount[ModErrors::json];
				++mModCount[ModStatus::errored];
				if (e.id != 101) {
					mErrorLocations += "\n" + errorPath.string() + " - JSON Formatting";
					continue;
				}
				mErrorLocations += "\n" + errorPath.string() + " - JSON Unexpected Char";
				// TODO clean commas and comments, then try again
				///*
				DPRINTIF(REPORT_JSON_FIX, "Json Fix Attempt\n");
				uintmax_t manifestSize = std::filesystem::file_size(tempPath);
				std::string jsonString(manifestSize, '\0');
				jsonStream.read(&jsonString[0], manifestSize);

				DPRINTIF(REPORT_JSON_FIX, "Json Fix RAW\n" + jsonString + "\n");

				// REVIEW: Can these thow exceptions?
				try {
					jsonString = stripComments(jsonString, true);
				}
				catch (...) {
					DPRINTIF(REPORT_JSON_FIX, "Json Fix Comment Clean Failure\n");
				}

				DPRINTIF(REPORT_JSON_FIX, "Json Fix Comment Cleaned\n" + jsonString + "\n");

				try {
					jsonString = stripTrailingCommas(jsonString, true);
				}
				catch (const std::regex_error& e) {
					std::string temp = e.what();
					DPRINTIF(REPORT_JSON_FIX, "Json Fix Comma Clean Failure: " + temp + "\n");
				}

				DPRINTIF(REPORT_JSON_FIX, "Json Fix Comma Cleaned\n" + jsonString + "\n");

				try {
					jsonManifest = nlohmann::json::parse(jsonString); // TODO handle trailing commas
					// Handle some minor typos and missing fields in manifest
					_cleanManifest(jsonManifest, errorPath);
					mErrorChecks[ModErrors::json] = false;
					DPRINTIF(REPORT_JSON_FIX, "Json Fix Reparse Success\n");
				}
				catch (nlohmann::json::parse_error& e) {
					DPRINTIF(REPORT_JSON_FIX, "Json Fix Reparse Failure\n" + std::string(e.what()));
					continue;
				}
				//*/
			}

			if (mErrorChecks[ModErrors::json] == true) { // TODO Review
				continue;
			}
			DPRINTIF(REPORT_ON_MOD_PARSED,
				jsonManifest["Name"].get<std::string>() + " exists, "
				+ jsonManifest["Version"].get<std::string>() + "\n");

			SmapiMod aMod(jsonManifest);
			if (!aMod.isSemver()) {
				++mErrorCount[ModErrors::semver];
				++mModCount[ModStatus::errored];
				mErrorLocations += "\n" + errorPath.string() + " - Unexpected Version Format";
			}

			wxVector<wxVariant> thisMod;
			thisMod.push_back(wxVariant(isActive));
			thisMod.push_back(wxVariant(aMod.name()));
			thisMod.push_back(wxVariant(aMod.author()));
			thisMod.push_back(wxVariant(aMod.version().to_string()));
			thisMod.push_back(wxVariant((directoryIterator.path()).string()));
			_mMainWindow->mModBrowserPanel->mModBrowserDataviewlistctrl->AppendItem(thisMod);
			++mModCount[ModStatus::loaded];
			thisMod.clear();
			DPRINTIF(REPORT_VERBOSE_MOD_OBJECTS, aMod.infoString());
		}
		catch (...) {
			mErrorLocations += "\n" + errorPath.string() + " - Fatal";
		}
	}
}

bool ManifestParser::existsModFolders() { // TODO: change disable to use '.'
	std::filesystem::path modPath = _mMainWindow->mSettingsPanel->gameDirectory();
	std::filesystem::path modPathDisabled = _mMainWindow->mSettingsPanel->gameDirectory();
	std::filesystem::path gamePath = _mMainWindow->mSettingsPanel->gameDirectory();
	modPath += "\\Mods";
	modPathDisabled += "\\Mods_disabled";
	gamePath += "\\Stardew Valley.exe"; // TODO Make crossplatform?

	DPRINT("mExistsModFolders - Begin Checking Mod Folders\n");

	if (!(std::filesystem::exists(gamePath) and std::filesystem::is_regular_file(gamePath))) {
		DPRINT("mExistsModFolders - Game Executable not Found on Path:\n"
			+ gamePath.string() + "\n" + "mExistsModFolders - Bad Game Directory\n");
		return false;
	}
	else
	{
		if (!(std::filesystem::exists(modPath) and std::filesystem::is_directory(modPath))) {
			DPRINT("mExistsModFolders - Mods Folder not Found\n");
			std::filesystem::create_directory(modPath);
			DPRINT("mExistsModFolders - Mods Folder Created at:\n" + modPath.string() + "\n");
		}
		else
		{
			DPRINT("mExistsModFolders - Mods Directory Found on Path:\n" + modPath.string() + "\n");
		}
		if (!(std::filesystem::exists(modPathDisabled) and std::filesystem::is_directory(modPathDisabled))) {
			DPRINT("mExistsModFolders - Mods_disabled Folder not Found\n");
			std::filesystem::create_directory(modPathDisabled);
			DPRINT("mExistsModFolders - Mods_disabled Folder Created at:\n" + modPathDisabled.string() + "\n");
		}
		else
		{
			DPRINT("mExistsModFolders - Mods Directory Found on Path:\n" + modPathDisabled.string() + "\n");
		}
	}
	return true;
}

void ManifestParser::_resetRefreshErrors() {
	mErrorLocations = "Errors at: ";
	mErrorChecks[ModErrors::json] = false;
	mErrorChecks[ModErrors::semver] = false;
	mErrorChecks[ModErrors::format] = false;
	mErrorChecks[ModErrors::formatLocal] = false;
	mErrorCount[ModErrors::json] = 0;
	mErrorCount[ModErrors::semver] = 0;
	mErrorCount[ModErrors::format] = 0;
	mModCount[ModStatus::total] = 0;
	mModCount[ModStatus::errored] = 0;
	mModCount[ModStatus::loaded] = 0;
}

void ManifestParser::_showRefreshErrors() {
	bool errorsExist = ((mErrorCount[ModErrors::json] != 0)
		or (mErrorCount[ModErrors::semver] != 0)
		or (mErrorCount[ModErrors::format] != 0));
	if (!errorsExist or (_mMainWindow->mSettingsPanel->mMuteErrors["on_refresh"] == true)) {
		return;
	}
	// Error counter dialogue prep
	std::string errorModLoopTitle = "Errors in Mods";
	std::string errorModLoopMessage =
		("Manifests with incorrect .json format: " + std::to_string(mErrorCount[ModErrors::json])
			+ "\nManifests with depreciated versioning: " + std::to_string(mErrorCount[ModErrors::semver])
			+ "\nManifests with other formatting errors: " + std::to_string(mErrorCount[ModErrors::format]));
	// if (!isActive) { final_error_title += "_disabled"; };
	// Error counter dialogue
	wxMessageDialog* errorModLoop = new wxMessageDialog(NULL,
		errorModLoopMessage, errorModLoopTitle, wxOK, wxDefaultPosition);
	errorModLoop->ShowModal();
	delete errorModLoop;
	if (mErrorChecks[ModErrors::semver]) {
		mErrorLocations += ("\n\nNOTE:\nSMAPI does not load mods with depreciated versioning.\nSee SMAPI logs or console for more details.");
	}
	wxMessageDialog* errorModLoopDetailed = new wxMessageDialog(NULL,
		mErrorLocations, errorModLoopTitle, wxOK, wxDefaultPosition);
	errorModLoopDetailed->ShowModal();
	delete errorModLoopDetailed;
	return;
}
