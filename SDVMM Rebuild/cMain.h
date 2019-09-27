#pragma once

#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include <wx/dataview.h>
#include <wx/event.h>
#include "cMod.h"


class cMain : public wxFrame // TODO Organize privacy
{
private:
	string gamepath_ = "";

	// IDs currently don't follow google style guide afaik
	int ID_BUTTON_NEXUS = NULL;
	int ID_BUTTON_FORUMS = NULL;
	int ID_MENU_MODS = NULL;
	int ID_MENU_DMODS = NULL;
	int ID_MENU_QUIT = NULL;

public:
	cMain();
	~cMain();
	string gamepath() { return gamepath_; }
	void set_gamepath(string);

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
	wxPanel* m_panel_notebook_tab3 = nullptr;
	wxListBox* m_list_loadorder = nullptr;
	wxBoxSizer* m_sizer_notebook_tab3a = nullptr;
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

	// Other Layout
	wxStaticBitmap* m_bitmap_banner = nullptr;
	wxStaticText* m_stext_smapi_version = nullptr;
	wxStaticText* m_stext_this_version = nullptr;
	wxBoxSizer* m_sizer_version_info = nullptr;
	wxPanel* m_bg_panel = nullptr;

	// Main Layout Sizers
	wxBoxSizer* m_sizer_main_horizontal = nullptr;
	wxBoxSizer* m_sizer_main_vertical = nullptr;

private:
	void OnLaunchSMAPIClick(wxCommandEvent& event);
	void OnLaunchVanillaClick(wxCommandEvent& event);
	void OnLaunchModSiteClick(wxCommandEvent& event);
	void OnRefreshClick(wxCommandEvent& event);
	void OnMenuClick(wxCommandEvent& event); // TODO complete
	void OnMenuModsClick(wxCommandEvent& event); // TODO Make cross platform
	void OnMenuModsDisabledClick(wxCommandEvent& event);  // TODO Make cross platform
	void OnMenuSettingsClick(wxCommandEvent& event);
	void OnMenuQuitClick(wxCommandEvent& event);
	
public:
	void ToggleMod(wxDataViewEvent& event);
	void FormatOldVersion(json& manifest);
	void RefreshModLists(); // TODO give some indication of the refresh
	void LoadModsFromDir(string folder_name);
	bool ExistsModFolders();
};

