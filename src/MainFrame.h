#pragma once
#include "DebugTools.h"

#include <fstream>
#include <iomanip>
#include "nlohmann/json.hpp" // There is a way to forward declare this, but I couldn't get it working
#include <sstream> 
#include <windows.h>
#include <wx/checkbox.h>
#include <wx/dataview.h>
#include <wx/dirdlg.h>
#include <wx/event.h>
#include <wx/fileconf.h>
#include <wx/filedlg.h>
#include <wx/filefn.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include <wx/stdpaths.h>
#include <wx/textfile.h>
#include <wx/wupdlock.h>
#include <wx/wx.h>

// TODO? migrate this to wxFileSystem
#include <filesystem>
namespace fs = std::filesystem;
using std::istream;
using std::ifstream;

class LauncherButtonPanel;
class ManifestParser;
class MenuBar;
class ModBrowserPanel;
class SettingsPanel;
class StatusBar;

class MainFrame : public wxFrame { // TODO Organize privacy
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
	StatusBar* mStatusBar = nullptr;

	// Right side buttons
	LauncherButtonPanel* mLauncherPanel = nullptr;

	// Other Layout
	wxStaticBitmap* mBitmapBanner = nullptr;
	wxBoxSizer* mHorizontalBannerSizer = nullptr;

	// Main Layout Sizers
	wxBoxSizer* mMainFrameHorizontalSizer = nullptr;
	wxBoxSizer* mMainFrameVerticalSizer = nullptr;
	
	ManifestParser* mManifestParser = nullptr;

public:
	void checkSmapiVersion();
};

