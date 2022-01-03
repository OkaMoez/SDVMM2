#include "MenuBar.h"

#include "cMain.h"
#include "SettingsPanel.h"

MenuBar::MenuBar(cMain* parentWindow)
	: mainWindow(parentWindow)
{
	// Menubar - File, Help, etc
	m_menubar_file = new wxMenu;
	//m_menubar_help = new wxMenu; // REMOVED FOR 0.5.0-ALPHA RELEASE
	this->Append(m_menubar_file, wxT("&File"));
	m_menubar_file->Append(ID_MENU_MODS, wxT("&Open Mods Folder"), wxEmptyString, wxITEM_NORMAL);
	m_menubar_file->Append(ID_MENU_DMODS, wxT("&Open Disabled Mods Folder"), wxEmptyString, wxITEM_NORMAL);
	m_menubar_file->Append(ID_MENU_QUIT, wxT("&Quit"), wxEmptyString, wxITEM_NORMAL);
	//this->Append(m_menubar_help, wxT("&Help")); // REMOVED FOR 0.5.0-ALPHA RELEASE
	this->Bind(wxEVT_MENU, &MenuBar::OnMenuClick, this, ID_MENU_MODS, ID_MENU_QUIT);
}

// Menu Bar Buttons
void MenuBar::OnMenuClick(wxCommandEvent& event) // TODO complete
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

void MenuBar::OnMenuModsClick(wxCommandEvent& event)
{
	event.Skip();
	std::string test_str = ("explorer " + (mainWindow->m_settings_panel->game_directory().string() + "\\Mods\\"));
	const char* open_command = (test_str.c_str());
	wxExecute(open_command, wxEXEC_ASYNC, NULL);


	/*
	Windows - explorer
	mac - open
	linux - konqueror or whatever gnome uses (nautilus?)
	*/
}

void MenuBar::OnMenuModsDisabledClick(wxCommandEvent& event)
{
	event.Skip();
	std::string test_str = ("explorer " + (mainWindow->m_settings_panel->game_directory().string() + "\\Mods_disabled"));
	const char* open_command = (test_str.c_str());
	wxExecute(open_command, wxEXEC_ASYNC, NULL);
}

void MenuBar::OnMenuQuitClick(wxCommandEvent& event)
{
	event.Skip();
	this->Close();
}

