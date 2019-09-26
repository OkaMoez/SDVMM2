#include "cApp.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	// Obsolete?
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "SDVMM 2",
	wxDefaultPosition, wxSize(750,500),
	wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	//---------------------------
	//  Notebook Implementation
	//---------------------------
	// Tab 1, 2, 3 = Active/Inactive Mods, XNB Mods, Drag/Drop Load Order
	m_notebook = new wxNotebook(this, -1);

	// Tab 1
	m_panel_nTab1 = new wxPanel(m_notebook, wxID_ANY);

	// Tab 1 - List Control - Creation w/ Columns
	m_dvlc_Mods = new wxDataViewListCtrl(m_panel_nTab1, wxID_ANY, wxDefaultPosition, wxSize(465, 200), wxLC_REPORT);
	m_dvlc_Mods->AppendToggleColumn("Active",wxDATAVIEW_CELL_ACTIVATABLE, 50, wxALIGN_LEFT, 0);
	m_dvlc_Mods->AppendTextColumn("Name", wxDATAVIEW_CELL_INERT, 200, wxALIGN_LEFT, 0);
	m_dvlc_Mods->AppendTextColumn("Author", wxDATAVIEW_CELL_INERT, 135, wxALIGN_LEFT, 0);
	m_dvlc_Mods->AppendTextColumn("Version", wxDATAVIEW_CELL_INERT, 80, wxALIGN_LEFT, 0);
	m_dvlc_Mods->AppendTextColumn("Location", wxDATAVIEW_CELL_INERT, 500, wxALIGN_LEFT, 0);
	// TODO Either hide scroll bar or hid location data
	m_dvlc_Mods->Bind(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, &cMain::toggleMod, this);
	

	// Tab 1 - List - Vertical Sizers + Title Text
	m_sizer_nTab1a_Mods = new wxBoxSizer(wxVERTICAL);
	m_sizer_nTab1a_Mods->AddSpacer(5);
	m_sizer_nTab1a_Mods->Add(m_dvlc_Mods, 1, 0, 0);
	m_sizer_nTab1a_Mods->AddSpacer(2);

	// Tab 1 - List - Horizontal Sizer
	m_sizer_nTab1a = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_nTab1a->AddSpacer(8);
	m_sizer_nTab1a->Add(m_sizer_nTab1a_Mods, 1, wxEXPAND, 0);
	m_sizer_nTab1a->AddSpacer(10);

	// tab 1 - Bottom Buttons 
	m_sizer_nTab1b = new wxBoxSizer(wxHORIZONTAL);
	m_btn_openAMods = new wxButton(m_panel_nTab1, 10001, "Open Mods", wxDefaultPosition, wxSize(80, 21));
	m_btn_openIMods = new wxButton(m_panel_nTab1, 10001, "Disabled Mods", wxDefaultPosition, wxSize(80, 21));
	m_btn_refreshMods = new wxButton(m_panel_nTab1, 10001, "Refresh", wxDefaultPosition, wxSize(60, 21));
	m_btn_openAMods->Bind(wxEVT_BUTTON, &cMain::OnModsClick, this);
	m_btn_openIMods->Bind(wxEVT_BUTTON, &cMain::OnDisabledClick, this);
	m_btn_refreshMods->Bind(wxEVT_BUTTON, &cMain::OnRefreshClick, this);
	m_sizer_nTab1b->Add(m_btn_openAMods, 5,  wxLEFT, 7);
	m_sizer_nTab1b->AddStretchSpacer(3);
	m_sizer_nTab1b->Add(m_btn_refreshMods, 4, wxLEFT | wxRIGHT, 5);
	m_sizer_nTab1b->AddStretchSpacer(3);
	m_sizer_nTab1b->Add(m_btn_openIMods, 5, wxRIGHT, 9);

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
	m_list_loadOrder = new wxListBox(m_panel_nTab3, wxID_ANY);
	m_list_loadOrder->Append(wxT("Not Implemented"));  // TODO

	// Tab 3 - Horizontal Sizer
	m_sizer_nTab3a = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_nTab3a->AddStretchSpacer(1);
	m_sizer_nTab3a->Add(m_list_loadOrder, 2, wxEXPAND, 0);
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
	m_notebook->AddPage(m_panel_nTab3, "Load Order", false); // TODO Delete

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
	m_btn_launchVanilla = new wxButton(this, 10001, "Launch Stardew Valley");
	m_btn_addMod = new wxButton(this, 10001, "Add Mod from File");
	m_btn_dlMod = new wxButton(this, 10001, "Download Mod from Nexus");
	m_btn_delMod = new wxButton(this, 10001, "Delete Mod");
	m_btn_launchSMAPI->Bind(wxEVT_BUTTON, &cMain::OnLaunchSMAPIClick, this);
	m_btn_launchVanilla->Bind(wxEVT_BUTTON, &cMain::OnLaunchSMAPIClick, this);

	// Right side button - sizer
	int prop_rBtns = 15;
	int prop_rSpace = 4;
	m_sizer_rBtns = new wxBoxSizer(wxVERTICAL);
	m_sizer_rBtns->Add(m_btn_launchSMAPI, prop_rBtns, wxEXPAND, 0);
	m_sizer_rBtns->AddStretchSpacer(prop_rSpace);
	m_sizer_rBtns->Add(m_btn_launchVanilla, prop_rBtns, wxEXPAND, 0);
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

