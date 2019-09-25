#pragma once

#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include "cMod.h"


class cMain : public wxFrame
{
private:
	string gamepath_ = "";
	void popModLists();

public:
	cMain();
	~cMain();
	string gamepath() { return gamepath_; }
	void set_gamepath(string);

public:
	// Notebook
	wxNotebook* m_notebook = nullptr;
	// Tab 1
	wxPanel* m_panel_nTab1 = nullptr;
	wxListView* m_listv_Mods = nullptr;
	wxBoxSizer* m_sizer_nTab1a_Mods = nullptr;
	wxStaticText* m_sText_aMod = nullptr;
	wxStaticText* m_sText_iMod = nullptr;
	wxButton* m_btn_openAMods = nullptr;
	wxButton* m_btn_openIMods = nullptr;
	wxButton* m_btn_refreshMods = nullptr;
	wxFont m_font;
	wxBoxSizer* m_sizer_nTab1 = nullptr;
	wxBoxSizer* m_sizer_nTab1a = nullptr;
	wxBoxSizer* m_sizer_nTab1b = nullptr;
	// Tab 2
	wxPanel* m_panel_nTab2 = nullptr;
	wxListBox* m_list_xMods = nullptr;
	wxBoxSizer* m_sizer_nTab2a = nullptr;
	wxBoxSizer* m_sizer_nTab2 = nullptr;
	// Tab 3
	wxPanel* m_panel_nTab3 = nullptr;
	wxListBox* m_list_loadOrder = nullptr;
	wxBoxSizer* m_sizer_nTab3a = nullptr;
	wxBoxSizer* m_sizer_nTab3 = nullptr;

	// Menubar
	wxMenuBar* menubar = nullptr;
	wxMenu* file = nullptr;
	wxMenu* help = nullptr;

	// Right side buttons
	wxButton* m_btn_launchSMAPI = nullptr;
	wxButton* m_btn_launchSDV = nullptr;
	wxButton* m_btn_addMod = nullptr;
	wxButton* m_btn_dlMod = nullptr;
	wxButton* m_btn_delMod = nullptr;
	wxBoxSizer* m_sizer_rBtns = nullptr;

	// Other Layout
	wxStaticBitmap* m_sbmp_banner = nullptr;
	wxStaticText* m_sText_APIversion = nullptr;
	wxStaticText* m_sText_MMversion = nullptr;
	wxBoxSizer* m_sizer_vInfo = nullptr;
	wxPanel* m_bg_panel = nullptr;

	// Main Layout Sizers
	wxBoxSizer* m_sizer_Hmain = nullptr;
	wxBoxSizer* m_sizer_Vmain = nullptr;


	void OnButtonClicked(wxCommandEvent& evt);
	void RefreshModList();

	wxDECLARE_EVENT_TABLE();
};

