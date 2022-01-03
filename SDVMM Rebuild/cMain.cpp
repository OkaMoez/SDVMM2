#include "cMain.h"
#include "strip.h"

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Stardew Valley Mod Manager 2",
	wxDefaultPosition, wxSize(750, 500),
	wxDEFAULT_FRAME_STYLE)
{
	SetMinSize(wxSize(750, 500));

	//---------------------------
	//  Notebook Implementation
	//---------------------------
	// Tab 1, 2, 3 = Active/Inactive Mods, XNB Mods, Settings
	m_notebook = new wxNotebook(this, -1);

	// Tab 1
	m_panel_notebook_tab1 = new wxPanel(m_notebook, wxID_ANY);

	// Tab 1 - List Control - Creation w/ Columns
	m_dataviewlistctrl_mods = new wxDataViewListCtrl(m_panel_notebook_tab1, wxID_ANY, wxDefaultPosition, wxSize(465, 200), wxLC_REPORT);
	m_dataviewlistctrl_mods->AppendToggleColumn("Active", wxDATAVIEW_CELL_ACTIVATABLE, 50, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE);
	m_dataviewlistctrl_mods->AppendTextColumn("Name", wxDATAVIEW_CELL_INERT, 200, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE);
	m_dataviewlistctrl_mods->AppendTextColumn("Author", wxDATAVIEW_CELL_INERT, 135, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE);
	m_dataviewlistctrl_mods->AppendTextColumn("Version", wxDATAVIEW_CELL_INERT, 80, wxALIGN_LEFT, 0);
	m_dataviewlistctrl_mods->AppendTextColumn("Location", wxDATAVIEW_CELL_INERT, 500, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE);
	// TODO Either hide scroll bar or hide location data?
	m_dataviewlistctrl_mods->Bind(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, &cMain::OnToggleClick, this);
	m_dataviewlistctrl_mods->Bind(wxEVT_DATAVIEW_COLUMN_HEADER_CLICK, &cMain::OnSortClick, this);

	// Tab 1 - List - Vertical Sizers + Title Text
	m_sizer_notebook_tab1a_mods = new wxBoxSizer(wxVERTICAL);
	m_sizer_notebook_tab1a_mods->AddSpacer(5);
	m_sizer_notebook_tab1a_mods->Add(m_dataviewlistctrl_mods, 1, wxEXPAND, 0);
	m_sizer_notebook_tab1a_mods->AddSpacer(6);

	// Tab 1 - List - Horizontal Sizer
	m_sizer_notebook_tab1a = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_notebook_tab1a->AddSpacer(8);
	m_sizer_notebook_tab1a->Add(m_sizer_notebook_tab1a_mods, 1, wxEXPAND, 0);
	m_sizer_notebook_tab1a->AddSpacer(10);

	// Tab 1 - Top-level Vertical Sizer
	m_sizer_notebook_tab1 = new wxBoxSizer(wxVERTICAL);
	m_sizer_notebook_tab1->AddSpacer(5);
	m_sizer_notebook_tab1->Add(m_sizer_notebook_tab1a, 1, wxEXPAND | wxBOTTOM, 3);
	m_panel_notebook_tab1->SetSizer(m_sizer_notebook_tab1);

	/* // REMOVED FOR 0.5.0-ALPHA RELEASE
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
	*/

	// Tab 3
	m_panel_notebook_tab3 = new SettingsPanel(m_notebook, wxID_ANY, this);

	// Notebook Tabs
	m_notebook->AddPage(m_panel_notebook_tab1, "SMAPI Mods", true);
	//m_notebook->AddPage(m_panel_notebook_tab2, "XNB Mods", false); // REMOVED FOR 0.5.0-ALPHA RELEASE
	m_notebook->AddPage(m_panel_notebook_tab3, "Settings", false);

	//---------------------------------
	//  Additional GUI Implementation
	//---------------------------------
	// Menubar - File, Help, etc
	m_menubar = new wxMenuBar; // TODO Implement
	m_menubar_file = new wxMenu;
	//m_menubar_help = new wxMenu; // REMOVED FOR 0.5.0-ALPHA RELEASE
	m_menubar->Append(m_menubar_file, wxT("&File"));
	m_menubar_file->Append(ID_MENU_MODS, wxT("&Open Mods Folder"), wxEmptyString, wxITEM_NORMAL);
	m_menubar_file->Append(ID_MENU_DMODS, wxT("&Open Disabled Mods Folder"), wxEmptyString, wxITEM_NORMAL);
	m_menubar_file->Append(ID_MENU_QUIT, wxT("&Quit"), wxEmptyString, wxITEM_NORMAL);
	//m_menubar->Append(m_menubar_help, wxT("&Help")); // REMOVED FOR 0.5.0-ALPHA RELEASE
	SetMenuBar(m_menubar);
	this->Bind(wxEVT_MENU, &cMain::OnMenuClick, this, ID_MENU_MODS, ID_MENU_QUIT);

	// Right side buttons
	m_panel_buttons_right = new wxPanel(this);
	m_button_launch_smapi = new wxButton(m_panel_buttons_right, wxID_ANY, "Launch SMAPI with Mods");
	m_button_launch_vanilla = new wxButton(m_panel_buttons_right, wxID_ANY, "Launch Stardew Valley");
	m_button_add_mod = new wxButton(m_panel_buttons_right, wxID_ANY, ""); // TODO "Add Mod from File/Archive" // REMOVED FOR 0.5.0-ALPHA RELEASE
	m_button_nexus_download = new wxButton(m_panel_buttons_right, ID_BUTTON_NEXUS, "Visit Nexus Mods");
	m_button_forums_download = new wxButton(m_panel_buttons_right, ID_BUTTON_FORUMS, "Visit Mod Forums");
	m_button_refresh_mods = new wxButton(m_panel_buttons_right, wxID_ANY, "Refresh Mod List");
	m_button_launch_smapi->Bind(wxEVT_BUTTON, &cMain::OnLaunchSMAPIClick, this);
	m_button_launch_vanilla->Bind(wxEVT_BUTTON, &cMain::OnLaunchVanillaClick, this);
	m_button_nexus_download->Bind(wxEVT_BUTTON, &cMain::OnLaunchModSiteClick, this);
	m_button_forums_download->Bind(wxEVT_BUTTON, &cMain::OnLaunchModSiteClick, this);
	m_button_refresh_mods->Bind(wxEVT_BUTTON, &cMain::OnRefreshClick, this);

	// Right side button - sizer
	int proportion_button = 10;
	int proportion_spacer = 1;
	m_sizer_buttons_right = new wxBoxSizer(wxVERTICAL);
	m_sizer_buttons_right->Add(m_button_launch_smapi, proportion_button, wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(proportion_spacer);
	m_sizer_buttons_right->Add(m_button_launch_vanilla, proportion_button, wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(proportion_spacer);
	m_sizer_buttons_right->Add(m_button_add_mod, (proportion_button / 2), wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(proportion_spacer);
	m_sizer_buttons_right->Add(m_button_nexus_download, (proportion_button / 2), wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(proportion_spacer);
	m_sizer_buttons_right->Add(m_button_forums_download, (proportion_button / 2), wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(proportion_spacer);
	m_sizer_buttons_right->Add(m_button_refresh_mods, proportion_button, wxEXPAND, 0);
	m_panel_buttons_right->SetSizer(m_sizer_buttons_right);
	m_panel_buttons_right->SetMaxSize(wxSize(250, 500));

	// Window layout horizontal
	m_sizer_main_horizontal = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_main_horizontal->Add(m_notebook, 2, wxEXPAND | wxLEFT | wxRIGHT, 10);
	m_sizer_main_horizontal->Add(m_panel_buttons_right, 1, wxEXPAND | wxRIGHT, 10);

	// Banner
	wxImage::AddHandler(new wxPNGHandler);
	m_bitmap_banner = new wxStaticBitmap(this, wxID_ANY, wxBitmap("SDVMM2.png", wxBITMAP_TYPE_PNG)); // TODO save in code?
	wxImage::CleanUpHandlers();
	m_sizer_banner_horizontal = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_banner_horizontal->Add(m_bitmap_banner, 0, wxEXPAND, 0);
	m_sizer_banner_horizontal->AddStretchSpacer(1);

	// Bottom Bar - Version Info & Mod Count
	m_stext_smapi_version = new wxStaticText(this, wxID_ANY, "SMAPI Version: " + version_smapi_); // TODO getters/setters
	m_stext_this_version = new wxStaticText(this, wxID_ANY, "SDVMM2 Version: " + version_this_mm_);
	m_stext_mod_count = new wxStaticText(this, wxID_ANY,
		std::to_string(mod_count_["loaded"]) + "/" +
		std::to_string(mod_count_["total"]) + " Mods Loaded");
	m_sizer_mod_count = new wxBoxSizer(wxVERTICAL);
	m_sizer_mod_count->Add(m_stext_mod_count, 0, wxALIGN_RIGHT, 0);
	m_sizer_version_info = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_version_info->Add(m_stext_this_version, 10, wxEXPAND | wxLEFT, 15);
	m_sizer_version_info->Add(m_stext_smapi_version, 10, wxEXPAND | wxLEFT, 5);
	m_sizer_version_info->AddStretchSpacer(10);
	m_sizer_version_info->Add(m_sizer_mod_count, 5, wxEXPAND | wxRIGHT, 10);

	// Window layout Vertical + insert banner
	m_sizer_main_vertical = new wxBoxSizer(wxVERTICAL);
	m_sizer_main_vertical->Add(m_sizer_banner_horizontal, 0, wxEXPAND | wxALL , 10);
	m_sizer_main_vertical->Add(m_sizer_main_horizontal, 40, wxEXPAND, 0);
	m_sizer_main_vertical->Add(m_sizer_version_info, 0, wxEXPAND, 0); // for static text
	SetSizer(m_sizer_main_vertical);

	// Setting background colour as needed
	SetBackgroundColour(wxColour(240, 240, 240, wxALPHA_OPAQUE));

	SelfInitialize();
}

//-------------------
// MEMBER FUNCTIONS
//-------------------
cMain::~cMain()
{
}

void cMain::SelfInitialize()
{
	D(
		OutputDebugString(_T("SelfInit - Begin\n"));
	)
	wxFileName f(wxStandardPaths::Get().GetExecutablePath());
	fs::path appPath = string(wxString(f.GetPath() + wxT("\\SDVMM2.ini")));

	D(
		OutputDebugString(_T("SelfInit - Checking for .ini at:\n"));
		OutputDebugStringA(appPath.string().c_str());
		OutputDebugString(_T("\n"));
	)
	config_ini = new wxFileConfig(wxEmptyString,
		wxEmptyString, appPath.string());
	config_ini->SetPath("/General");

	if (fs::exists(appPath))
	{
		m_panel_notebook_tab3->SelfInitialize();
	}
	else
	{
		D(
			OutputDebugString(_T("SelfInit - No .ini Found\n"));
		)
	}
}

//-----------------------------
// Buttons and Menu Functions
//-----------------------------
// Top Level Buttons
void cMain::OnLaunchSMAPIClick(wxCommandEvent& event) // TODO Steam Launcher option
{
	event.Skip();
	if (error_check_["smapi"] == true) 
	{
		m_button_launch_smapi->Disable();
		m_button_launch_smapi->SetLabel("SMAPI Not Found!");
	}
	else
	{
		if (m_panel_notebook_tab3->launch_with_steam())
		{
			string test_str = ((this->m_panel_notebook_tab3->steam_directory().string() + "\\Steam.exe")) + " -applaunch 413150" +
				" \"" + m_panel_notebook_tab3->game_directory().string() + "//StardewValleyAPI.exe\" %command%";
			const char* open_command = (test_str.c_str());
			wxExecute(open_command, wxEXEC_ASYNC, NULL);

		}
		else
		{
			wxString temp = wxGetCwd();
			wxSetWorkingDirectory(this->m_panel_notebook_tab3->game_directory().string());
			string test_str = ((this->m_panel_notebook_tab3->game_directory().string() + "\\StardewModdingAPI"));
			const char* open_command = (test_str.c_str());
			wxExecute(open_command, wxEXEC_ASYNC, NULL);
			wxSetWorkingDirectory(temp);
		}
	}
}

void cMain::OnLaunchVanillaClick(wxCommandEvent& event) // TODO Steam Launcher option
{
	event.Skip();
	if (m_panel_notebook_tab3->launch_with_steam())
	{
		string test_str = ((m_panel_notebook_tab3->steam_directory().string() + "\\Steam.exe")) + " -applaunch 413150";
		const char* open_command = (test_str.c_str());
		wxExecute(open_command, wxEXEC_ASYNC, NULL);
		wxExecute(open_command , wxEXEC_ASYNC, NULL);
	}
	else 
	{
		wxString temp = wxGetCwd();
		wxSetWorkingDirectory(m_panel_notebook_tab3->game_directory().string());
		string test_str = ((m_panel_notebook_tab3->game_directory().string() + "\\Stardew Valley"));
		const char* open_command = (test_str.c_str());
		wxExecute(open_command, wxEXEC_ASYNC, NULL);
		wxSetWorkingDirectory(temp);
	}

}

void cMain::OnLaunchModSiteClick(wxCommandEvent& event)
{

	if (event.GetId() == ID_BUTTON_NEXUS)
	{
		wxLaunchDefaultBrowser("https://www.nexusmods.com/stardewvalley");
	}
	else if (event.GetId() == ID_BUTTON_FORUMS)
	{
		wxLaunchDefaultBrowser("https://community.playstarbound.com/forums/mods.215/");
	}
	else {}
	event.Skip();
}

void cMain::OnRefreshClick(wxCommandEvent& event) // TODO give some indication of the refresh
{
	event.Skip();
	this->RefreshModLists();
}

// Mod List Buttons
void cMain::OnToggleClick(wxDataViewEvent& event)
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
	);
	wxVariant temp_path("");
	m_dataviewlistctrl_mods->GetValue(temp_path, m_dataviewlistctrl_mods->GetSelectedRow(), 4);
	fs::path mod_path = string(temp_path);
	fs::path parent_path = mod_path.parent_path();
	fs::path folder_name = mod_path.filename();
	while (parent_path != ((m_panel_notebook_tab3->game_directory()) += "\\Mods")
		and parent_path != ((m_panel_notebook_tab3->game_directory()) += "\\Mods_disabled"))
	{

		folder_name = (parent_path.filename() += ("\\" + folder_name.string()));
		parent_path = parent_path.parent_path();
	}


	D(
		OutputDebugString(_T("Mod toggle called.\n"));
		OutputDebugStringA(parent_path.string().c_str());
		OutputDebugString(_T("\n"));
		OutputDebugStringA(folder_name.string().c_str());
		OutputDebugString(_T("\n"));
	);

	if (parent_path == ((m_panel_notebook_tab3->game_directory()) += "\\Mods"))
	{
		D(
			OutputDebugStringA(mod_path.string().c_str());
		OutputDebugString(_T("\n"));
		OutputDebugStringA((string(m_panel_notebook_tab3->game_directory().string() += "\\Mods_disabled\\") += folder_name.string()).c_str());
		OutputDebugString(_T("\n"));
		);

		// Build required parent folders for move
		while (!fs::is_directory(((m_panel_notebook_tab3->game_directory() += "\\Mods_disabled\\") += folder_name).parent_path()))
		{
			fs::path rrename_path = ((m_panel_notebook_tab3->game_directory() += "\\Mods_disabled\\") += folder_name).parent_path();
			while (!fs::is_directory(rrename_path.parent_path()))
			{
				rrename_path = rrename_path.parent_path();
			}
			fs::create_directory(rrename_path);
		}
		fs::rename(mod_path, (fs::path(m_panel_notebook_tab3->game_directory() += "\\Mods_disabled\\") += folder_name));

		// Delete empty nested folders
		fs::path clean_path = mod_path.parent_path();
		std::error_code ec;
		while (fs::is_empty(clean_path) and (clean_path != ((m_panel_notebook_tab3->game_directory()) += "\\Mods")))
		{
			fs::remove(clean_path, ec);
			D(
				OutputDebugString(_T("Empty folder deleted.\n"));
				OutputDebugStringA(clean_path.string().c_str());
				OutputDebugString(_T("\n"));
			);
			clean_path = clean_path.parent_path();
		}
	}
	else if (parent_path == ((m_panel_notebook_tab3->game_directory()) += "\\Mods_disabled"))
	{
		D(
			OutputDebugStringA(mod_path.string().c_str());
			OutputDebugString(_T("\n"));
			OutputDebugStringA((string(m_panel_notebook_tab3->game_directory().string() += "\\Mods\\") += folder_name.string()).c_str());
			OutputDebugString(_T("\n"));
		);

		// Build required parent folders for move
		while (!fs::is_directory(((m_panel_notebook_tab3->game_directory() += "\\Mods\\") += folder_name).parent_path()))
		{
			fs::path rrename_path = ((m_panel_notebook_tab3->game_directory() += "\\Mods\\") += folder_name).parent_path();
			while (!fs::is_directory(rrename_path.parent_path()))
			{
				rrename_path = rrename_path.parent_path();
			}
			fs::create_directory(rrename_path);
		}

		fs::rename(mod_path, (fs::path(m_panel_notebook_tab3->game_directory() += "\\Mods\\") += folder_name));

		// Delete empty nested folders
		fs::path clean_path = mod_path.parent_path();
		std::error_code ec;
		while (fs::is_empty(clean_path) and (clean_path != ((m_panel_notebook_tab3->game_directory()) += "\\Mods_disabled")))
		{
			fs::remove(clean_path, ec);
			D(
				OutputDebugString(_T("Empty folder deleted.\n"));
				OutputDebugStringA(clean_path.string().c_str());
				OutputDebugString(_T("\n"));
			);
			clean_path = clean_path.parent_path();
		}
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
			else {}
		);
	}
	RefreshModLists();
}

void cMain::OnSortClick(wxDataViewEvent& event)
{
	const unsigned idx = event.GetColumn();

	D(
		OutputDebugString(_T("OnSortClick Event - Col "));
		OutputDebugStringA(std::to_string(idx).c_str());
	)

	// default handling for the column click is to sort by this column or
	// toggle its sort order
	wxDataViewColumn* const col = m_dataviewlistctrl_mods->GetColumn(idx);
	if (!col->IsSortable())
	{
		D(
			OutputDebugString(_T(" - Not Sortable\n"));
		)
		// no default handling for non-sortable columns
		event.Skip();
		return;
	}

	if (col->IsSortKey())
	{
		// already acending order, just change the order
		D(
			OutputDebugString(_T(" - Old"));
		)
		col->ToggleSortOrder();
	}
	else // not using this column for sorting yet
	{
		for (int i = 0; i < 5; i++)
		{
			if (m_dataviewlistctrl_mods->GetColumn(i)->IsSortKey())
			{
				m_dataviewlistctrl_mods->GetColumn(i)->UnsetAsSortKey();
			}
		}
		col->SetSortOrder(false);
		D(
			OutputDebugString(_T(" - New"));
		)
	}

	wxDataViewModel* const model = m_dataviewlistctrl_mods->GetModel();
	if (model)
		model->Resort();

	m_dataviewlistctrl_mods->OnColumnChange(idx);
	D(
		OutputDebugString(_T(" - Sorted\n"));
	)
}

// Menu Bar Buttons
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
	else if (event.GetId() == (ID_MENU_QUIT))
	{
		OnMenuQuitClick(event);
	}
	else {}
}

void cMain::OnMenuModsClick(wxCommandEvent& event)
{
	event.Skip();
	string test_str = ("explorer " + (m_panel_notebook_tab3->game_directory().string() + "\\Mods\\"));
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
	string test_str = ("explorer " + (m_panel_notebook_tab3->game_directory().string() + "\\Mods_disabled"));
	const char* open_command = (test_str.c_str());
	wxExecute(open_command, wxEXEC_ASYNC, NULL);
}

void cMain::OnMenuQuitClick(wxCommandEvent& event)
{
	event.Skip();
	this->Close();
}

//--------------------
// Backend Functions
//--------------------
void cMain::CleanManifest(json& manifest, fs::path error_path) // TODO move check to refresh and make flag
{
	if (!manifest.contains("Name"))
	{
		error_check_["format"] = true;
		error_check_["format_local"] = true;
		error_count_["format"]++;
		string temp = "";
		if (manifest.contains("name"))
		{
			manifest["name"].get_to(temp);
			manifest["Name"] = temp;
			manifest.erase("name");
		}
		else
		{
			manifest["Name"] = temp;
		}
		D(
			OutputDebugStringA((error_path.string() + " Manifest Error - Name\n").c_str());
		)
	}
	if (!manifest.contains("Author"))
	{
		error_check_["format"] = true;
		error_check_["format_local"] = true;
		error_count_["format"]++;
		string temp = "";
		if (manifest.contains("author"))
		{
			manifest["author"].get_to(temp);
			manifest["Author"] = temp;
			manifest.erase("author");
		}
		else
		{
			manifest["Author"] = temp;
		}
		D(
			OutputDebugStringA((error_path.string() + " Manifest Error - Author\n").c_str());
		)
	}
	if (!manifest.contains("Version"))
	{
		error_check_["format"] = true;
		error_check_["format_local"] = true;
		error_count_["format"]++;
		string temp = "";
		if (manifest.contains("version"))
		{
			manifest["version"].get_to(temp);
			manifest["Version"] = temp;
			manifest.erase("version");
		}
		else
		{
			manifest["Version"] = temp;
		}
		D(
			OutputDebugStringA((error_path.string() + " Manifest Error - Version\n").c_str());
		)
	}
	else if (manifest["Version"].is_object())
	{
		// flag outdated version object and make readable
		error_check_["semvar"] = true;
		error_count_["semvar"]++;
		error_locations_ += "\n" + error_path.string() + " - Depreciated Versioning";
		string temp = "";
		int temp_v1 = NULL;
		int temp_v2 = NULL;
		int temp_v3 = NULL;
		manifest["Version"]["MajorVersion"].get_to(temp_v1);
		manifest["Version"]["MinorVersion"].get_to(temp_v2);
		manifest["Version"]["PatchVersion"].get_to(temp_v3);
		temp = std::to_string(temp_v1)
			+ "." + std::to_string(temp_v2)
			+ "." + std::to_string(temp_v3);
		manifest.erase("Version");
		manifest["Version"] = temp;
	}
	if (!manifest.contains("Description"))
	{
		error_check_["format"] = true;
		error_check_["format_local"] = true;
		error_count_["format"]++;
		string temp = "";
		if (manifest.contains("description"))
		{
			manifest["description"].get_to(temp);
			manifest["Description"] = temp;
			manifest.erase("description");
		}
		else
		{
			manifest["Description"] = temp;
		}
		D(
			OutputDebugStringA((error_path.string() + " Manifest Error - Description\n").c_str());
		)
	}
	if (!manifest.contains("UniqueID"))
	{
		error_check_["format"] = true;
		error_check_["format_local"] = true;
		error_count_["format"]++;
		string temp = "";
		if (manifest.contains("uniqueID"))
		{
			// if bad case, fix case (more work needed)
		}
		else
		{
			manifest["UniqueID"] = temp;
		}
		D(
			OutputDebugStringA((error_path.string() + " Manifest Error - UniqueID\n").c_str());
		)
	}
	if (error_check_["format_local"] == true)
	{
		mod_count_["errored"]++;
		error_locations_ += "\n" + error_path.string() + " - Manifest Formatting";
	}
}

void cMain::RefreshModLists()
{
	ResetRefreshErrors();
	wxWindowUpdateLocker noUpdates(m_dataviewlistctrl_mods);
	m_dataviewlistctrl_mods->DeleteAllItems();
	try { LoadModsFromDir("\\Mods\\"); }
	catch (...) {
		wxMessageDialog* error_load_mods = new wxMessageDialog(NULL,
			wxT("Fatal error attempting to refresh active mods."),
			wxT("Refresh Error"), wxOK, wxDefaultPosition);
		error_load_mods->ShowModal();
		delete error_load_mods;
	}
	try { LoadModsFromDir("\\Mods_disabled\\"); }
	catch (...) {
		wxMessageDialog* error_load_modsd = new wxMessageDialog(NULL,
			wxT("Fatal error attempting to refresh inactive mods."),
			wxT("Refresh Error"), wxOK, wxDefaultPosition);
		error_load_modsd->ShowModal();
		delete error_load_modsd;
	}
	m_dataviewlistctrl_mods->GetModel()->Resort();
	// Pull out this from the main contructor
	string temp_mod = std::to_string(mod_count_["loaded"]) + "/" +
		std::to_string(mod_count_["total"]) + " Mods Successfully Loaded";
	m_stext_mod_count->SetLabel(temp_mod);
	ShowRefreshErrors();
}

void cMain::LoadModsFromDir(string folder_name) 
{
	// TODO group and report errors in scrollable dialogue (bad jsons, incompatible mods, etc.)
	// TODO replace custom ioFunctions with filesystem?
	fs::path temp_dir = (m_panel_notebook_tab3->game_directory());
	temp_dir += folder_name;
	fs::path temp_path;
	fs::path error_path;
	bool is_active = (folder_name == "\\Mods\\");
	int error_json = 0; // 0 = no error, 1 = bad comma, 2 = other

	D(
		OutputDebugString(_T("LoadModsFromDir - Begin Iterator at:\n"));
		OutputDebugStringA(m_panel_notebook_tab3->game_directory().string().c_str());
		OutputDebugString(_T("\n"));
	)
	for (auto& dir_iter : fs::recursive_directory_iterator(temp_dir))
	{
		error_check_["json"] = false;
		error_check_["format_local"] = false;
		error_path = dir_iter.path().filename();
		temp_path = dir_iter.path();
		D(
			OutputDebugStringA(temp_path.string().c_str());
		)
		if (fs::is_directory(temp_path))
		{
			D(
				OutputDebugString(_T(" - Is Directory\n"));
			)
			mod_count_["total"]++;
			temp_path += "\\manifest.json";
			if (fs::exists(temp_path))
			{
				ifstream json_stream(temp_path.c_str());
				json json_manifest;
				try
				{
					try
					{ // Parse json
						json_manifest = json::parse(json_stream); // TODO handle trailing commas
						// Handle some minor typos and missing fields in manifest
						CleanManifest(json_manifest, error_path);
					}
					catch (json::parse_error & e)
					{ // On fail, output error and skip to next mod
						error_check_["json"] = true;
						error_count_["json"]++;
						mod_count_["errored"]++;
						string temp_exc = e.what();
						if (e.id == 101) {
							error_locations_ += "\n" + error_path.string() + " - JSON Unexpected Char";
							// TODO clean commas and comments, then try again
							///*
							D(
								OutputDebugString(_T("Json Fix Attempt\n"));
							)
								//std::stringstream json_sstream;
								//json_sstream << json_stream.rdbuf();
								string json_string = "New\n";
							//json_string = json_sstream.str();
							ifstream json_stream2(temp_path.c_str(), std::ios::in | std::ios::binary);
							json_stream2.seekg(0, std::ios::end);
							json_string.resize(json_stream2.tellg());
							json_stream2.seekg(0, std::ios::beg);
							json_stream2.read(&json_string[0], json_string.size());
							json_stream2.close();

							D(
								OutputDebugString(_T("Json Fix RAW\n"));
							OutputDebugStringA(json_string.c_str());
							OutputDebugString(_T("\n"));
							)

								try
							{
								json_string = stripComments(json_string, true);
							}
							catch (...)
							{
								D(
									OutputDebugString(_T("Json Fix Comment Clean Failure\n"));
								)
							}

							D(
								OutputDebugString(_T("Json Fix Comment Cleaned\n"));
							OutputDebugStringA(json_string.c_str());
							OutputDebugString(_T("\n"));
							)

								try
							{
								json_string = stripTrailingCommas(json_string, true);
							}
							catch (const std::regex_error & e)
							{
								string temp = e.what();
								D(
									OutputDebugString(_T("Json Fix Comma Clean Failure: " + temp + "\n"));
								)
							}
							//json_sstream.clear();
							//json_sstream.str(string());
							//json_sstream << json_string;

							D(
								OutputDebugString(_T("Json Fix Comma Cleaned\n"));
							OutputDebugStringA(json_string.c_str());
							OutputDebugString(_T("\n"));
							)

								try
							{
								json_manifest = json::parse(json_string); // TODO handle trailing commas
								// Handle some minor typos and missing fields in manifest
								CleanManifest(json_manifest, error_path);
								error_check_["json"] = false;
								D(
									OutputDebugString(_T("Json Fix Reparse Success\n"));
								)
							}
							catch (...)
							{
								D(
									OutputDebugString(_T("Json Fix Reparse Failure\n"));
								)
									continue;
							}
							//*/
						}
						else {
							error_locations_ += "\n" + error_path.string() + " - JSON Formatting";
							continue;
						}
					}

					if (fs::exists(temp_path) and (error_check_["json"] == false)) // TODO Review
					{
						D(
							if (report_parsed_mod_data) {
								string temp_msg1 = "";
								string temp_msg2 = "";
								json_manifest["Name"].get_to(temp_msg1);
								json_manifest["Version"].get_to(temp_msg2);
								OutputDebugStringA((temp_msg1 + " exists, " + temp_msg2 + "\n").c_str());
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
						mod_count_["loaded"]++;
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
								OutputDebugStringA((aMod.infoString()).c_str());
							}
							else {}
						)
					}
				}
				catch (...)
				{
					error_locations_ += "\n" + error_path.string() + " - Fatal";
				}
			}
		}
		else 
		{
		D(
			OutputDebugString(_T(" - Is NOT Directory\n"));
		)
		}
	}
}

bool cMain::ExistsModFolders()
{
	fs::path mod_path = m_panel_notebook_tab3->game_directory();
	fs::path mod_d_path = m_panel_notebook_tab3->game_directory();
	fs::path game_file_path = m_panel_notebook_tab3->game_directory();
	mod_path += "\\Mods";
	mod_d_path += "\\Mods_disabled";
	game_file_path += "\\Stardew Valley.exe"; // TODO Make crossplatform?

	D(
		OutputDebugString(_T("ExistsModFolders - Begin Checking Mod Folders\n"));
	)

	if (!(fs::exists(game_file_path) and fs::is_regular_file(game_file_path)))
	{
		D(
			OutputDebugString(_T("ExistsModFolders - Game Executable not Found on Path:\n"));
			OutputDebugStringA(game_file_path.string().c_str());
			OutputDebugString(_T("\n"));
			OutputDebugString(_T("ExistsModFolders - Bad Game Directory\n"));
		)
			return false;
	}
	else
	{
		if (!(fs::exists(mod_path) and fs::is_directory(mod_path)))
		{
			D(
				OutputDebugString(_T("ExistsModFolders - Mods Folder not Found\n"));
			)
			fs::create_directory(mod_path);
			D(
				OutputDebugString(_T("ExistsModFolders - Mods Folder Created at:\n"));
				OutputDebugStringA(mod_path.string().c_str());
				OutputDebugString(_T("\n"));
			)
		}
		else
		{
			D(
				OutputDebugString(_T("ExistsModFolders - Mods Directory Found on Path:\n"));
				OutputDebugStringA(mod_path.string().c_str());
				OutputDebugString(_T("\n"));
			)
		}
		if (!(fs::exists(mod_d_path) and fs::is_directory(mod_d_path)))
		{
			D(
				OutputDebugString(_T("ExistsModFolders - Mods_disabled Folder not Found\n"));
			)
			fs::create_directory(mod_d_path);
			D(
				OutputDebugString(_T("ExistsModFolders - Mods_disabled Folder Created at:\n"));
				OutputDebugStringA(mod_d_path.string().c_str());
				OutputDebugString(_T("\n"));
			)
		}
		else
		{
			D(
				OutputDebugString(_T("ExistsModFolders - Mods Directory Found on Path:\n"));
				OutputDebugStringA(mod_d_path.string().c_str());
				OutputDebugString(_T("\n"));
			)
		}
	}
	return true;
}

void cMain::CheckSmapiVersion()
{
	string version = "";
	fs::path path_smapi_logs = string(wxStandardPaths::Get().GetUserConfigDir());
	path_smapi_logs += "\\StardewValley\\ErrorLogs\\SMAPI-latest.txt";
	if (fs::exists(path_smapi_logs) and fs::is_regular_file(path_smapi_logs))
	{
		D(
			OutputDebugString(_T("CheckSmapiVersion - Logs Found\n"));
		)
		wxTextFile smapi_logs;
		smapi_logs.Open(wxString(path_smapi_logs));
		wxString temp_string = smapi_logs.GetFirstLine();
		size_t temp_version_start = temp_string.Find("] ") + 8;
		size_t temp_version_end = temp_string.Find(" with Stardew") - 1;
		version = temp_string.SubString(temp_version_start, temp_version_end);
		D(
			OutputDebugString(_T("CheckSmapiVersion - Version: "));
			OutputDebugStringA(version.c_str());
			OutputDebugString(_T("\n"));
		)
	}
	else
	{
		D(
			OutputDebugString(_T("CheckSmapiVersion - No Logs Found to Scrape\n"));
		)
		version = "not found";
	}
	m_stext_smapi_version->SetLabel("SMAPI Version: " + version);
}

void cMain::ResetRefreshErrors() 
{
	error_locations_ = "Errors at: ";
	error_check_["json"] = false;
	error_check_["semvar"] = false;
	error_check_["format"] = false;
	error_check_["format_local"] = false;
	error_count_["json"] = 0;
	error_count_["semvar"] = 0;
	error_count_["format"] = 0;
	mod_count_["total"] = 0;
	mod_count_["errored"] = 0;
	mod_count_["loaded"] = 0;
}

void cMain::ShowRefreshErrors()
{
	if ((error_mute_["on_refresh"] == false) and 
		((error_count_["json"] != 0) or (error_count_["semvar"] != 0) or (error_count_["format"] != 0)))
	{
		// Error counter dialogue prep
		string error_mod_loop_title = "Errors in Mods";
		string error_mod_loop_message =
			("Manifests with incorrect .json format: " + std::to_string(error_count_["json"]) +
				"\nManifests with depreciated versioning: " + std::to_string(error_count_["semvar"]) +
				"\nManifests with other formatting errors: " + std::to_string(error_count_["format"]));
		// if (!is_active) { final_error_title += "_disabled"; };
		// Error counter dialogue
		wxMessageDialog* error_mod_loop = new wxMessageDialog(NULL,
			error_mod_loop_message, error_mod_loop_title, wxOK, wxDefaultPosition);
		error_mod_loop->ShowModal();
		delete error_mod_loop;
		if (error_check_["semvar"]) 
		{
			error_locations_ += "\n[SMAPI does not load mods with depreciated versioning.]";
		}
		wxMessageDialog* error_mod_loop_detailed = new wxMessageDialog(NULL,
			error_locations_, error_mod_loop_title, wxOK, wxDefaultPosition);
		error_mod_loop_detailed->ShowModal();
		delete error_mod_loop_detailed;
	}
}
