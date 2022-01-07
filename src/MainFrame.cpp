#include "MainFrame.h"

//#include "JsonCleaner.h"
#include "LauncherButtonPanel.h"
#include "ManifestParser.h"
#include "MenuBar.h"
#include "ModBrowserPanel.h"
#include "SettingsPanel.h"
#include "SmapiMod.h"
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
	mStatusBar = new StatusBar(this, wxID_ANY, v_default, v_default, wxSB_SUNKEN);
	SetStatusBar(mStatusBar);

	// Vertical layout
	mMainFrameVerticalSizer = new wxBoxSizer(wxVERTICAL);
	mMainFrameVerticalSizer->Add(mHorizontalBannerSizer, 0, wxEXPAND | wxALL , 10);
	mMainFrameVerticalSizer->Add(mMainFrameHorizontalSizer, 40, wxEXPAND, 0);
	SetSizer(mMainFrameVerticalSizer);

	// Setting background colour as needed
	SetBackgroundColour(wxColour(240, 240, 240, wxALPHA_OPAQUE));

	mManifestParser = new ManifestParser(this);
	tryLoadSettings();
	//mManifestParser->refreshModLists();
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
void MainFrame::checkSmapiVersion() {
	std::string version = "not found";
	fs::path pathSmapiLogs = std::string(wxStandardPaths::Get().GetUserConfigDir());
	pathSmapiLogs += "\\StardewValley\\ErrorLogs\\SMAPI-latest.txt";
	if (fs::exists(pathSmapiLogs) and fs::is_regular_file(pathSmapiLogs)) {
		DPRINT("checkSmapiVersion - Logs Found\n");
		wxTextFile smapiLogs;
		smapiLogs.Open(wxString(pathSmapiLogs));
		wxString tempString = smapiLogs.GetFirstLine();
		size_t tempVersionStart = tempString.Find("] ") + 8;
		size_t tempVersionEnd = tempString.Find(" with Stardew") - 1;
		version = tempString.SubString(tempVersionStart, tempVersionEnd);
		DPRINT("checkSmapiVersion - Version: " + version + "\n");
	}
	else
	{
		DPRINT("checkSmapiVersion - No Logs Found\n");
	}
	//mVersionSmapiStext->SetLabel("SMAPI Version: " + version);
	mStatusBar->SetStatusText("SMAPI Version: " + version, 0);
}
