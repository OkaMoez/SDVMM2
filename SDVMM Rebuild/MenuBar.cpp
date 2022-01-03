#include "MenuBar.h"

#include "MainFrame.h"
#include "SettingsPanel.h"

MenuBar::MenuBar(MainFrame* parentWindow)
	: _mMainWindow(parentWindow) {
	// Menubar - File, Help, etc
	mMenubar_file = new wxMenu;
	//mMenubar_help = new wxMenu; // REMOVED FOR 0.5.0-ALPHA RELEASE
	this->Append(mMenubar_file, wxT("&File"));
	mMenubar_file->Append(ID_MENU_MODS, wxT("&Open Mods Folder"), wxEmptyString, wxITEM_NORMAL);
	mMenubar_file->Append(ID_MENU_DMODS, wxT("&Open Disabled Mods Folder"), wxEmptyString, wxITEM_NORMAL);
	mMenubar_file->Append(ID_MENU_QUIT, wxT("&Quit"), wxEmptyString, wxITEM_NORMAL);
	//this->Append(mMenubar_help, wxT("&Help")); // REMOVED FOR 0.5.0-ALPHA RELEASE
	this->Bind(wxEVT_MENU, &MenuBar::OnMenuClick, this, ID_MENU_MODS, ID_MENU_QUIT);
}

// Menu Bar Buttons
void MenuBar::OnMenuClick(wxCommandEvent& event){ // TODO complete 
	if (event.GetId() == (ID_MENU_MODS)) {
		OnMenuModsClick(event);
	}
	else if (event.GetId() == (ID_MENU_DMODS)) {
		OnMenuModsDisabledClick(event);
	}
	else if (event.GetId() == (ID_MENU_QUIT)) {
		OnMenuQuitClick(event);
	}
}

void MenuBar::OnMenuModsClick(wxCommandEvent& event) {
	event.Skip();
	std::string test_str = ("explorer " + (_mMainWindow->mSettingsPanel->gameDirectory().string() + "\\Mods\\"));
	const char* open_command = (test_str.c_str());
	wxExecute(open_command, wxEXEC_ASYNC, NULL);


	/*
	Windows - explorer
	mac - open
	linux - konqueror or whatever gnome uses (nautilus?)
	*/
}

void MenuBar::OnMenuModsDisabledClick(wxCommandEvent& event) {
	event.Skip();
	std::string test_str = ("explorer " + (_mMainWindow->mSettingsPanel->gameDirectory().string() + "\\Mods_disabled"));
	const char* open_command = (test_str.c_str());
	wxExecute(open_command, wxEXEC_ASYNC, NULL);
}

void MenuBar::OnMenuQuitClick(wxCommandEvent& event) {
	event.Skip();
	this->Close();
}

