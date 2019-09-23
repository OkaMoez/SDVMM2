#include "cMain.h"

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
	wxNotebook* m_notebook = new wxNotebook(this, -1);

	// Tab 1
	wxPanel* test_panelX = new wxPanel(m_notebook, wxID_ANY);
	wxBoxSizer* m_sizer_nTab1 = new wxBoxSizer(wxVERTICAL);

	// Tab 1 - List Boxes - Creation
	wxListBox* m_listc_aMods = new wxListBox(test_panelX, wxID_ANY);
	wxListBox* m_listc_iMods = new wxListBox(test_panelX, wxID_ANY);

	// Tab 1 - List Boxes - Vertical Lists + Title Text
	wxBoxSizer* m_sizer_nTab1a_aMods = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* m_sizer_nTab1a_iMods = new wxBoxSizer(wxVERTICAL);
	wxStaticText* m_sText_aMod = new wxStaticText(test_panelX, wxID_ANY, "Active Mods");
	wxStaticText* m_sText_iMod = new wxStaticText(test_panelX, wxID_ANY, "Inactive Mods");
	wxFont m_font = m_sText_aMod->GetFont();
	m_font.SetWeight(wxFONTWEIGHT_BOLD);
	m_sText_aMod->SetFont(m_font);
	m_sText_iMod->SetFont(m_font);
	m_sizer_nTab1a_aMods->Add(m_sText_aMod, 0, 0, 0);
	m_sizer_nTab1a_aMods->Add(m_listc_aMods, 1, wxEXPAND, 0);
	m_sizer_nTab1a_iMods->Add(m_sText_iMod, 0, 0, 0);
	m_sizer_nTab1a_iMods->Add(m_listc_iMods, 1, wxEXPAND, 0);

	// Tab 1 - List Boxes - Horizontal List Sizer
	wxBoxSizer* m_sizer_nTab1a = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_nTab1a->Add(m_sizer_nTab1a_aMods, 1, wxEXPAND | wxLEFT, 8);
	m_sizer_nTab1a->AddSpacer(10);
	m_sizer_nTab1a->Add(m_sizer_nTab1a_iMods, 1, wxEXPAND | wxRIGHT, 10);

	// tab 1 - bottom buttons 
	wxBoxSizer* m_sizer_nTab1b = new wxBoxSizer(wxHORIZONTAL);
	m_btn_openAMods = new wxButton(test_panelX, 10001, "Open Folder", wxDefaultPosition, wxSize(80, 21));
	m_btn_openIMods = new wxButton(test_panelX, 10001, "Open Folder", wxDefaultPosition, wxSize(80, 21));
	m_btn_refreshMods = new wxButton(test_panelX, 10001, "Refresh", wxDefaultPosition, wxSize(80, 21));
	m_sizer_nTab1b->Add(m_btn_openAMods, 1,  wxLEFT, 7);
	m_sizer_nTab1b->AddStretchSpacer(1);
	m_sizer_nTab1b->Add(m_btn_refreshMods, 1, wxLEFT | wxRIGHT, 5);
	m_sizer_nTab1b->AddStretchSpacer(1);
	m_sizer_nTab1b->Add(m_btn_openIMods, 1, wxRIGHT, 9);

	// Tab 1 - Top-level Vertical Sizer
	m_sizer_nTab1->AddSpacer(5);
	m_sizer_nTab1->Add(m_sizer_nTab1a, 1, wxEXPAND, 0);
	m_sizer_nTab1->Add(m_sizer_nTab1b, 0, wxEXPAND | wxTOP | wxBOTTOM, 3);
	test_panelX->SetSizer(m_sizer_nTab1);

	// tab 2
	wxPanel* test_panelY = new wxPanel(m_notebook, wxID_ANY);
	wxBoxSizer* m_sizer_nTab2 = new wxBoxSizer(wxVERTICAL);
	wxPanel* test_panel1 = new wxPanel(test_panelY, wxID_ANY);
	test_panel1->SetBackgroundColour(*wxRED);
	m_sizer_nTab2->AddSpacer(5);
	m_sizer_nTab2->Add(test_panel1, 1, wxEXPAND, 0);
	m_sizer_nTab2->AddSpacer(30);
	test_panelY->SetSizer(m_sizer_nTab2);

	// tab 3
	wxPanel* test_panelZ = new wxPanel(m_notebook, wxID_ANY);
	wxBoxSizer* m_sizer_nTab3 = new wxBoxSizer(wxVERTICAL);
	wxPanel* test_panel2 = new wxPanel(test_panelZ, wxID_ANY);
	test_panel2->SetBackgroundColour(*wxRED);
	m_sizer_nTab3->AddSpacer(5);
	m_sizer_nTab3->Add(test_panel2, 1, wxEXPAND, 0);
	m_sizer_nTab3->AddSpacer(30);
	test_panelZ->SetSizer(m_sizer_nTab3);

	m_notebook->AddPage(test_panelX, "SMAPI Mods", true);
	m_notebook->AddPage(test_panelY, "XNB Mods", false);
	m_notebook->AddPage(test_panelZ, "Load Order", false);

	// Band-aid fix for intial render issues
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
	wxBoxSizer* m_sizer_rBtns = new wxBoxSizer(wxVERTICAL);
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
	wxBoxSizer* m_sizer_Hmain = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_Hmain->Add(m_notebook, 2, wxEXPAND | wxLEFT | wxRIGHT, 10);
	m_sizer_Hmain->Add(m_sizer_rBtns, 1, wxEXPAND | wxRIGHT, 10);

	// Banner
	wxImage::AddHandler(new wxPNGHandler);
	wxStaticBitmap* m_sbmp_banner = new wxStaticBitmap(this, wxID_ANY, wxBitmap("SDVMM2.png", wxBITMAP_TYPE_PNG));
	wxImage::CleanUpHandlers();

	// Version info
	std::string m_version_SMAPI = "1.1.1";
	std::string m_version_SDVMM2 = "1.0.0";
	wxStaticText* m_sText_APIversion = new wxStaticText(this, wxID_ANY, "SMAPI Version: " + m_version_SMAPI);
	wxStaticText* m_sText_MMversion = new wxStaticText(this, wxID_ANY, "SDVMM2 Version: " + m_version_SDVMM2);
	wxBoxSizer* m_sizer_vInfo = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_vInfo->Add(m_sText_MMversion, 1, wxEXPAND | wxLEFT, 15);
	m_sizer_vInfo->Add(m_sText_APIversion, 1, wxEXPAND | wxLEFT, 5);
	m_sizer_vInfo->AddStretchSpacer(1);

	// Window layout Vertical + insert banner
	wxBoxSizer* m_sizer_Vmain = new wxBoxSizer(wxVERTICAL);
	m_sizer_Vmain->Add(m_sbmp_banner, 16, wxEXPAND | wxALL, 10);
	m_sizer_Vmain->Add(m_sizer_Hmain, 40, wxEXPAND, 0);
	m_sizer_Vmain->Add(m_sizer_vInfo, 3, wxEXPAND, 0); // for static text
	SetSizer(m_sizer_Vmain);

	// Setting background colour as needed
	wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800, 500));
	wxColour* m_colour_grey = new wxColour(240, 240, 240, wxALPHA_OPAQUE);
	panel->SetBackgroundColour(wxColour(*m_colour_grey));
	m_sText_APIversion->SetBackgroundColour(wxColour(*m_colour_grey));
	m_sText_MMversion->SetBackgroundColour(wxColour(*m_colour_grey));
	delete m_colour_grey;
}

cMain::~cMain()
{
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	//m_list1->AppendString(m_txt1->GetValue());
	//evt.Skip();
}