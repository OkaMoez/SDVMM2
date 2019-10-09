#include "cApp.h"

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Stardew Valley Mod Manager 2",
	wxDefaultPosition, wxSize(750,500),
	wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	//---------------------------
	//  Notebook Implementation
	//---------------------------
	// Tab 1, 2, 3 = Active/Inactive Mods, XNB Mods, Settings
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
	m_sizer_notebook_tab1a_mods->AddSpacer(6);

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
	m_panel_notebook_tab3 = new wxPanel(m_notebook, wxID_ANY);

	// Tab 3 - Launcher Sizer
	m_stext_launcher = new wxStaticText(m_panel_notebook_tab3, wxID_ANY, "Launch w/ Steam: ");
	m_checkbox_launcher = new wxCheckBox(m_panel_notebook_tab3, wxID_ANY, "(uncheck if you have the GOG version)");
	m_checkbox_launcher->Bind(wxEVT_CHECKBOX, &cMain::OnLauncherToggleClick, this);
	m_sizer_notebook_tab3_launcher = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_notebook_tab3_launcher->Add(m_stext_launcher, 2, wxALIGN_CENTER_VERTICAL, 0);
	m_sizer_notebook_tab3_launcher->Add(m_checkbox_launcher, 7, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 0);


	// Tab 3 - Game Directory Sizer
	m_stext_game_directory = new wxStaticText(m_panel_notebook_tab3, wxID_ANY, "Game Folder: ");
	m_textctrl_game_directory = new wxTextCtrl(m_panel_notebook_tab3, wxID_ANY, "game directory not found");
	m_button_game_directory_save = new wxButton(m_panel_notebook_tab3, wxID_ANY, "Save", wxDefaultPosition, wxSize(60, 25));
	m_button_game_directory_browse = new wxButton(m_panel_notebook_tab3, wxID_ANY, "Browse", wxDefaultPosition, wxSize(60, 25));
	m_button_game_directory_save->Bind(wxEVT_BUTTON, &cMain::OnGameDirectorySaveClick, this);
	m_button_game_directory_browse->Bind(wxEVT_BUTTON, &cMain::OnGameDirectoryBrowseClick, this);
	m_dirdialog_game_browse = new wxDirDialog(this, "Select your 'Stardew Valley' game directory",
		wxEmptyString, wxDD_DIR_MUST_EXIST);
	m_sizer_notebook_tab3_game_directory = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_notebook_tab3_game_directory->Add(m_stext_game_directory, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
	m_sizer_notebook_tab3_game_directory->Add(m_textctrl_game_directory, 4, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	m_sizer_notebook_tab3_game_directory->Add(m_button_game_directory_save, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	m_sizer_notebook_tab3_game_directory->Add(m_button_game_directory_browse, 1, wxALIGN_CENTER_VERTICAL, 0);

	// Tab 3 - Steam Directory Sizer
	m_stext_steam_directory = new wxStaticText(m_panel_notebook_tab3, wxID_ANY, "Steam Folder: ");
	m_textctrl_steam_directory = new wxTextCtrl(m_panel_notebook_tab3, wxID_ANY, "steam directory not found");
	m_button_steam_directory_save = new wxButton(m_panel_notebook_tab3, wxID_ANY, "Save", wxDefaultPosition, wxSize(60, 25));
	m_button_steam_directory_browse = new wxButton(m_panel_notebook_tab3, wxID_ANY, "Browse", wxDefaultPosition, wxSize(60, 25));
	m_button_steam_directory_save->Bind(wxEVT_BUTTON, &cMain::OnSteamDirectorySaveClick, this);
	m_button_steam_directory_browse->Bind(wxEVT_BUTTON, &cMain::OnSteamDirectoryBrowseClick, this);
	m_filedialog_steam_browse = new wxFileDialog(this, "Select the Steam executable/application file (Steam.exe)",
		wxEmptyString, "Steam.exe", wxFileSelectorDefaultWildcardStr, wxFD_FILE_MUST_EXIST);
	m_sizer_notebook_tab3_steam_directory = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_notebook_tab3_steam_directory->Add(m_stext_steam_directory, 0, wxALIGN_CENTER_VERTICAL, 0);
	m_sizer_notebook_tab3_steam_directory->Add(m_textctrl_steam_directory, 4, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	m_sizer_notebook_tab3_steam_directory->Add(m_button_steam_directory_save, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	m_sizer_notebook_tab3_steam_directory->Add(m_button_steam_directory_browse, 1, wxALIGN_CENTER_VERTICAL, 0);

	// Tab 3 - Vertical Sizer // TODO change layout
	m_sizer_notebook_tab3_items = new wxBoxSizer(wxVERTICAL);
	m_sizer_notebook_tab3_items->Add(m_sizer_notebook_tab3_launcher, 1, wxEXPAND, 0);
	m_sizer_notebook_tab3_items->AddStretchSpacer(0);
	m_sizer_notebook_tab3_items->Add(m_sizer_notebook_tab3_game_directory, 1, wxEXPAND, 0);
	m_sizer_notebook_tab3_items->Add(m_sizer_notebook_tab3_steam_directory, 1, wxEXPAND, 0);
	m_sizer_notebook_tab3_items->AddStretchSpacer(4);

	// Tab 3 - Dummy Sizers for Margins
	m_sizer_notebook_tab3_left = new wxBoxSizer(wxVERTICAL);
	m_sizer_notebook_tab3_left->Add(m_sizer_notebook_tab3_items, 1, wxEXPAND | wxLEFT, 7);
	m_sizer_notebook_tab3_right = new wxBoxSizer(wxVERTICAL);
	m_sizer_notebook_tab3_right->Add(m_sizer_notebook_tab3_left, 1, wxEXPAND | wxRIGHT, 9);
	m_sizer_notebook_tab3 = new wxBoxSizer(wxVERTICAL);
	m_sizer_notebook_tab3->AddSpacer(10);
	m_sizer_notebook_tab3->Add(m_sizer_notebook_tab3_right, 1, wxEXPAND, 0);
	m_sizer_notebook_tab3->AddSpacer(10);
	m_panel_notebook_tab3->SetSizer(m_sizer_notebook_tab3);

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
	ID_MENU_MODS = wxNewId();
	ID_MENU_DMODS = wxNewId();
	ID_MENU_QUIT = wxNewId();
	m_menubar->Append(m_menubar_file, wxT("&File"));
	m_menubar_file->Append(ID_MENU_MODS, wxT("&Open Mods Folder"), wxEmptyString, wxITEM_NORMAL);
	m_menubar_file->Append(ID_MENU_DMODS, wxT("&Open Disabled Mods Folder"), wxEmptyString, wxITEM_NORMAL);
	m_menubar_file->Append(ID_MENU_QUIT, wxT("&Quit"), wxEmptyString, wxITEM_NORMAL);
	//m_menubar->Append(m_menubar_help, wxT("&Help")); // REMOVED FOR 0.5.0-ALPHA RELEASE
	SetMenuBar(m_menubar);
	this->Bind(wxEVT_MENU, &cMain::OnMenuClick, this, ID_MENU_MODS, ID_MENU_QUIT);

	// Right side buttons
	ID_BUTTON_NEXUS = wxNewId();
	ID_BUTTON_FORUMS = wxNewId();
	m_button_launch_smapi = new wxButton(this, wxID_ANY, "Launch SMAPI with Mods");
	m_button_launch_vanilla = new wxButton(this, wxID_ANY, "Launch Stardew Valley");
	m_button_add_mod = new wxButton(this, wxID_ANY, ""); // TODO "Add Mod from File/Archive" // REMOVED FOR 0.5.0-ALPHA RELEASE
	m_button_nexus_download = new wxButton(this, ID_BUTTON_NEXUS, "Visit Nexus Mods");
	m_button_forums_download = new wxButton(this, ID_BUTTON_FORUMS, "Visit Mod Forums");
	m_button_refresh_mods = new wxButton(this, wxID_ANY, "Refresh Mod List");
	m_button_launch_smapi->Bind(wxEVT_BUTTON, &cMain::OnLaunchSMAPIClick, this);
	m_button_launch_vanilla->Bind(wxEVT_BUTTON, &cMain::OnLaunchVanillaClick, this);
	m_button_nexus_download->Bind(wxEVT_BUTTON, &cMain::OnLaunchModSiteClick, this);
	m_button_forums_download->Bind(wxEVT_BUTTON, &cMain::OnLaunchModSiteClick, this);
	m_button_refresh_mods->Bind(wxEVT_BUTTON, &cMain::OnRefreshClick, this);

	// Right side button - sizer
	int prop_rBtns = 10;
	int prop_rSpace = 1;
	m_sizer_buttons_right = new wxBoxSizer(wxVERTICAL);
	m_sizer_buttons_right->Add(m_button_launch_smapi, prop_rBtns, wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(prop_rSpace);
	m_sizer_buttons_right->Add(m_button_launch_vanilla, prop_rBtns, wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(prop_rSpace);
	m_sizer_buttons_right->Add(m_button_add_mod, (prop_rBtns/2), wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(prop_rSpace);
	m_sizer_buttons_right->Add(m_button_nexus_download, (prop_rBtns/2), wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(prop_rSpace);
	m_sizer_buttons_right->Add(m_button_forums_download, (prop_rBtns/2), wxEXPAND, 0);
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
	m_stext_smapi_version = new wxStaticText(this, wxID_ANY, "SMAPI Version: " + version_smapi_); // TODO getters/setters
	m_stext_this_version = new wxStaticText(this, wxID_ANY, "SDVMM2 Version: " + version_this_mm_);
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
	m_panel_notebook_tab1->SetBackgroundColour(wxColour(*wxWHITE));
	m_stext_smapi_version->SetBackgroundColour(wxColour(*m_colour_grey));
	m_stext_this_version->SetBackgroundColour(wxColour(*m_colour_grey));
	delete m_colour_grey;

	SelfInitialize();
}



//-------------------
// MEMBER FUNCTIONS
//-------------------
cMain::~cMain()
{
	delete m_dirdialog_game_browse;
	delete m_filedialog_steam_browse;
	delete config_ini;
}

void cMain::SelfInitialize()
{
	D(
		OutputDebugString(_T("SelfInit - Begin\n"));
	)
	wxFileName f(wxStandardPaths::Get().GetExecutablePath());
	wxString appPath = (f.GetPath() + wxT("\\SDVMM2.ini"));
	D(
		OutputDebugString(_T("SelfInit - Checking for .ini at:\n"));
		OutputDebugStringA(appPath + "\n");
	)
	config_ini = new wxFileConfig(wxEmptyString,
		wxEmptyString, appPath);
	config_ini->SetPath("/General");

	if (existsFile(string(appPath)))
	{
		ini_exists_ = true;
		D(
			OutputDebugString(_T("SelfInit - .ini Exists\n"));
		)
		D(
			OutputDebugString(_T("SelfInit - Open .ini\n"));
		)
		set_game_directory(string(config_ini->Read(wxT("GamePath"), "directory not found")));
		D(
			OutputDebugString(_T("SelfInit - .ini Game Path Read\n"));
		)
		set_launch_with_steam(config_ini->ReadBool("SteamLauncher", true));
		D(
			OutputDebugString(_T("SelfInit - .ini Launcher Preference Read\n"));
		)
		set_steam_directory(string(config_ini->Read(wxT("SteamPath"), "directory not found")));
		D(
			OutputDebugString(_T("SelfInit - .ini Steam Path Read\n"));
		)

		if (ExistsModFolders())
		{
			D(
				OutputDebugString(_T("SelfInit - Refreshing Mod List\n"));
			)
			RefreshModLists();
			D(
				OutputDebugString(_T("Refreshed Mod List\n"));
			)
		}
		else
		{
			D(
				OutputDebugString(_T("SelfInit - No Mod Folders Found\n"));
			)
		}
		D(
			OutputDebugString(_T("SelfInit - Game Directory\n"));
			OutputDebugStringA(game_directory().string().c_str());
			OutputDebugString(_T("\n"));
			OutputDebugString(_T("SelfInit - Checking SMAPI Version\n"));
		)
			CheckSmapiVersion();
		D(
			OutputDebugString(_T("SelfInit - Checked SMAPI Version\n"));
		)
	}
	else
	{
		D(
			OutputDebugString(_T("SelfInit - No .ini Found\n"));
		)
	}
}

//----------
// Setters
//----------
void cMain::set_launch_with_steam(bool state)
{
	m_checkbox_launcher->SetValue(state);
	launch_with_steam_ = state;
}

void cMain::set_game_directory(fs::path filepath)
{
	m_textctrl_game_directory->SetLabel(filepath.string());
	game_directory_ = filepath;
	if (!fs::exists(string(m_textctrl_game_directory->GetLineText(0)) + "\\Mods"))
	{
		fs::create_directory(string(m_textctrl_game_directory->GetLineText(0)) + "\\Mods");
	}
	if (!fs::exists(string(m_textctrl_game_directory->GetLineText(0)) + "\\Mods_disabled"))
	{
		fs::create_directory(string(m_textctrl_game_directory->GetLineText(0)) + "\\Mods_disabled");
	}
}

void cMain::set_steam_directory(fs::path filepath)
{
	m_textctrl_steam_directory->SetLabel(filepath.string());
	steam_directory_ = filepath;
}

void cMain::set_version_this_mm(string version)
{
	version_this_mm_ = version;
}


//-----------------------------
// Buttons and Menu Functions
//-----------------------------
// Top Level Buttons
void cMain::OnLaunchSMAPIClick(wxCommandEvent& event) // TODO Steam Launcher option
{
	event.Skip();
	if (launch_with_steam())
	{
		string test_str = ((this->steam_directory().string() + "\\Steam.exe")) + " -applaunch 413150" +
			" \"" + game_directory().string() + "//StardewValleyAPI.exe\" %command%";
		const char* open_command = (test_str.c_str());
		wxExecute(open_command, wxEXEC_ASYNC, NULL);

	}
	else
	{
		string test_str = ((this->game_directory().string() + "\\StardewModdingAPI"));
		const char* open_command = (test_str.c_str());
		wxExecute(open_command, wxEXEC_ASYNC, NULL);
	}
}

void cMain::OnLaunchVanillaClick(wxCommandEvent& event) // TODO Steam Launcher option
{
	event.Skip();
	if (launch_with_steam())
	{
		string test_str = ((this->steam_directory().string() + "\\Steam.exe")) + " -applaunch 413150";
		const char* open_command = (test_str.c_str());
		wxExecute(open_command, wxEXEC_ASYNC, NULL);
		wxExecute(open_command , wxEXEC_ASYNC, NULL);
	}
	else 
	{
		string test_str = ((this->game_directory().string() + "\\Stardew Valley"));
		const char* open_command = (test_str.c_str());
		wxExecute(open_command, wxEXEC_ASYNC, NULL);
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
	string test_str = ("explorer " + (this->game_directory().string() + "\\Mods\\"));
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
	string test_str = ("explorer " + (this->game_directory().string() + "\\Mods_disabled"));
	const char* open_command = (test_str.c_str());
	wxExecute(open_command, wxEXEC_ASYNC, NULL);
}

void cMain::OnMenuQuitClick(wxCommandEvent& event)
{
	event.Skip();
	this->Close();
}

// Settings Buttons
void cMain::OnLauncherToggleClick(wxCommandEvent& event)
{
	event.Skip();
	if (fs::exists(string(m_textctrl_steam_directory->GetLineText(0)) + "\\Steam.exe"))
	{
		set_launch_with_steam(m_checkbox_launcher->GetValue());
		config_ini->Write("SteamLauncher", m_checkbox_launcher->GetValue());
		config_ini->Flush();
	}
	else
	{
		set_launch_with_steam(false);
		wxMessageDialog* event_launcher_toggle_box1 = new wxMessageDialog(NULL,
			wxT("No Steam files found. \nPlease save the Steam path below and retry."), 
			wxT("Launcher Option"),	wxOK, wxDefaultPosition);
		event_launcher_toggle_box1->ShowModal();
		delete event_launcher_toggle_box1;
	}
	if (launch_with_steam())
	{
		D(
			if (report_launcher_cbox_event) {
				wxMessageDialog* event_launcher_toggle_box1 = new wxMessageDialog(NULL,
					wxT("Launcher toggled on."), wxT("Launcher Option"),
					wxOK, wxDefaultPosition);
				event_launcher_toggle_box1->ShowModal();
				delete event_launcher_toggle_box1;
			}
			else {}
		)
	}
}

void cMain::OnGameDirectorySaveClick(wxCommandEvent& event)
{
	event.Skip();
	if (fs::exists(string(m_textctrl_game_directory->GetLineText(0)) + "\\Stardew Valley.exe"))
	{
		set_game_directory(string(m_textctrl_game_directory->GetLineText(0)));
		config_ini->Write("GamePath", wxString(game_directory().string()));
		config_ini->Flush();
		RefreshModLists();
	}
	else
	{
		wxMessageDialog* event_bad_game_directory = new wxMessageDialog(NULL,
			wxT("Game files not found in: " + string(m_textctrl_game_directory->GetLineText(0))),
			wxT("Game Directory"), wxOK, wxDefaultPosition);
		event_bad_game_directory->ShowModal();
		delete event_bad_game_directory;
	}
}

void cMain::OnGameDirectoryBrowseClick(wxCommandEvent& event)
{
	event.Skip();
	if (m_dirdialog_game_browse->ShowModal() == wxID_OK)
	{
		if (fs::exists(string(m_dirdialog_game_browse->GetPath()) + "\\Stardew Valley.exe"))
		{
			m_dirdialog_game_browse->SetPath(m_dirdialog_game_browse->GetPath());
			set_game_directory(string(m_dirdialog_game_browse->GetPath()));
			config_ini->Write("GamePath", wxString(game_directory().string()));
			config_ini->Flush();
			RefreshModLists();
		}
		else
		{
			m_dirdialog_game_browse->SetPath(m_dirdialog_game_browse->GetPath());
			wxMessageDialog* game_directory_browse_fail = new wxMessageDialog(NULL,
				("Game executable not found in directory:\n" + string(m_dirdialog_game_browse->GetPath())),
				wxT("Incorrect Directory"), wxOK, wxDefaultPosition);
			game_directory_browse_fail->ShowModal();
			delete game_directory_browse_fail;
		}
	}
	else {}
}

void cMain::OnSteamDirectorySaveClick(wxCommandEvent& event)
{
	event.Skip();
	if (fs::exists(string(m_textctrl_steam_directory->GetLineText(0)) + "\\Steam.exe"))
	{
		set_steam_directory(string(m_textctrl_steam_directory->GetLineText(0)));
		config_ini->Write("SteamPath", wxString(steam_directory().string()));
		config_ini->Flush();
	}
	else
	{
		wxMessageDialog* event_bad_steam_directory = new wxMessageDialog(NULL,
			wxT("Steam files not found in: " + string(m_textctrl_steam_directory->GetLineText(0))),
			wxT("Steam Directory"), wxOK, wxDefaultPosition);
		event_bad_steam_directory->ShowModal();
		delete event_bad_steam_directory;
	}
}

void cMain::OnSteamDirectoryBrowseClick(wxCommandEvent& event)
{
	event.Skip();
	if ((m_filedialog_steam_browse->ShowModal() == wxID_OK))
	{
		if ((fs::exists(string(m_filedialog_steam_browse->GetPath()))) and
			(fs::path(string((m_filedialog_steam_browse->GetPath()))).filename() == fs::path("Steam.exe")))
		{
			m_filedialog_steam_browse->SetPath(m_filedialog_steam_browse->GetPath());
			set_steam_directory((fs::path(string(m_filedialog_steam_browse->GetPath())).parent_path()).string());
			config_ini->Write("SteamPath", wxString(steam_directory().string()));
			config_ini->Flush();
		}
		else
		{
			m_filedialog_steam_browse->SetPath(m_filedialog_steam_browse->GetPath());
			wxMessageDialog* steam_directory_browse_fail = new wxMessageDialog(NULL,
				("Steam executable not found:\n" + string(m_filedialog_steam_browse->GetPath())),
				wxT("Incorrect Directory"), wxOK, wxDefaultPosition);
			steam_directory_browse_fail->ShowModal();
			delete steam_directory_browse_fail;
		}
	}
	else {}
}

//--------------------
// Backend Functions
//--------------------
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

	if (parent_path == ((this->game_directory()) += "\\Mods"))
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

		fs::copy(mod_path, (fs::path(this->game_directory() += "\\Mods_disabled\\") += folder_name));
		fs::remove_all(mod_path);

	}
	else if (parent_path == ((this->game_directory()) += "\\Mods_disabled"))
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

			fs::copy(mod_path, (fs::path(this->game_directory() += "\\Mods\\") += folder_name));
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

void cMain::FormatOldVersion(json& manifest) // TODO move check to refresh and make flag
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

void cMain::LoadModsFromDir(string folder_name) 
{
	// TODO group and report errors in scrollable dialogue (bad jsons, incompatible mods, etc.)
	// TODO replace custom ioFunctions with filesystem?
	json json_manifest;
	bool is_active = (folder_name == "\\Mods\\");
	bool is_good_json = false;
	bool is_using_semvar = true;
	fs::path temp_dir = (this->game_directory());
	temp_dir += folder_name;
	fs::path temp_path;
	D(
		OutputDebugString(_T("LoadModsFromDir - Begin Iterator at:\n"));
		OutputDebugStringA(game_directory().string().c_str());
		OutputDebugString(_T("\n"));
	)
	for (auto& dir_iter : fs::directory_iterator(temp_dir))
	{
		is_good_json = false;
		temp_path = dir_iter.path();
		D(
			OutputDebugStringA(temp_path.string().c_str());
		)
		if (fs::is_directory(temp_path))
		{
		D(
			OutputDebugString(_T(" - Is Directory\n"));
		)
			temp_path += "\\manifest.json";

				int json_problem = NULL;
			ifstream json_stream(temp_path.c_str());
			try {
				json_manifest = json::parse(json_stream); // TODO handle trailing commas
				is_good_json = true;
			}
			catch (json::parse_error& e) {
				is_good_json = false;
				string temp_exc = e.what();

				if (e.id == 101) {
					json_problem = 1;
					// TODO clean commas and try again
				}
				else {
					json_problem = 2;
				}
			}

			// Check for required manifest.json fields and edit as needed
			// TODO 
			if (!json_manifest.contains("Name"))
			{
				string temp = "";
				if (json_manifest.contains("name"))
				{
					json_manifest["name"].get_to(temp);
					json_manifest["Name"] = temp;
					json_manifest.erase("name");
				}
				else
				{
					json_manifest["Name"] = temp;
				}

			}
			if (!json_manifest.contains("Author"))
			{
				string temp = "";
				if (json_manifest.contains("author"))
				{
					json_manifest["author"].get_to(temp);
					json_manifest["Author"] = temp;
					json_manifest.erase("author");
				}
				else
				{
					json_manifest["Author"] = temp;
				}
			}
			if (!json_manifest.contains("Version"))
			{
				string temp = "";
				if (json_manifest.contains("version"))
				{
					json_manifest["version"].get_to(temp);
					json_manifest["Version"] = temp;
					json_manifest.erase("version");
				}
				else
				{
					json_manifest["Version"] = temp;
				}
			}
			else if (json_manifest["Version"].is_object())
			{
				// flag outdated version object and make readable
				string temp = "";
				is_using_semvar = false;
				int temp_v1 = NULL;
				int temp_v2 = NULL;
				int temp_v3 = NULL;
				json_manifest["Version"]["MajorVersion"].get_to(temp_v1);
				json_manifest["Version"]["MinorVersion"].get_to(temp_v2);
				json_manifest["Version"]["PatchVersion"].get_to(temp_v3);
				temp = std::to_string(temp_v1)
					+ "." + std::to_string(temp_v2)
					+ "." + std::to_string(temp_v3);
				json_manifest.erase("Version");
				json_manifest["Version"] = temp;
			}
			if (!json_manifest.contains("Description"))
			{
				string temp = "";
				if (json_manifest.contains("description"))
				{
					json_manifest["description"].get_to(temp);
					json_manifest["Description"] = temp;
					json_manifest.erase("description");
				}
				else
				{
					json_manifest["Description"] = temp;
				}
			}
			if (!json_manifest.contains("UniqueID"))
			{
				string temp = "";
				if (json_manifest.contains("uniqueID"))
				{
					// if bad case, fix case (more work needed)
				}
				else
				{
					json_manifest["UniqueID"] = temp;
				}
			}

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
						wxT("Bad JSON Format: Illegal trailing comma at:\n" + temp_path.string()),
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
	fs::path mod_path = this->game_directory();
	fs::path mod_d_path = this->game_directory();
	fs::path game_file_path = this->game_directory();
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