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
#include "SettingsPanel.h"

#include <filesystem>
namespace fs = std::filesystem;
using std::istream;
using std::ifstream;


class cMain : public wxFrame // TODO Organize privacy
{
private:

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

public:
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
	SettingsPanel* m_panel_notebook_tab3 = nullptr;

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