void cMain::OnLaunchSMAPIClick(wxCommandEvent& event)
{
	event.Skip();
	string test_str = ((this->gamepath() + "\\StardewModdingAPI"));
	const char* open_command = (test_str.c_str());
	wxExecute(open_command, wxEXEC_ASYNC, NULL);

}

void cMain::OnLaunchVanillaClick(wxCommandEvent& event)
{
	event.Skip();
	string test_str = ((this->gamepath() + "\\Stardew Valley"));
	const char* open_command = (test_str.c_str());
	wxExecute(open_command, wxEXEC_ASYNC, NULL);

}

void cMain::OnModsClick(wxCommandEvent& event)
{
	event.Skip();
	string test_str = ("explorer " + (this->gamepath() + "\\Mods\\"));
	const char* open_command = (test_str.c_str());
	wxExecute(open_command, wxEXEC_ASYNC, NULL);


	/*
	Windows - explorer
	mac - open
	linux - konqueror or whatever gnome uses (nautilus?)
	*/
}

void cMain::OnDisabledClick(wxCommandEvent& event)
{
	event.Skip();
	string test_str = ("explorer " + (this->gamepath() + "\\Mods_disabled"));
	const char* open_command = (test_str.c_str());
	wxExecute(open_command, wxEXEC_ASYNC, NULL);
}

void cMain::OnRefreshClick(wxCommandEvent& event)
{
	event.Skip();
	this->refreshModLists();
}

void cMain::toggleMod(wxDataViewEvent& event)
{
	event.Skip();
	
	D(
		if (report_cbox_event) {
			wxMessageDialog* event_toggle_box1 = new wxMessageDialog(NULL,
				wxT("Mod toggled."), wxT("Event captured"),
				wxOK, wxDefaultPosition);
			event_toggle_box1->ShowModal();
			delete event_toggle_box1;
		}
		else {}
	)
	wxVariant temp_path("");
	m_dvlc_Mods->GetValue(temp_path, m_dvlc_Mods->GetSelectedRow(), 4);
	fs::path mod_path = string(temp_path);
	fs::path parent_path = mod_path.parent_path();
	fs::path folder_name = mod_path.filename();

	if (parent_path == ((this->gamepath()) += "\\Mods"))
	{
		D(
			if (report_file_move_event) {
				wxMessageDialog* event_toggle_box2 = new wxMessageDialog(NULL,
					wxT("Was in Mods"), wxT("Event item info"),
					wxOK, wxDefaultPosition);
				event_toggle_box2->ShowModal();
				delete event_toggle_box2;
			}
			else {}
		)

		fs::copy(mod_path, (fs::path(this->gamepath() += "\\Mods_disabled\\") += folder_name));
		fs::remove_all(mod_path);

	}
	else if (parent_path == ((this->gamepath()) += "\\Mods_disabled"))
	{
		D(
			if (report_file_move_event) {
				wxMessageDialog* event_toggle_box2 = new wxMessageDialog(NULL,
					wxT("Was in Mods_disabled"), wxT("Event item info"),
					wxOK, wxDefaultPosition);
				event_toggle_box2->ShowModal();
				delete event_toggle_box2;
			}
			else{}
		)

			fs::copy(mod_path, (fs::path(this->gamepath() += "\\Mods\\") += folder_name));
			fs::remove_all(mod_path);
	}
	else
	{
		D(
			if (report_file_move_event) {
				wxMessageDialog* event_toggle_ebox1 = new wxMessageDialog(NULL,
					wxT("Bad path"), wxT("Event item info"),
					wxOK, wxDefaultPosition);
				event_toggle_ebox1->ShowModal();
				delete event_toggle_ebox1;
			}
			else{}
		)
	}
	refreshModLists();
}

