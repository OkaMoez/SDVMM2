#include "SettingsPanel.h"

#include "cMain.h"
#include "ModBrowserPanel.h"

SettingsPanel::SettingsPanel(wxWindow* parent, wxWindowID windowID, cMain* parentWindow)
	: wxPanel(parent, windowID)
	, mainWindow(parentWindow)
{
	// Tab 3 - Launcher Sizer
	m_stext_launcher = new wxStaticText(this, wxID_ANY, "Launch w/ Steam: ");
	m_checkbox_launcher = new wxCheckBox(this, wxID_ANY, "  (uncheck if you have the GOG version)");
	m_checkbox_launcher->Bind(wxEVT_CHECKBOX, &SettingsPanel::OnLauncherToggleClick, this);
	m_sizer_notebook_tab3_launcher = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_notebook_tab3_launcher->Add(m_stext_launcher, 0, wxALIGN_CENTER_VERTICAL, 0);
	m_sizer_notebook_tab3_launcher->AddSpacer(20);
	m_sizer_notebook_tab3_launcher->Add(m_checkbox_launcher, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 0);
	m_sizer_notebook_tab3_launcher->AddStretchSpacer(1);


	// Tab 3 - Game Directory Sizer
	m_stext_game_directory = new wxStaticText(this, wxID_ANY, "Game Folder: ");
	m_textctrl_game_directory = new wxTextCtrl(this, wxID_ANY, "game directory not found");
	m_button_game_directory_save = new wxButton(this, wxID_ANY, "Save", wxDefaultPosition, wxSize(60, 25));
	m_button_game_directory_browse = new wxButton(this, wxID_ANY, "Browse", wxDefaultPosition, wxSize(60, 25));
	m_button_game_directory_save->Bind(wxEVT_BUTTON, &SettingsPanel::OnGameDirectorySaveClick, this);
	m_button_game_directory_browse->Bind(wxEVT_BUTTON, &SettingsPanel::OnGameDirectoryBrowseClick, this);
	m_dirdialog_game_browse = new wxDirDialog(this, "Select your 'Stardew Valley' game directory",
		wxEmptyString, wxDD_DIR_MUST_EXIST);
	m_sizer_notebook_tab3_game_directory = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_notebook_tab3_game_directory->Add(m_stext_game_directory, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
	m_sizer_notebook_tab3_game_directory->Add(m_textctrl_game_directory, 4, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	m_sizer_notebook_tab3_game_directory->Add(m_button_game_directory_save, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	m_sizer_notebook_tab3_game_directory->Add(m_button_game_directory_browse, 1, wxALIGN_CENTER_VERTICAL, 0);

	// Tab 3 - Steam Directory Sizer
	m_stext_steam_directory = new wxStaticText(this, wxID_ANY, "Steam Folder: ");
	m_textctrl_steam_directory = new wxTextCtrl(this, wxID_ANY, "steam directory not found");
	m_button_steam_directory_save = new wxButton(this, wxID_ANY, "Save", wxDefaultPosition, wxSize(60, 25));
	m_button_steam_directory_browse = new wxButton(this, wxID_ANY, "Browse", wxDefaultPosition, wxSize(60, 25));
	m_button_steam_directory_save->Bind(wxEVT_BUTTON, &SettingsPanel::OnSteamDirectorySaveClick, this);
	m_button_steam_directory_browse->Bind(wxEVT_BUTTON, &SettingsPanel::OnSteamDirectoryBrowseClick, this);
	m_filedialog_steam_browse = new wxFileDialog(this, "Select the Steam executable/application file (Steam.exe)",
		wxEmptyString, "Steam.exe", wxFileSelectorDefaultWildcardStr, wxFD_FILE_MUST_EXIST);
	m_sizer_notebook_tab3_steam_directory = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_notebook_tab3_steam_directory->Add(m_stext_steam_directory, 0, wxALIGN_CENTER_VERTICAL, 0);
	m_sizer_notebook_tab3_steam_directory->Add(m_textctrl_steam_directory, 4, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	m_sizer_notebook_tab3_steam_directory->Add(m_button_steam_directory_save, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	m_sizer_notebook_tab3_steam_directory->Add(m_button_steam_directory_browse, 1, wxALIGN_CENTER_VERTICAL, 0);

	// Tab 3 - Error Mute Sizer
	m_stext_mute = new wxStaticText(this, wxID_ANY, "Mute Mod List Errors:");
	m_checkbox_mute = new wxCheckBox(this, wxID_ANY, "  (unmute for debugging)");
	m_checkbox_mute->Bind(wxEVT_CHECKBOX, &SettingsPanel::OnMuteModToggleClick, this);
	m_sizer_notebook_tab3_mute = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_notebook_tab3_mute->Add(m_stext_mute, 0, wxALIGN_CENTER_VERTICAL, 0);
	m_sizer_notebook_tab3_mute->AddSpacer(5);
	m_sizer_notebook_tab3_mute->Add(m_checkbox_mute, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 0);
	m_sizer_notebook_tab3_mute->AddStretchSpacer(1);

	// Tab 3 - Vertical Sizer // TODO change layout
	m_sizer_notebook_tab3_items = new wxBoxSizer(wxVERTICAL);
	m_sizer_notebook_tab3_items->Add(m_sizer_notebook_tab3_launcher, 0, wxEXPAND, 0);
	m_sizer_notebook_tab3_items->AddSpacer(5);
	m_sizer_notebook_tab3_items->Add(m_sizer_notebook_tab3_game_directory, 0, wxEXPAND, 0);
	m_sizer_notebook_tab3_items->AddSpacer(5);
	m_sizer_notebook_tab3_items->Add(m_sizer_notebook_tab3_steam_directory, 0, wxEXPAND, 0);
	m_sizer_notebook_tab3_items->AddSpacer(5);
	m_sizer_notebook_tab3_items->Add(m_sizer_notebook_tab3_mute, 0, wxEXPAND, 0);
	m_sizer_notebook_tab3_items->AddStretchSpacer(1);

	// Tab 3 - Dummy Sizers for Margins
	m_sizer_notebook_tab3_left = new wxBoxSizer(wxVERTICAL);
	m_sizer_notebook_tab3_left->Add(m_sizer_notebook_tab3_items, 1, wxEXPAND | wxLEFT, 7);
	m_sizer_notebook_tab3_right = new wxBoxSizer(wxVERTICAL);
	m_sizer_notebook_tab3_right->Add(m_sizer_notebook_tab3_left, 1, wxEXPAND | wxRIGHT, 9);
	m_sizer_notebook_tab3 = new wxBoxSizer(wxVERTICAL);
	m_sizer_notebook_tab3->AddSpacer(10);
	m_sizer_notebook_tab3->Add(m_sizer_notebook_tab3_right, 1, wxEXPAND, 0);
	m_sizer_notebook_tab3->AddSpacer(10);
	this->SetSizer(m_sizer_notebook_tab3);
}

SettingsPanel::~SettingsPanel()
{
	delete m_dirdialog_game_browse;
	delete m_filedialog_steam_browse;
	delete config_ini;
}

void SettingsPanel::SelfInitialize()
{
	ini_exists_ = true;
	D(
		OutputDebugString(_T("SelfInit - .ini Exists\n"));
	)

	D(
			OutputDebugString(_T("SelfInit - Open .ini\n"));
	)

	game_directory_ = std::string(config_ini->Read("GamePath", "directory not found"));
	D(
		OutputDebugString(_T("SelfInit - .ini Game Path Read\n"));
	)

	launch_with_steam_ = config_ini->ReadBool("SteamLauncher", true);
	D(
		OutputDebugString(_T("SelfInit - .ini Launcher Preference Read\n"));
	)

	steam_directory_ = std::string(config_ini->Read("SteamPath", "directory not found"));
	D(
		OutputDebugString(_T("SelfInit - .ini Steam Path Read\n"));
	)

	error_mute_["on_refresh"] = config_ini->ReadBool("MuteErrors", false);
	m_checkbox_mute->SetValue(error_mute_["on_refresh"]);
	D(
		OutputDebugString(_T("SelfInit - .ini Launcher Preference Read\n"));
	)

		if (mainWindow->ExistsModFolders())
		{
			D(
				OutputDebugString(_T("SelfInit - Refreshing Mod List\n"));
			)
			mainWindow->m_mod_browser_panel->m_dataviewlistctrl_mods->GetColumn(1)->SetSortOrder(true);
			mainWindow->RefreshModLists();
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
		mainWindow->CheckSmapiVersion();
	D(
		OutputDebugString(_T("SelfInit - Checked SMAPI Version\n"));
	)
}

// Settings Buttons
void SettingsPanel::OnLauncherToggleClick(wxCommandEvent& event)
{
	event.Skip();
	launch_with_steam_ = m_checkbox_launcher->GetValue();
	config_ini->Write("SteamLauncher", m_checkbox_launcher->GetValue());
	config_ini->Flush();
	if (!fs::exists(std::string(m_textctrl_steam_directory->GetLineText(0)) + "\\Steam.exe"))
	{
		if (launch_with_steam_)
		{
			wxMessageDialog* event_launcher_toggle_box1 = new wxMessageDialog(NULL,
				wxT("No Steam files found. \nPlease save the Steam path below and retry."),
				wxT("Launcher Option"), wxOK, wxDefaultPosition);
			event_launcher_toggle_box1->ShowModal();
			delete event_launcher_toggle_box1;
			launch_with_steam_ = false;
		}
	}
	if (launch_with_steam_)
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

void SettingsPanel::OnGameDirectorySaveClick(wxCommandEvent& event)
{
	event.Skip();
	if (fs::exists(std::string(m_textctrl_game_directory->GetLineText(0)) + "\\Stardew Valley.exe"))
	{
		game_directory_ = std::string(m_textctrl_game_directory->GetLineText(0));
		config_ini->Write("GamePath", wxString(game_directory_.string()));
		config_ini->Flush();
		mainWindow->RefreshModLists();
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

void SettingsPanel::OnGameDirectoryBrowseClick(wxCommandEvent& event)
{
	event.Skip();
	if (m_dirdialog_game_browse->ShowModal() == wxID_OK)
	{
		if (fs::exists(std::string(m_dirdialog_game_browse->GetPath()) + "\\Stardew Valley.exe"))
		{
			m_dirdialog_game_browse->SetPath(m_dirdialog_game_browse->GetPath());
			game_directory_ = std::string(m_dirdialog_game_browse->GetPath());
			config_ini->Write("GamePath", wxString(game_directory_.string()));
			config_ini->Flush();
			mainWindow->RefreshModLists();
		}
		else
		{
			m_dirdialog_game_browse->SetPath(m_dirdialog_game_browse->GetPath());
			wxMessageDialog* game_directory_browse_fail = new wxMessageDialog(NULL,
				("Game executable not found in directory:\n" + std::string(m_dirdialog_game_browse->GetPath())),
				wxT("Incorrect Directory"), wxOK, wxDefaultPosition);
			game_directory_browse_fail->ShowModal();
			delete game_directory_browse_fail;
		}
	}
	else {}
}

void SettingsPanel::OnSteamDirectorySaveClick(wxCommandEvent& event)
{
	event.Skip();
	steam_directory_ = string(m_textctrl_steam_directory->GetLineText(0));
	config_ini->Write("SteamPath", wxString(steam_directory_.string()));
	config_ini->Flush();
	if (!fs::exists(string(m_textctrl_steam_directory->GetLineText(0)) + "\\Steam.exe") and
		!fs::exists(string(m_textctrl_steam_directory->GetLineText(0)) + "\\steam.exe"))
	{
		wxMessageDialog* event_bad_steam_directory = new wxMessageDialog(NULL,
			wxT("Steam files not found in: " + string(m_textctrl_steam_directory->GetLineText(0))),
			wxT("Steam Directory"), wxOK, wxDefaultPosition);
		event_bad_steam_directory->ShowModal();
		delete event_bad_steam_directory;
	}
}

void SettingsPanel::OnSteamDirectoryBrowseClick(wxCommandEvent& event)
{
	event.Skip();
	if ((m_filedialog_steam_browse->ShowModal() == wxID_OK))
	{
		if ((fs::exists(std::string(m_filedialog_steam_browse->GetPath()))) and
			((fs::path(std::string((m_filedialog_steam_browse->GetPath()))).filename() == fs::path("Steam.exe")) or
				(fs::path(std::string((m_filedialog_steam_browse->GetPath()))).filename() == fs::path("steam.exe"))))
		{
			m_filedialog_steam_browse->SetPath(m_filedialog_steam_browse->GetPath());
			steam_directory_ = (fs::path(std::string(m_filedialog_steam_browse->GetPath())).parent_path()).string();
			config_ini->Write("SteamPath", wxString(steam_directory_.string()));
			config_ini->Flush();
		}
		else
		{
			m_filedialog_steam_browse->SetPath(m_filedialog_steam_browse->GetPath());
			wxMessageDialog* steam_directory_browse_fail = new wxMessageDialog(NULL,
				("Steam executable not found:\n" + std::string(m_filedialog_steam_browse->GetPath())),
				wxT("Incorrect Directory"), wxOK, wxDefaultPosition);
			steam_directory_browse_fail->ShowModal();
			delete steam_directory_browse_fail;
		}
	}
	else {}
}

void SettingsPanel::OnMuteModToggleClick(wxCommandEvent& event)
{
	event.Skip();
	bool checkboxValue = m_checkbox_mute->GetValue();
	config_ini->Write("MuteErrors", checkboxValue);
	config_ini->Flush();
	error_mute_["on_refresh"] = checkboxValue;
}

