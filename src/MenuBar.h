#pragma once
#include <wx/wx.h>

class MainFrame;

class MenuBar : public wxMenuBar {
public:
	MenuBar(MainFrame* parent);

private:
	MainFrame* _mMainWindow = nullptr;

	// Menu Bar Buttons
	void OnMenuClick(wxCommandEvent& event); // TODO complete
	void OnMenuModsClick(wxCommandEvent& event); // TODO Make cross platform
	void OnMenuModsDisabledClick(wxCommandEvent& event);  // TODO Make cross platform
	void OnMenuQuitClick(wxCommandEvent& event);

	wxMenu* mMenubar_file = nullptr;
	wxMenu* mMenubar_help = nullptr;

	// TODO Rename?
	int ID_MENU_MODS = wxNewId();
	int ID_MENU_DMODS = wxNewId();
	int ID_MENU_QUIT = wxNewId();
};