void cMain::formatOldVersion(json& manifest)
{
	string temp_v = "";
	if (manifest.at("Version").is_object())
	{
		int temp_v1 = NULL;
		int temp_v2 = NULL;
		int temp_v3 = NULL;
		manifest["Version"]["MajorVersion"].get_to(temp_v1);
		manifest["Version"]["MinorVersion"].get_to(temp_v2);
		manifest["Version"]["PatchVersion"].get_to(temp_v3);
		temp_v = std::to_string(temp_v1)
			+ "." + std::to_string(temp_v2)
			+ "." + std::to_string(temp_v3);
		manifest.erase("Version");
		manifest["Version"] = temp_v;
	}
	else
		manifest.at("Version").get_to(temp_v);

	D(
		if (report_got_version) {
			wxMessageDialog* m_pBox2 = new wxMessageDialog(NULL,
				("got version: " + temp_v), wxT("File Check"),
				wxOK, wxDefaultPosition);
			m_pBox2->ShowModal();
			delete m_pBox2;
		}
		else {}
	)
}

void cMain::refreshModLists()
{
	wxWindowUpdateLocker noUpdates(m_dvlc_Mods);
	m_dvlc_Mods->DeleteAllItems();
	loadModsFromDir("\\Mods\\");
	loadModsFromDir("\\Mods_disabled\\");
}

void cMain::loadModsFromDir(string folder_name)
{
	json json_manifest;
	bool is_good_json = false;
	bool is_active = (folder_name == "\\Mods\\");
	fs::path temp_dir = (this->gamepath());
	temp_dir += folder_name;
	fs::path temp_path;
	for (auto& dir_iter : fs::directory_iterator(temp_dir))
	{
		is_good_json = false;
		temp_path = dir_iter.path();
		temp_path += "\\manifest.json";


		D(
			if (report_looped_path) {
				wxMessageDialog* m_pBox6 = new wxMessageDialog(NULL,
					(temp_path.string()), wxT("Path Check"),
					wxOK, wxDefaultPosition);
				m_pBox6->ShowModal();
				delete m_pBox6;
			}
			else {}
		)

			int json_problem = NULL;
		ifstream json_stream(temp_path.c_str());
		try {
			json_manifest = json::parse(json_stream); // TODO prompt user to handle trailing commas
			is_good_json = true;
		}
		catch (json::parse_error & e) {
			is_good_json = false;
			string temp_exc = e.what();

			if (e.id == 101) { // TODO use exception id
				json_problem = 1;
			}
			else {
				json_problem = 2;
			}

			D(
				if (report_parse_exception) {
					wxMessageDialog* m_pBox2 = new wxMessageDialog(NULL,
						temp_exc, wxT("Exception Report"),
						wxOK, wxDefaultPosition);
					m_pBox2->ShowModal();
					delete m_pBox2;
				}
				else {}
			)

		}

		this->formatOldVersion(json_manifest);

		if (existsFile(temp_path.string()) and is_good_json == true) // TODO Review
		{
			D(
				if (report_parsed_mod_data) {
					string temp_msg1 = "";
					string temp_msg2 = "";
					json_manifest["Name"].get_to(temp_msg1);
					json_manifest["Version"].get_to(temp_msg2);
					wxMessageDialog* m_pBox2 = new wxMessageDialog(NULL,
						(temp_msg1 + " exists, " + temp_msg2),
						wxT("File Check"), wxOK, wxDefaultPosition);
					m_pBox2->ShowModal();
					delete m_pBox2;
				}
				else {}
			)

				cMod aMod(json_manifest);
			wxVector<wxVariant> thisMod;
			thisMod.push_back(wxVariant(is_active));
			thisMod.push_back(wxVariant(aMod.mod_name()));
			thisMod.push_back(wxVariant(aMod.mod_author()));
			thisMod.push_back(wxVariant(aMod.mod_version()));
			thisMod.push_back(wxVariant((dir_iter.path()).string()));
			this->m_dvlc_Mods->AppendItem(thisMod);
			thisMod.clear();

			/*
			wxStringClientData *ldata = new wxStringClientData(wxT("MyID123"));
			m_listCtrl->AppendItem(data, (wxUIntPtr)ldata);

			wxStringClientData *pStrData = (wxStringClientData*) m_listCtrl->GetItemData(m_listCtrl->GetCurrentItem());
				if(!pStrData)
			wxString id = pStrData->GetData();
			*/

			D(
				if (report_mod_object_data) {
					wxMessageDialog* m_pBox2 = new wxMessageDialog(NULL,
						(aMod.infoString()), wxT("Mod Object"),
						wxOK, wxDefaultPosition);
					m_pBox2->ShowModal();
					delete m_pBox2;
				}
				else {}
			)
		}
		else if (is_good_json == false)
		{
			if (json_problem == 1)
			{
				wxMessageDialog* init_eBox1 = new wxMessageDialog(NULL,
					wxT("Bad Format: Illegal trailing comma at:\n" + temp_path.string()),
					wxT("manifest.json error"), wxOK, wxDefaultPosition);
				init_eBox1->ShowModal();
				delete init_eBox1;
			}
			else if (json_problem)
			{
				wxMessageDialog* init_eBox2 = new wxMessageDialog(NULL,
					wxT("Bad Format: I dunno yet."), wxT("manifest.json error"),
					wxOK, wxDefaultPosition);
				init_eBox2->ShowModal();
				delete init_eBox2;
			}
			else {}
		}
	}
}

