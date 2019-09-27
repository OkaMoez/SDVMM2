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
	m_panel_notebook_tab1 = new wxPanel(m_notebook, wxID_ANY);

	// Tab 1 - List Control - Creation w/ Columns
	m_dataviewlistctrl_mods = new wxDataViewListCtrl(m_panel_notebook_tab1, wxID_ANY, wxDefaultPosition, wxSize(465, 200), wxLC_REPORT);
	m_dataviewlistctrl_mods->AppendToggleColumn("Active",wxDATAVIEW_CELL_ACTIVATABLE, 50, wxALIGN_LEFT, 0);
	m_dataviewlistctrl_mods->AppendTextColumn("Name", wxDATAVIEW_CELL_INERT, 200, wxALIGN_LEFT, 0);
	m_dataviewlistctrl_mods->AppendTextColumn("Author", wxDATAVIEW_CELL_INERT, 135, wxALIGN_LEFT, 0);
	m_dataviewlistctrl_mods->AppendTextColumn("Version", wxDATAVIEW_CELL_INERT, 80, wxALIGN_LEFT, 0);
	m_dataviewlistctrl_mods->AppendTextColumn("Location", wxDATAVIEW_CELL_INERT, 500, wxALIGN_LEFT, 0);
	// TODO Either hide scroll bar or hide location data?
	m_dataviewlistctrl_mods->Bind(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, &cMain::ToggleMod, this);
	
	// Tab 1 - List - Vertical Sizers + Title Text
	m_sizer_notebook_tab1a_mods = new wxBoxSizer(wxVERTICAL);
	m_sizer_notebook_tab1a_mods->AddSpacer(5);
	m_sizer_notebook_tab1a_mods->Add(m_dataviewlistctrl_mods, 1, 0, 0);
	m_sizer_notebook_tab1a_mods->AddSpacer(2);

	// Tab 1 - List - Horizontal Sizer
	m_sizer_notebook_tab1a = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_notebook_tab1a->AddSpacer(8);
	m_sizer_notebook_tab1a->Add(m_sizer_notebook_tab1a_mods, 1, wxEXPAND, 0);
	m_sizer_notebook_tab1a->AddSpacer(10);

	// Tab 1 - Top-level Vertical Sizer
	m_sizer_notebook_tab1 = new wxBoxSizer(wxVERTICAL);
	m_sizer_notebook_tab1->AddSpacer(5);
	m_sizer_notebook_tab1->Add(m_sizer_notebook_tab1a, 1, wxEXPAND| wxBOTTOM, 3);
	m_panel_notebook_tab1->SetSizer(m_sizer_notebook_tab1);

	// Tab 2
	m_panel_notebook_tab2 = new wxPanel(m_notebook, wxID_ANY);

	// Tab 2 - List Box
	m_list_xnb_mods = new wxListBox(m_panel_notebook_tab2, wxID_ANY);
	m_list_xnb_mods->Append(wxT("Not Implemented"));  // TODO XNB support

	// Tab 2 - Horizontal Sizer
	m_sizer_notebook_tab2a = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_notebook_tab2a->AddStretchSpacer(1);
	m_sizer_notebook_tab2a->Add(m_list_xnb_mods, 2, wxEXPAND, 0);
	m_sizer_notebook_tab2a->AddStretchSpacer(1);


	// Tab 2 - Vertical Sizer
	m_sizer_notebook_tab2 = new wxBoxSizer(wxVERTICAL);
	m_sizer_notebook_tab2->AddSpacer(10);
	m_sizer_notebook_tab2->Add(m_sizer_notebook_tab2a, 1, wxEXPAND, 0);
	m_sizer_notebook_tab2->AddSpacer(10);
	m_panel_notebook_tab2->SetSizer(m_sizer_notebook_tab2);

	// Tab 3
	m_panel_notebook_tab3 = new wxPanel(m_notebook, wxID_ANY);

	// Tab 3 - List Box
	m_list_loadorder = new wxListBox(m_panel_notebook_tab3, wxID_ANY);
	m_list_loadorder->Append(wxT("Not Implemented"));  // TODO Load Order tomfoolery?

	// Tab 3 - Horizontal Sizer
	m_sizer_notebook_tab3a = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_notebook_tab3a->AddStretchSpacer(1);
	m_sizer_notebook_tab3a->Add(m_list_loadorder, 2, wxEXPAND, 0);
	m_sizer_notebook_tab3a->AddStretchSpacer(1);


	// Tab 3 - Vertical Sizer
	m_sizer_notebook_tab3 = new wxBoxSizer(wxVERTICAL);
	m_sizer_notebook_tab3->AddSpacer(10);
	m_sizer_notebook_tab3->Add(m_sizer_notebook_tab3a, 1, wxEXPAND, 0);
	m_sizer_notebook_tab3->AddSpacer(10);
	m_panel_notebook_tab3->SetSizer(m_sizer_notebook_tab3);

	// Notebook Tabs
	m_notebook->AddPage(m_panel_notebook_tab1, "SMAPI Mods", true);
	m_notebook->AddPage(m_panel_notebook_tab2, "XNB Mods", false);
	m_notebook->AddPage(m_panel_notebook_tab3, "Load Order", false); // TODO Delete?

	// Band-aid fix for intial render issues (flips pages once)
	m_notebook->SetSelection(1);
	m_notebook->SetSelection(0);
	
	//---------------------------------
	//  Additional GUI Implementation
	//---------------------------------
	// Menubar - File, Help, etc
	m_menubar = new wxMenuBar; // TODO Implement
	m_menubar_file = new wxMenu;
	m_menubar_help = new wxMenu;
	m_menubar->Append(m_menubar_file, wxT("File"));
	ID_MENU_MODS = wxNewId();
	ID_MENU_DMODS = wxNewId();
	m_menubar_file->Append(ID_MENU_MODS, "Open Mods Folder", wxEmptyString, wxITEM_NORMAL);
	m_menubar_file->Append(ID_MENU_DMODS, "Open Disabled Mods Folder", wxEmptyString, wxITEM_NORMAL);
	m_menubar->Append(m_menubar_help, wxT("&Help"));
	SetMenuBar(m_menubar);
	this->Bind(wxEVT_MENU, &cMain::OnMenuClick, this, ID_MENU_MODS);

	// Right side buttons
	int r_btn_width = 200;
	int r_btn_height = 50;
	m_button_launch_smapi = new wxButton(this, wxID_ANY, "Launch SMAPI with Mods");
	m_button_launch_vanilla = new wxButton(this, wxID_ANY, "Launch Stardew Valley"); // TODO FIX
	m_button_add_mod = new wxButton(this, wxID_ANY, "Add Mod from File"); // TODO
	m_button_download_mod = new wxButton(this, wxID_ANY, "Download Mod from Nexus"); // TODO
	m_button_refresh_mods = new wxButton(this, wxID_ANY, "Refresh Mod List"); // TODO Remove?
	m_button_launch_smapi->Bind(wxEVT_BUTTON, &cMain::OnLaunchSMAPIClick, this);
	m_button_launch_vanilla->Bind(wxEVT_BUTTON, &cMain::OnLaunchVanillaClick, this);

	m_button_refresh_mods->Bind(wxEVT_BUTTON, &cMain::OnRefreshClick, this);

	// Right side button - sizer
	int prop_rBtns = 15;
	int prop_rSpace = 4;
	m_sizer_buttons_right = new wxBoxSizer(wxVERTICAL);
	m_sizer_buttons_right->Add(m_button_launch_smapi, prop_rBtns, wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(prop_rSpace);
	m_sizer_buttons_right->Add(m_button_launch_vanilla, prop_rBtns, wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(prop_rSpace);
	m_sizer_buttons_right->Add(m_button_add_mod, prop_rBtns, wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(prop_rSpace);
	m_sizer_buttons_right->Add(m_button_download_mod, prop_rBtns, wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(prop_rSpace);
	m_sizer_buttons_right->Add(m_button_refresh_mods, prop_rBtns, wxEXPAND, 0);

	// Window layout horizontal
	m_sizer_main_horizontal = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_main_horizontal->Add(m_notebook, 2, wxEXPAND | wxLEFT | wxRIGHT, 10);
	m_sizer_main_horizontal->Add(m_sizer_buttons_right, 1, wxEXPAND | wxRIGHT, 10);

	// Banner
	wxImage::AddHandler(new wxPNGHandler);
	m_bitmap_banner = new wxStaticBitmap(this, wxID_ANY, wxBitmap("SDVMM2.png", wxBITMAP_TYPE_PNG)); // TODO save in code?
	wxImage::CleanUpHandlers();

	// Version info
	string m_version_smapi = "1.1.1"; // TODO Fetch
	string m_version_this_mm = "1.0.0";
	m_stext_smapi_version = new wxStaticText(this, wxID_ANY, "SMAPI Version: " + m_version_smapi); // TODO Fetch
	m_stext_this_version = new wxStaticText(this, wxID_ANY, "SDVMM2 Version: " + m_version_this_mm);
	m_sizer_version_info = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_version_info->Add(m_stext_this_version, 1, wxEXPAND | wxLEFT, 15);
	m_sizer_version_info->Add(m_stext_smapi_version, 1, wxEXPAND | wxLEFT, 5);
	m_sizer_version_info->AddStretchSpacer(1);

	// Window layout Vertical + insert banner
	m_sizer_main_vertical = new wxBoxSizer(wxVERTICAL);
	m_sizer_main_vertical->Add(m_bitmap_banner, 16, wxEXPAND | wxALL, 10);
	m_sizer_main_vertical->Add(m_sizer_main_horizontal, 40, wxEXPAND, 0);
	m_sizer_main_vertical->Add(m_sizer_version_info, 3, wxEXPAND, 0); // for static text
	SetSizer(m_sizer_main_vertical);

	// Setting background colour as needed
	m_bg_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(800, 500));
	wxColour* m_colour_grey = new wxColour(240, 240, 240, wxALPHA_OPAQUE);
	//m_bg_panel->SetBackgroundColour(wxColour(*m_colour_grey));
	//m_notebook->SetBackgroundColour(wxColour(*m_colour_grey));
	m_stext_smapi_version->SetBackgroundColour(wxColour(*m_colour_grey));
	m_stext_this_version->SetBackgroundColour(wxColour(*m_colour_grey));
	/*
	m_button_launch_smapi->SetBackgroundColour(wxColour(*m_colour_grey));
	m_button_launch_vanilla->SetBackgroundColour(wxColour(*m_colour_grey));
	m_button_add_mod->SetBackgroundColour(wxColour(*m_colour_grey));
	m_button_download_mod->SetBackgroundColour(wxColour(*m_colour_grey));
	m_button_refresh_mods->SetBackgroundColour(wxColour(*m_colour_grey));
	*/
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

void cMain::OnMenuClick(wxCommandEvent& event) // TODO complete
{
	if (event.GetId() == (ID_MENU_MODS))
	{
		OnMenuModsClick(event);
	}
	else if (event.GetId() == (ID_MENU_DMODS))
	{
		OnMenuModsDisabledClick(event);
	}
	else {}
}

void cMain::OnMenuModsClick(wxCommandEvent& event)
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

void cMain::OnMenuModsDisabledClick(wxCommandEvent& event)
{
	event.Skip();
	string test_str = ("explorer " + (this->gamepath() + "\\Mods_disabled"));
	const char* open_command = (test_str.c_str());
	wxExecute(open_command, wxEXEC_ASYNC, NULL);
}

void cMain::OnRefreshClick(wxCommandEvent& event) // TODO give some indication of the refresh
{
	event.Skip();
	this->RefreshModLists();
}

void cMain::ToggleMod(wxDataViewEvent& event)
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
	m_dataviewlistctrl_mods->GetValue(temp_path, m_dataviewlistctrl_mods->GetSelectedRow(), 4);
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
	RefreshModLists();
}

void cMain::FormatOldVersion(json& manifest) // TODO remove? currently is rejected by smapi
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

void cMain::RefreshModLists()
{
	wxWindowUpdateLocker noUpdates(m_dataviewlistctrl_mods);
	m_dataviewlistctrl_mods->DeleteAllItems();
	LoadModsFromDir("\\Mods\\");
	LoadModsFromDir("\\Mods_disabled\\");
}

void cMain::LoadModsFromDir(string folder_name) // TODO replace custom ioFunctions with filesystem
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

		this->FormatOldVersion(json_manifest);

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
			this->m_dataviewlistctrl_mods->AppendItem(thisMod);
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

bool cMain::ExistsModFolders()
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