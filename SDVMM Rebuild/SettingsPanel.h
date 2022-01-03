#pragma once
#include "DebugTools.h"

#include <wx/wx.h>
#include <wx/dataview.h>
#include <wx/fileconf.h>

// TODO? migrate this to wxFileSystem
#include <filesystem>
namespace fs = std::filesystem;

class MainFrame;

class SettingsPanel : public wxPanel {

public:
	SettingsPanel(wxWindow* parent, wxWindowID windowID, MainFrame* parentWindow);
	~SettingsPanel();

	void tryLoadSettings();
	bool iniExists() { return _mIniExists; }
	bool shouldLaunchWithSteam() { return _mLaunchWithSteam; }
	fs::path gameDirectory() { return _mGameDirectory; }
	fs::path steamDirectory() { return _mSteamDirectory; }
	std::string versionSmapi() { return _mVersionSmapi; }
	std::string versionModManager() { return _mVersionModManager; }

	// Settings Buttons
	void onLauncherToggleClick(wxCommandEvent& event);
	void onGameDirectorySaveClick(wxCommandEvent& event);
	void onGameDirectoryBrowseClick(wxCommandEvent& event);
	void onSteamDirectorySaveClick(wxCommandEvent& event);
	void onSteamDirectoryBrowseClick(wxCommandEvent& event);
	void onMuteModToggleClick(wxCommandEvent& event);

	wxFileConfig* configIni = nullptr;

	std::unordered_map<std::string, bool> muteErrors {
		{"on_refresh", true}
	};

private:
	bool _mIniExists = false;
	bool _mLaunchWithSteam = false;
	fs::path _mGameDirectory = "";
	fs::path _mSteamDirectory = "";
	std::string _mVersionSmapi = "not found";
	std::string _mVersionModManager = "0.6";

	MainFrame* _mMainWindow = nullptr;

	// Tab 3 - Launcher Option
	wxStaticText* _mLauncherChoiceStext = nullptr;
	wxCheckBox* _mLauncherChoiceCheckbox = nullptr;
	wxBoxSizer* _mLauncherChoiceSizer = nullptr;
	// Tab 3 - Game Directory
	wxStaticText* _mGameDirectoryStext = nullptr;
	wxTextCtrl* _mGameDirectoryTextctrl = nullptr;
	wxDirDialog* _mGameDirectoryDirdialog = nullptr;
	wxButton* _mGameDirectorySaveButton = nullptr;
	wxButton* _mGameDirectoryBrowseButton = nullptr;
	wxBoxSizer* _mGameDirectorySizer = nullptr;
	// Tab 3 - Steam Directory
	wxStaticText* _mSteamDirectoryStext = nullptr;
	wxTextCtrl* _mSteamDirectoryTextctrl = nullptr;
	wxFileDialog* _mSteamDirectoryFiledialog = nullptr;
	wxButton* _mSteamDirectorySaveButton = nullptr;
	wxButton* _mSteamDirectoryBrowseButton = nullptr;
	wxBoxSizer* _mSteamDirectorySizer = nullptr;
	// Tab 3 - Error Mute Option
	wxStaticText* _mMuteErrorsStext = nullptr;
	wxCheckBox* _mMuteErrorsCheckbox = nullptr;
	wxBoxSizer* _mMuteErrorsSizer = nullptr;
	// Tab 3 - Layout
	wxBoxSizer* _mSettingsFieldsSizer = nullptr;
	wxBoxSizer* _mLeftSpacerSizer = nullptr;
	wxBoxSizer* _mRightSpacerSizer = nullptr;
	wxBoxSizer* _mSettingsPanelSizer = nullptr;
};