bool cMain::existsModFolders()
{
	fs::path mod_path = this->gamepath();
	fs::path mod_d_path = this->gamepath();
	fs::path game_file_path = this->gamepath();
	mod_path += "\\Mods";
	mod_d_path += "\\Mods_disabled";
	game_file_path += "\\Stardew Valley.exe"; // TODO Make crossplatform?

	if (!(fs::exists(game_file_path) and fs::is_regular_file(game_file_path)))
	{
		D(
			wxMessageDialog * init_mfBox1 = new wxMessageDialog(NULL,
				wxT("Game executable not found on path:\n" + game_file_path.string()),
				wxT("wrong directory"), wxOK, wxDefaultPosition);
		init_mfBox1->ShowModal();
		delete init_mfBox1;
		)
			return false;
	}
	else
	{
		if (!(fs::exists(mod_path) and fs::is_directory(mod_path)))
		{
			fs::create_directory(mod_path);
			D(
				if (report_mod_directories) {
					wxMessageDialog* init_mdBox1 = new wxMessageDialog(NULL,
						mod_path.string(), wxT("Mods Directory Created"),
						wxOK, wxDefaultPosition);
					init_mdBox1->ShowModal();
					delete init_mdBox1;
				}
				else {}
			)
		}
		else
		{
			D(
				if (report_mod_directories) {
					wxMessageDialog* init_mdBox1 = new wxMessageDialog(NULL,
						mod_path.string(), wxT("Mods Directory Found"),
						wxOK, wxDefaultPosition);
					init_mdBox1->ShowModal();
					delete init_mdBox1;
				}
				else {}
			)
		}
		if (!(fs::exists(mod_d_path) and fs::is_directory(mod_d_path)))
		{
			fs::create_directory(mod_d_path);
			D(
				if (report_mod_directories) {
					wxMessageDialog* init_mdBox1 = new wxMessageDialog(NULL,
						mod_d_path.string(), wxT("Mods_d Directory Created"),
						wxOK, wxDefaultPosition);
					init_mdBox1->ShowModal();
					delete init_mdBox1;
				}
				else {}
			)
		}
		else
		{
			D(
				if (report_mod_directories) {
					wxMessageDialog* init_mdBox1 = new wxMessageDialog(NULL,
						mod_d_path.string(), wxT("Mods_d Directory Found"),
						wxOK, wxDefaultPosition);
					init_mdBox1->ShowModal();
					delete init_mdBox1;
				}
				else {}
			)
		}
	}
	return true;
}