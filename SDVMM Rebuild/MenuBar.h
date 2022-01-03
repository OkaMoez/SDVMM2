#pragma once
#include <wx/wx.h>

class cMain;

class MenuBar : public wxMenuBar {
public:
	MenuBar(cMain* parentWindow);

private:
	cMain* mainWindow = nullptr;

	// Menu Bar Buttons
	void OnMenuClick(wxCommandEvent& event); // TODO complete
	void OnMenuModsClick(wxCommandEvent& event); // TODO Make cross platform
	void OnMenuModsDisabledClick(wxCommandEvent& event);  // TODO Make cross platform
	void OnMenuQuitClick(wxCommandEvent& event);

	wxMenu* m_menubar_file = nullptr;
	wxMenu* m_menubar_help = nullptr;

	int ID_MENU_MODS = wxNewId();
	int ID_MENU_DMODS = wxNewId();
	int ID_MENU_QUIT = wxNewId();
};
