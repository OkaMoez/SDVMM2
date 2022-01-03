#pragma once
#include <wx/wx.h>

class MainFrame;

class MenuBar : public wxMenuBar {
public:
	MenuBar(MainFrame* parentWindow);

private:
	MainFrame* mainWindow = nullptr;

	// Menu Bar Buttons
	void OnMenuClick(wxCommandEvent& event); // TODO complete
	void OnMenuModsClick(wxCommandEvent& event); // TODO Make cross platform
	void OnMenuModsDisabledClick(wxCommandEvent& event);  // TODO Make cross platform
	void OnMenuQuitClick(wxCommandEvent& event);

	wxMenu* m_menubar_file = nullptr;
	wxMenu* m_menubar_help = nullptr;

	// TODO Rename?
	int ID_MENU_MODS = wxNewId();
	int ID_MENU_DMODS = wxNewId();
	int ID_MENU_QUIT = wxNewId();
};
