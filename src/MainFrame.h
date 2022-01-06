#pragma once
#include <wx/wx.h>

#include <fstream>
#include <iomanip>
#include "nlohmann/json.hpp" // There is a way to forward declare this, but I couldn't get it working
#include <sstream> 
#include "SmapiMod.h"
#include <windows.h>
#include <wx/menu.h>
#include <wx/event.h>
#include <wx/notebook.h>
#include <wx/dataview.h>
#include <wx/checkbox.h>
#include <wx/fileconf.h>
#include <wx/wupdlock.h>
#include <wx/textfile.h>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#include <wx/stdpaths.h>
#include <wx/filefn.h>

// TODO? migrate this to wxFileSystem
#include <filesystem>
namespace fs = std::filesystem;
using std::istream;
using std::ifstream;

class LauncherButtonPanel;
class MenuBar;
class ModBrowserPanel;
class SettingsPanel;
class StatusBar;

enum class ModErrors {
	json,
	semvar,
	format,
	formatLocal,
	smapi
};

enum class ModStatus {
	total,
	errored,
	loaded
};

class MainFrame : public wxFrame // TODO Organize privacy
{
public:
	std::string mErrorLocations = "Errors at: ";

	std::unordered_map<ModErrors, bool> mErrorChecks
	{
		{ModErrors::json, false},
		{ModErrors::semvar, false},
		{ModErrors::format, false},
		{ModErrors::formatLocal, false},
		{ModErrors::smapi, false}
	};

	std::unordered_map<ModErrors, int> mErrorCount
	{
		{ModErrors::json, 0},
		{ModErrors::semvar, 0},
		{ModErrors::format, 0}
	};

	std::unordered_map<ModStatus, int> mModCount
	{
		{ModStatus::total, 0},
		{ModStatus::errored, 0},
		{ModStatus::loaded, 0}
	};

public:
	MainFrame();
	~MainFrame();
	void tryLoadSettings();

public:
	// Notebook
	wxNotebook* mTabbedNotebook = nullptr;
	// Tab 1
	ModBrowserPanel* mModBrowserPanel = nullptr;
	// Tab 3
	SettingsPanel* mSettingsPanel = nullptr;

	// mMenubar
	MenuBar* mMenubar = nullptr;
	StatusBar* _mStatusBar = nullptr;

	// Right side buttons
	LauncherButtonPanel* mLauncherPanel = nullptr;

	// Other Layout
	wxStaticBitmap* mBitmapBanner = nullptr;
	wxBoxSizer* mHorizontalBannerSizer = nullptr;
	//wxStaticText* mVersionSmapiStext = nullptr;
	//wxStaticText* mModManagerStext = nullptr;
	//wxStaticText* mModCountStext = nullptr;
	//wxBoxSizer* mModCountSizer = nullptr;
	//wxBoxSizer* mVersionSizer = nullptr;

	// Main Layout Sizers
	wxBoxSizer* mMainFrameHorizontalSizer = nullptr;
	wxBoxSizer* mMainFrameVerticalSizer = nullptr;
	
public:
	void mCleanManifest(nlohmann::json& manifest, fs::path error_path);
	void mCleanJson(); // TODO tranfer code to function
	void mRefreshModLists(); // TODO give some indication of the refresh
	void mLoadModsFromDir(std::string folderName);
	bool mExistsModFolders();
	void mCheckSmapiVersion();
	void mResetRefreshErrors(); // TODO format and move to getters/setters?
	void mShowRefreshErrors();
};

