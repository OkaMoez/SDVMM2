#pragma once

#include <wx/wx.h>
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
#include <fileapi.h>
#include <fstream>
#include <iomanip>
#include <sstream> 
#include <filesystem>
#include "cMod.h"
namespace fs = std::filesystem;
using std::istream;
using std::ifstream;


class cMain : public wxFrame // TODO Organize privacy
{
private:
	bool ini_exists_ = false;
	bool launch_with_steam_ = false;
	fs::path game_directory_ = "";
	fs::path steam_directory_ = "";
	string version_smapi_ = "not found";
	string version_this_mm_ = "0.6";
	string error_locations_ = "Errors at: ";
	std::map<string, bool> error_mute_{
		{"on_refresh", true}
	};
	std::map<string, bool> error_check_{
		{"json", false},
		{"semvar", false},
		{"format", false},
		{"format_local", false},
		{"smapi", false}
	};
	std::map<string, int> error_count_{
		{"json", 0},
		{"semvar", 0},
		{"format", 0}
	};
	std::map<string, int> mod_count_{
		{"total", 0},
		{"errored", 0},
		{"loaded", 0}
	};

	// TODO Rename?
	int ID_MENU_MODS = wxNewId();
	int ID_MENU_DMODS = wxNewId();
	int ID_MENU_QUIT = wxNewId();
	int ID_BUTTON_NEXUS = wxNewId();
	int ID_BUTTON_FORUMS = wxNewId();

public:
	cMain();
	~cMain();
	void SelfInitialize();
	bool ini_exists() { return ini_exists_; }
	bool launch_with_steam() { return launch_with_steam_; }
	fs::path game_directory() { return game_directory_; }
	fs::path steam_directory() { return steam_directory_; }
	string version_smapi() { return version_smapi_; }
	string version_this_mm() { return version_this_mm_; }
	void set_launch_with_steam(bool state);
	void set_game_directory(fs::path filepath);
	void set_steam_directory(fs::path filepath);
	void set_version_this_mm(string version);
	void set_error_mute(bool state);

public:
	wxFileConfig* config_ini = nullptr;
	// Notebook
	wxNotebook* m_notebook = nullptr;
	// Tab 1
	wxPanel* m_panel_notebook_tab1 = nullptr;
	wxDataViewListCtrl* m_dataviewlistctrl_mods = nullptr;
	wxBoxSizer* m_sizer_notebook_tab1a_mods = nullptr;
	wxBoxSizer* m_sizer_notebook_tab1 = nullptr;
	wxBoxSizer* m_sizer_notebook_tab1a = nullptr;
	wxBoxSizer* m_sizer_notebook_tab1b = nullptr;
	// Tab 2
	wxPanel* m_panel_notebook_tab2 = nullptr;
	wxListBox* m_list_xnb_mods = nullptr;
	wxBoxSizer* m_sizer_notebook_tab2a = nullptr;
	wxBoxSizer* m_sizer_notebook_tab2 = nullptr;
	// Tab 3
	wxPanel* m_panel_notebook_tab3 = nullptr;
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

	// m_menubar
	wxMenuBar* m_menubar = nullptr;
	wxMenu* m_menubar_file = nullptr;
	wxMenu* m_menubar_help = nullptr;

	// Right side buttons
	wxButton* m_button_launch_smapi = nullptr;
	wxButton* m_button_launch_vanilla = nullptr;
	wxButton* m_button_add_mod = nullptr;
	wxButton* m_button_nexus_download = nullptr;
	wxButton* m_button_forums_download = nullptr;
	wxButton* m_button_refresh_mods = nullptr;
	wxBoxSizer* m_sizer_buttons_right = nullptr;
	wxPanel* m_panel_buttons_right = nullptr;

	// Other Layout
	wxStaticBitmap* m_bitmap_banner = nullptr;
	wxBoxSizer* m_sizer_banner_horizontal = nullptr;
	wxStaticText* m_stext_smapi_version = nullptr;
	wxStaticText* m_stext_this_version = nullptr;
	wxStaticText* m_stext_mod_count = nullptr;
	wxBoxSizer* m_sizer_mod_count = nullptr;
	wxBoxSizer* m_sizer_version_info = nullptr;

	// Main Layout Sizers
	wxBoxSizer* m_sizer_main_horizontal = nullptr;
	wxBoxSizer* m_sizer_main_vertical = nullptr;

private:
	// Top Level Buttons
	void OnLaunchSMAPIClick(wxCommandEvent& event);
	void OnLaunchVanillaClick(wxCommandEvent& event);
	void OnLaunchModSiteClick(wxCommandEvent& event);
	void OnRefreshClick(wxCommandEvent& event);
	// Mod List Buttons
	void OnToggleClick(wxDataViewEvent& event);
	void OnSortClick(wxDataViewEvent& event);
	// Menu Bar Buttons
	void OnMenuClick(wxCommandEvent& event); // TODO complete
	void OnMenuModsClick(wxCommandEvent& event); // TODO Make cross platform
	void OnMenuModsDisabledClick(wxCommandEvent& event);  // TODO Make cross platform
	void OnMenuQuitClick(wxCommandEvent& event);
	// Settings Buttons
	void OnLauncherToggleClick(wxCommandEvent& event);
	void OnGameDirectorySaveClick(wxCommandEvent& event);
	void OnGameDirectoryBrowseClick(wxCommandEvent& event);
	void OnSteamDirectorySaveClick(wxCommandEvent& event);
	void OnSteamDirectoryBrowseClick(wxCommandEvent& event);
	void OnMuteModToggleClick(wxCommandEvent& event);
	
public:
	void CleanManifest(json& manifest, fs::path error_path);
	void CleanJson(); // TODO tranfer code to function
	void RefreshModLists(); // TODO give some indication of the refresh
	void LoadModsFromDir(string folder_name);
	bool ExistsModFolders();
	void CheckSmapiVersion();
	void ResetRefreshErrors(); // TODO format and move to getters/setters?
	void ShowRefreshErrors();
};

