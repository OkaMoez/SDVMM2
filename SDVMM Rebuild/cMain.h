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
#include "cMod.h"

#include <filesystem>
namespace fs = std::filesystem;
using std::istream;
using std::ifstream;

class MenuBar;
class ModBrowserPanel;
class SettingsPanel;

enum class mod_errors {
	json,
	semvar,
	format,
	format_local,
	smapi
};

enum class mod_status {
	total,
	errored,
	loaded
};

class cMain : public wxFrame // TODO Organize privacy
{
private:
	std::string error_locations_ = "Errors at: ";

	std::unordered_map<mod_errors, bool> error_check_
	{
		{mod_errors::json, false},
		{mod_errors::semvar, false},
		{mod_errors::format, false},
		{mod_errors::format_local, false},
		{mod_errors::smapi, false}
	};

	std::unordered_map<mod_errors, int> error_count_
	{
		{mod_errors::json, 0},
		{mod_errors::semvar, 0},
		{mod_errors::format, 0}
	};

	std::unordered_map<mod_status, int> mod_count_
	{
		{mod_status::total, 0},
		{mod_status::errored, 0},
		{mod_status::loaded, 0}
	};

	// TODO Rename?
	int ID_BUTTON_NEXUS = wxNewId();
	int ID_BUTTON_FORUMS = wxNewId();

public:
	cMain();
	~cMain();
	void SelfInitialize();

public:
	// Notebook
	wxNotebook* m_notebook = nullptr;
	// Tab 1
	ModBrowserPanel* m_mod_browser_panel = nullptr;
	// Tab 2
	wxPanel* m_panel_notebook_tab2 = nullptr;
	wxListBox* m_list_xnb_mods = nullptr;
	wxBoxSizer* m_sizer_notebook_tab2a = nullptr;
	wxBoxSizer* m_sizer_notebook_tab2 = nullptr;
	// Tab 3
	SettingsPanel* m_settings_panel = nullptr;

	// m_menubar
	MenuBar* m_menubar = nullptr;

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

