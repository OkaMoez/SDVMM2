#include "SettingsPanel.h"

SettingsPanel::SettingsPanel(wxWindow* parent, wxWindowID windowID) 
	: wxPanel(parent, windowID)
{
	// Tab 3 - Launcher Sizer
	m_stext_launcher = new wxStaticText(this, wxID_ANY, "Launch w/ Steam: ");
	m_checkbox_launcher = new wxCheckBox(this, wxID_ANY, "  (uncheck if you have the GOG version)");
	//m_checkbox_launcher->Bind(wxEVT_CHECKBOX, &cMain::OnLauncherToggleClick, this);
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
	//m_button_game_directory_save->Bind(wxEVT_BUTTON, &cMain::OnGameDirectorySaveClick, this);
	//m_button_game_directory_browse->Bind(wxEVT_BUTTON, &cMain::OnGameDirectoryBrowseClick, this);
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
	//m_button_steam_directory_save->Bind(wxEVT_BUTTON, &cMain::OnSteamDirectorySaveClick, this);
	//m_button_steam_directory_browse->Bind(wxEVT_BUTTON, &cMain::OnSteamDirectoryBrowseClick, this);
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
	//m_checkbox_mute->Bind(wxEVT_CHECKBOX, &cMain::OnMuteModToggleClick, this);
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
