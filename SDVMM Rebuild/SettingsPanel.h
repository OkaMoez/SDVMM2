#pragma once
#include "debugConstants.h"

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

	void SelfInitialize();
	bool ini_exists() { return ini_exists_; }
	bool launch_with_steam() { return launch_with_steam_; }
	fs::path game_directory() { return game_directory_; }
	fs::path steam_directory() { return steam_directory_; }
	std::string version_smapi() { return version_smapi_; }
	std::string version_this_mm() { return version_this_mm_; }

	// Settings Buttons
	void OnLauncherToggleClick(wxCommandEvent& event);
	void OnGameDirectorySaveClick(wxCommandEvent& event);
	void OnGameDirectoryBrowseClick(wxCommandEvent& event);
	void OnSteamDirectorySaveClick(wxCommandEvent& event);
	void OnSteamDirectoryBrowseClick(wxCommandEvent& event);
	void OnMuteModToggleClick(wxCommandEvent& event);

	wxFileConfig* config_ini = nullptr;

	std::unordered_map<std::string, bool> error_mute_
	{
		{"on_refresh", true}
	};

private:
	bool ini_exists_ = false;
	bool launch_with_steam_ = false;
	fs::path game_directory_ = "";
	fs::path steam_directory_ = "";
	std::string version_smapi_ = "not found";
	std::string version_this_mm_ = "0.6";

	MainFrame* mainWindow = nullptr;

	// Tab 3 - Launcher Option
	wxStaticText* m_stext_launcher = nullptr;
	wxCheckBox* m_checkbox_launcher = nullptr;
	wxBoxSizer* m_sizer_notebook_tab3_launcher = nullptr;
	// Tab 3 - Game Directory
	wxStaticText* m_stext_game_directory = nullptr;
	wxTextCtrl* m_textctrl_game_directory = nullptr;
	wxDirDialog* m_dirdialog_game_browse = nullptr;
	wxButton* m_button_game_directory_save = nullptr;
	wxButton* m_button_game_directory_browse = nullptr;
	wxBoxSizer* m_sizer_notebook_tab3_game_directory = nullptr;
	// Tab 3 - Steam Directory
	wxStaticText* m_stext_steam_directory = nullptr;
	wxTextCtrl* m_textctrl_steam_directory = nullptr;
	wxFileDialog* m_filedialog_steam_browse = nullptr;
	wxButton* m_button_steam_directory_save = nullptr;
	wxButton* m_button_steam_directory_browse = nullptr;
	wxBoxSizer* m_sizer_notebook_tab3_steam_directory = nullptr;
	// Tab 3 - Error Mute Option
	wxStaticText* m_stext_mute = nullptr;
	wxCheckBox* m_checkbox_mute = nullptr;
	wxBoxSizer* m_sizer_notebook_tab3_mute = nullptr;
	// Tab 3 - Layout
	wxBoxSizer* m_sizer_notebook_tab3_items = nullptr;
	wxBoxSizer* m_sizer_notebook_tab3_left = nullptr;
	wxBoxSizer* m_sizer_notebook_tab3_right = nullptr;
	wxBoxSizer* m_sizer_notebook_tab3 = nullptr;
};
