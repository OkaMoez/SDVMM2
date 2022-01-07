#include "MainFrame.h"

#include "JsonCleaner.h"
#include "LauncherButtonPanel.h"
#include "MenuBar.h"
#include "ModBrowserPanel.h"
#include "SettingsPanel.h"
#include "StatusBar.h"


MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Stardew Valley Mod Manager 2",
	wxDefaultPosition, wxSize(750, 500),
	wxDEFAULT_FRAME_STYLE) {
	SetMinSize(wxSize(750, 500));

	//---------------------------
	//  Notebook Implementation
	//---------------------------
	mTabbedNotebook = new wxNotebook(this, -1);

	mModBrowserPanel = new ModBrowserPanel(this, mTabbedNotebook, wxID_ANY);
	mSettingsPanel = new SettingsPanel(this, mTabbedNotebook, wxID_ANY);

	mTabbedNotebook->AddPage(mModBrowserPanel, "SMAPI Mods", true);
	mTabbedNotebook->AddPage(mSettingsPanel, "Settings", false);

	//---------------------------------
	//  Additional GUI Implementation
	//---------------------------------

	// Launcher buttons
	mLauncherPanel = new LauncherButtonPanel(this, this, wxID_ANY);

	// Horizontal layout
	mMainFrameHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
	mMainFrameHorizontalSizer->Add(mTabbedNotebook, 2, wxEXPAND | wxLEFT | wxRIGHT, 10);
	mMainFrameHorizontalSizer->Add(mLauncherPanel, 1, wxEXPAND | wxRIGHT, 10);

	// Menubar - File, Help, etc
	mMenubar = new MenuBar(this);
	SetMenuBar(mMenubar);

	// Title banner
	wxImage::AddHandler(new wxPNGHandler);
	mBitmapBanner = new wxStaticBitmap(this, wxID_ANY, wxBitmap("SDVMM2.png", wxBITMAP_TYPE_PNG)); // TODO save in code?
	wxImage::CleanUpHandlers();
	mHorizontalBannerSizer = new wxBoxSizer(wxHORIZONTAL);
	mHorizontalBannerSizer->Add(mBitmapBanner, 0, wxEXPAND, 0);
	mHorizontalBannerSizer->AddStretchSpacer(1);

	//// Status Bar - Version Info & Mod Count
	//mVersionSmapiStext = new wxStaticText(this, wxID_ANY, "SMAPI Version: " + mSettingsPanel->versionSmapi()); // TODO getters/setters
	//mModManagerStext = new wxStaticText(this, wxID_ANY, "SDVMM2 Version: " + mSettingsPanel->versionModManager());
	//mModCountStext = new wxStaticText(this, wxID_ANY,
	//	std::to_string(mModCount[ModStatus::loaded]) + "/" + std::to_string(mModCount[ModStatus::total]) + " Mods Loaded");
	//mModCountSizer = new wxBoxSizer(wxVERTICAL);
	//mModCountSizer->Add(mModCountStext, 0, wxALIGN_RIGHT, 0);
	//mVersionSizer = new wxBoxSizer(wxHORIZONTAL);
	//mVersionSizer->Add(mModManagerStext, 10, wxEXPAND | wxLEFT, 15);
	//mVersionSizer->Add(mVersionSmapiStext, 10, wxEXPAND | wxLEFT, 5);
	//mVersionSizer->AddStretchSpacer(10);
	//mVersionSizer->Add(mModCountSizer, 5, wxEXPAND | wxRIGHT, 10);

	constexpr semver::version v_default;
	_mStatusBar = new StatusBar(this, wxID_ANY, v_default, v_default, wxSB_SUNKEN);
	SetStatusBar(_mStatusBar);

	// Vertical layout
	mMainFrameVerticalSizer = new wxBoxSizer(wxVERTICAL);
	mMainFrameVerticalSizer->Add(mHorizontalBannerSizer, 0, wxEXPAND | wxALL , 10);
	mMainFrameVerticalSizer->Add(mMainFrameHorizontalSizer, 40, wxEXPAND, 0);
	SetSizer(mMainFrameVerticalSizer);

	// Setting background colour as needed
	SetBackgroundColour(wxColour(240, 240, 240, wxALPHA_OPAQUE));

	tryLoadSettings();
}

//-------------------
// MEMBER FUNCTIONS
//-------------------
MainFrame::~MainFrame() {
}

