#include "cApp.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	//EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, 1, "SDVMM 2",
	wxDefaultPosition, wxSize(750,500),
	wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	//---------------------------
	//  Notebook Implementation
	//---------------------------
	// Tab 1, 2, 3 = Active/Inactive Mods, XNB Mods, Drag/Drop Load Order
	//
	m_notebook = new wxNotebook(this, -1);

	// Tab 1
	m_panel_nTab1 = new wxPanel(m_notebook, wxID_ANY);

	// Tab 1 - List Control - Creation
	m_listc_Mods = new wxListCtrl(m_panel_nTab1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_LIST);
	m_listc_Mods->

	// Tab 1 - List - Vertical Sizers + Title Text
	m_sizer_nTab1a_Mods = new wxBoxSizer(wxVERTICAL);
	m_sizer_nTab1a_Mods->AddSpacer(5);
	m_sizer_nTab1a_Mods->Add(m_listc_Mods, 1, wxEXPAND, 0);
	m_sizer_nTab1a_Mods->AddSpacer(2);

	// Tab 1 - List - Horizontal Sizer
	m_sizer_nTab1a = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_nTab1a->AddSpacer(8);
	m_sizer_nTab1a->Add(m_sizer_nTab1a_Mods, 1, wxEXPAND, 0);
	m_sizer_nTab1a->AddSpacer(10);

	// tab 1 - Bottom Buttons 
	m_sizer_nTab1b = new wxBoxSizer(wxHORIZONTAL);
	m_btn_openAMods = new wxButton(m_panel_nTab1, 10001, "Open Folder", wxDefaultPosition, wxSize(80, 21));
	m_btn_openIMods = new wxButton(m_panel_nTab1, 10001, "Open Folder", wxDefaultPosition, wxSize(80, 21));
	m_btn_refreshMods = new wxButton(m_panel_nTab1, 10001, "Refresh", wxDefaultPosition, wxSize(80, 21));
	m_sizer_nTab1b->Add(m_btn_openAMods, 1,  wxLEFT, 7);
	m_sizer_nTab1b->AddStretchSpacer(1);
	m_sizer_nTab1b->Add(m_btn_refreshMods, 1, wxLEFT | wxRIGHT, 5);
	m_sizer_nTab1b->AddStretchSpacer(1);
	m_sizer_nTab1b->Add(m_btn_openIMods, 1, wxRIGHT, 9);

	// Tab 1 - Top-level Vertical Sizer
	m_sizer_nTab1 = new wxBoxSizer(wxVERTICAL);
	m_sizer_nTab1->AddSpacer(5);
	m_sizer_nTab1->Add(m_sizer_nTab1a, 1, wxEXPAND, 0);
	m_sizer_nTab1->Add(m_sizer_nTab1b, 0, wxEXPAND | wxTOP | wxBOTTOM, 3);
	m_panel_nTab1->SetSizer(m_sizer_nTab1);

	// Tab 2
	m_panel_nTab2 = new wxPanel(m_notebook, wxID_ANY);

	// Tab 2 - List Box
	m_list_xMods = new wxListBox(m_panel_nTab2, wxID_ANY);
	m_list_xMods->Append(wxT("Not Implemented"));  // TODO

	// Tab 2 - Horizontal Sizer
	m_sizer_nTab2a = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_nTab2a->AddStretchSpacer(1);
	m_sizer_nTab2a->Add(m_list_xMods, 2, wxEXPAND, 0);
	m_sizer_nTab2a->AddStretchSpacer(1);


	// Tab 2 - Vertical Sizer
	m_sizer_nTab2 = new wxBoxSizer(wxVERTICAL);
	m_sizer_nTab2->AddSpacer(10);
	m_sizer_nTab2->Add(m_sizer_nTab2a, 1, wxEXPAND, 0);
	m_sizer_nTab2->AddSpacer(10);
	m_panel_nTab2->SetSizer(m_sizer_nTab2);

	// Tab 3
	m_panel_nTab3 = new wxPanel(m_notebook, wxID_ANY);

	// Tab 3 - List Box
	m_listc_loadOrder = new wxListBox(m_panel_nTab3, wxID_ANY);
	m_listc_loadOrder->Append(wxT("Not Implemented"));  // TODO

	// Tab 3 - Horizontal Sizer
	m_sizer_nTab3a = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_nTab3a->AddStretchSpacer(1);
	m_sizer_nTab3a->Add(m_listc_loadOrder, 2, wxEXPAND, 0);
	m_sizer_nTab3a->AddStretchSpacer(1);


	// Tab 3 - Vertical Sizer
	m_sizer_nTab3 = new wxBoxSizer(wxVERTICAL);
	m_sizer_nTab3->AddSpacer(10);
	m_sizer_nTab3->Add(m_sizer_nTab3a, 1, wxEXPAND, 0);
	m_sizer_nTab3->AddSpacer(10);
	m_panel_nTab3->SetSizer(m_sizer_nTab3);

	// Notebook Tabs
	m_notebook->AddPage(m_panel_nTab1, "SMAPI Mods", true);
	m_notebook->AddPage(m_panel_nTab2, "XNB Mods", false);
	m_notebook->AddPage(m_panel_nTab3, "Load Order", false);

	// Band-aid fix for intial render issues (flips pages once)
	m_notebook->SetSelection(1);
	m_notebook->SetSelection(0);
	
	
	//---------------------------------
	//  Additional GUI Implementation
	//---------------------------------
	// Menubar - File, Help, etc
	menubar = new wxMenuBar;
	file = new wxMenu;
	help = new wxMenu;
	menubar->Append(file, wxT("&File"));
	menubar->Append(help, wxT("&Help"));
	SetMenuBar(menubar);

	// Right side buttons
	int r_btn_width = 200;
	int r_btn_height = 50;
	m_btn_launchSMAPI = new wxButton(this, 10001, "Launch SMAPI");
	m_btn_launchSDV = new wxButton(this, 10001, "Launch Stardew Valley");
	m_btn_addMod = new wxButton(this, 10001, "Add Mod from File");
	m_btn_dlMod = new wxButton(this, 10001, "Download Mod from Nexus");
	m_btn_delMod = new wxButton(this, 10001, "Delete Mod");

	// Right side button - sizer
	int prop_rBtns = 15;
	int prop_rSpace = 4;
	m_sizer_rBtns = new wxBoxSizer(wxVERTICAL);
	m_sizer_rBtns->Add(m_btn_launchSMAPI, prop_rBtns, wxEXPAND, 0);
	m_sizer_rBtns->AddStretchSpacer(prop_rSpace);
	m_sizer_rBtns->Add(m_btn_launchSDV, prop_rBtns, wxEXPAND, 0);
	m_sizer_rBtns->AddStretchSpacer(prop_rSpace);
	m_sizer_rBtns->Add(m_btn_addMod, prop_rBtns, wxEXPAND, 0);
	m_sizer_rBtns->AddStretchSpacer(prop_rSpace);
	m_sizer_rBtns->Add(m_btn_dlMod, prop_rBtns, wxEXPAND, 0);
	m_sizer_rBtns->AddStretchSpacer(prop_rSpace);
	m_sizer_rBtns->Add(m_btn_delMod, prop_rBtns, wxEXPAND, 0);

	// Window layout horizontal
	m_sizer_Hmain = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_Hmain->Add(m_notebook, 2, wxEXPAND | wxLEFT | wxRIGHT, 10);
	m_sizer_Hmain->Add(m_sizer_rBtns, 1, wxEXPAND | wxRIGHT, 10);

	// Banner
	wxImage::AddHandler(new wxPNGHandler);
	m_sbmp_banner = new wxStaticBitmap(this, wxID_ANY, wxBitmap("SDVMM2.png", wxBITMAP_TYPE_PNG));
	wxImage::CleanUpHandlers();

	// Version info
	string m_version_SMAPI = "1.1.1";
	string m_version_SDVMM2 = "1.0.0";
	m_sText_APIversion = new wxStaticText(this, wxID_ANY, "SMAPI Version: " + m_version_SMAPI);
	m_sText_MMversion = new wxStaticText(this, wxID_ANY, "SDVMM2 Version: " + m_version_SDVMM2);
	m_sizer_vInfo = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_vInfo->Add(m_sText_MMversion, 1, wxEXPAND | wxLEFT, 15);
	m_sizer_vInfo->Add(m_sText_APIversion, 1, wxEXPAND | wxLEFT, 5);
	m_sizer_vInfo->AddStretchSpacer(1);

	// Window layout Vertical + insert banner
	m_sizer_Vmain = new wxBoxSizer(wxVERTICAL);
	m_sizer_Vmain->Add(m_sbmp_banner, 16, wxEXPAND | wxALL, 10);
	m_sizer_Vmain->Add(m_sizer_Hmain, 40, wxEXPAND, 0);
	m_sizer_Vmain->Add(m_sizer_vInfo, 3, wxEXPAND, 0); // for static text
	SetSizer(m_sizer_Vmain);

	// Setting background colour as needed
	m_bg_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800, 500));
	wxColour* m_colour_grey = new wxColour(240, 240, 240, wxALPHA_OPAQUE);
	m_bg_panel->SetBackgroundColour(wxColour(*m_colour_grey));
	m_sText_APIversion->SetBackgroundColour(wxColour(*m_colour_grey));
	m_sText_MMversion->SetBackgroundColour(wxColour(*m_colour_grey));
	delete m_colour_grey;
}

cMain::~cMain()
{
}

void cMain::set_gamepath(string filepath)
{
	gamepath_ = filepath;
}

void cMain::popModLists()
{

}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	//m_list1->AppendString(m_txt1->GetValue());
	//evt.Skip();
}

void cMain::RefreshModList()
{

}