void MainFrame::tryLoadSettings() {
	DPRINT("SelfInit - Begin\n");
	wxFileName f(wxStandardPaths::Get().GetExecutablePath());
	fs::path appPath = std::string(wxString(f.GetPath() + wxT("\\SDVMM2.ini")));

	DPRINT("SelfInit - Checking for .ini at:\n" + appPath.string() + "\n");
	mSettingsPanel->mConfigIni = new wxFileConfig(wxEmptyString, wxEmptyString, appPath.string());
	mSettingsPanel->mConfigIni->SetPath("/General");

	if (fs::exists(appPath)) {
		mSettingsPanel->tryLoadSettings();
	}
	else
	{
		D("SelfInit - No .ini Found\n");
	}
}

//--------------------
// Backend Functions
//--------------------
void MainFrame::mCleanManifest(nlohmann::json& manifest, fs::path errorPath) { // TODO move check to refresh and make flag

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

void MainFrame::mRefreshModLists() {
	mResetRefreshErrors();
	wxWindowUpdateLocker noUpdates(mModBrowserPanel->mModBrowserDataviewlistctrl);
	mModBrowserPanel->mModBrowserDataviewlistctrl->DeleteAllItems();
	try { mLoadModsFromDir("\\Mods\\"); }
	catch (...) {
		wxMessageDialog* errorLoadMods = new wxMessageDialog(NULL,
			wxT("Fatal error attempting to refresh active mods."),
			wxT("Refresh Error"), wxOK, wxDefaultPosition);
		errorLoadMods->ShowModal();
		delete errorLoadMods;
	}
	try { mLoadModsFromDir("\\Mods_disabled\\"); }
	catch (...) {
		wxMessageDialog* errorLoadModsD = new wxMessageDialog(NULL,
			wxT("Fatal error attempting to refresh inactive mods."),
			wxT("Refresh Error"), wxOK, wxDefaultPosition);
		errorLoadModsD->ShowModal();
		delete errorLoadModsD;
	}
	mModBrowserPanel->mModBrowserDataviewlistctrl->GetModel()->Resort();
	// Pull out this from the main contructor
	std::string tempMod = std::to_string(mModCount[ModStatus::loaded]) + "/" +
		std::to_string(mModCount[ModStatus::total]) + " Mods Successfully Loaded";
	//mModCountStext->SetLabel(tempMod);
	_mStatusBar->SetStatusText(tempMod, 2);
	mShowRefreshErrors();
}

void MainFrame::mLoadModsFromDir(std::string folderName) {
	// TODO group and report errors in scrollable dialogue (bad jsons, incompatible mods, etc.)
	// TODO replace custom ioFunctions with filesystem?
	fs::path targetDirectory = (mSettingsPanel->gameDirectory());
	targetDirectory += folderName;
	fs::path tempPath;
	fs::path errorPath;
	bool isActive = (folderName == "\\Mods\\");
	//int errorJson = 0; // 0 = no error, 1 = bad comma, 2 = other

	DPRINT("mLoadModsFromDir - Begin Iterator at:\n" + mSettingsPanel->gameDirectory().string() + "\n");
	for (auto& directoryIterator : fs::recursive_directory_iterator(targetDirectory)) {
		mErrorChecks[ModErrors::json] = false;
		mErrorChecks[ModErrors::formatLocal] = false;
		errorPath = directoryIterator.path().filename();
		tempPath = directoryIterator.path();
		DPRINTIF(REPORT_MOD_DIRECTORY, tempPath.string() + "\n");

		if (!fs::is_directory(tempPath)) {
			DPRINTIF(REPORT_MOD_DIRECTORY & REPORT_IDENTIFY_DIRECTORIES, " - Is NOT Directory\n");
			continue;
		}
		DPRINTIF(REPORT_MOD_DIRECTORY & REPORT_IDENTIFY_DIRECTORIES, " - Is Directory\n");

		tempPath += "\\manifest.json";
		if (!fs::exists(tempPath)) {
			continue;
		}
		//DPRINTIF(???, " - Manifest found.\n");

		mModCount[ModStatus::total]++;
		ifstream jsonStream(tempPath.c_str());
		nlohmann::json jsonManifest;
		try
		{
			try
			{ // Parse json
				jsonManifest = nlohmann::json::parse(jsonStream); // TODO handle trailing commas
				// Handle some minor typos and missing fields in manifest
				mCleanManifest(jsonManifest, errorPath);
			}
			catch (nlohmann::json::parse_error & e) { // On fail, output error and skip to next mod
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
				std::string jsonString = "New\n";
				ifstream jsonStream2(tempPath.c_str(), std::ios::in | std::ios::binary);
				jsonStream2.seekg(0, std::ios::end);
				jsonString.resize(jsonStream2.tellg());
				jsonStream2.seekg(0, std::ios::beg);
				jsonStream2.read(&jsonString[0], jsonString.size());
				jsonStream2.close();

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
				catch (const std::regex_error & e) {
					std::string temp = e.what();
					DPRINTIF(REPORT_JSON_FIX, "Json Fix Comma Clean Failure: " + temp + "\n");
				}

				DPRINTIF(REPORT_JSON_FIX, "Json Fix Comma Cleaned\n" + jsonString + "\n");

				try	{
					jsonManifest = nlohmann::json::parse(jsonString); // TODO handle trailing commas
					// Handle some minor typos and missing fields in manifest
					mCleanManifest(jsonManifest, errorPath);
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
			mModBrowserPanel->mModBrowserDataviewlistctrl->AppendItem(thisMod);
			++mModCount[ModStatus::loaded];
			thisMod.clear();
			DPRINTIF(REPORT_VERBOSE_MOD_OBJECTS, aMod.infoString());
		}
		catch (...) {
			mErrorLocations += "\n" + errorPath.string() + " - Fatal";
		}
	}
}

bool MainFrame::mExistsModFolders() {
	fs::path modPath = mSettingsPanel->gameDirectory();
	fs::path modPathDisabled = mSettingsPanel->gameDirectory();
	fs::path gamePath = mSettingsPanel->gameDirectory();
	modPath += "\\Mods";
	modPathDisabled += "\\Mods_disabled";
	gamePath += "\\Stardew Valley.exe"; // TODO Make crossplatform?

	DPRINT("mExistsModFolders - Begin Checking Mod Folders\n");

	if (!(fs::exists(gamePath) and fs::is_regular_file(gamePath))) {
		DPRINT("mExistsModFolders - Game Executable not Found on Path:\n"
			+ gamePath.string() + "\n" + "mExistsModFolders - Bad Game Directory\n");
		return false;
	}
	else
	{
		if (!(fs::exists(modPath) and fs::is_directory(modPath))) {
			DPRINT("mExistsModFolders - Mods Folder not Found\n");
			fs::create_directory(modPath);
			DPRINT("mExistsModFolders - Mods Folder Created at:\n" + modPath.string() + "\n");
		}
		else
		{
			DPRINT("mExistsModFolders - Mods Directory Found on Path:\n" + modPath.string() + "\n");
		}
		if (!(fs::exists(modPathDisabled) and fs::is_directory(modPathDisabled))) {
			DPRINT("mExistsModFolders - Mods_disabled Folder not Found\n");
			fs::create_directory(modPathDisabled);
			DPRINT("mExistsModFolders - Mods_disabled Folder Created at:\n" + modPathDisabled.string() + "\n");
		}
		else
		{
			DPRINT("mExistsModFolders - Mods Directory Found on Path:\n" + modPathDisabled.string() + "\n");
		}
	}
	return true;
}

void MainFrame::mCheckSmapiVersion() {
	std::string version = "not found";
	fs::path pathSmapiLogs = std::string(wxStandardPaths::Get().GetUserConfigDir());
	pathSmapiLogs += "\\StardewValley\\ErrorLogs\\SMAPI-latest.txt";
	if (fs::exists(pathSmapiLogs) and fs::is_regular_file(pathSmapiLogs)) {
		DPRINT("mCheckSmapiVersion - Logs Found\n");
		wxTextFile smapiLogs;
		smapiLogs.Open(wxString(pathSmapiLogs));
		wxString tempString = smapiLogs.GetFirstLine();
		size_t tempVersionStart = tempString.Find("] ") + 8;
		size_t tempVersionEnd = tempString.Find(" with Stardew") - 1;
		version = tempString.SubString(tempVersionStart, tempVersionEnd);
		DPRINT("mCheckSmapiVersion - Version: " + version + "\n");
	}
	else
	{
		DPRINT("mCheckSmapiVersion - No Logs Found\n");
	}
	//mVersionSmapiStext->SetLabel("SMAPI Version: " + version);
	_mStatusBar->SetStatusText("SMAPI Version: " + version, 0);
}

void MainFrame::mResetRefreshErrors() {
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

void MainFrame::mShowRefreshErrors() {
	bool errorsExist = ((mErrorCount[ModErrors::json] != 0) 
			or (mErrorCount[ModErrors::semver] != 0) 
			or (mErrorCount[ModErrors::format] != 0));
	if (!errorsExist or (mSettingsPanel->mMuteErrors["on_refresh"] == true) ) {
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
