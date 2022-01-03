#pragma once
#include <wx/wx.h>

class MainFrame;

class LauncherButtonPanel : public wxPanel
{
public:
	LauncherButtonPanel(wxWindow* parent, wxWindowID windowID, MainFrame* parentWindow);

private:
	MainFrame* _mMainWindow = nullptr;

	// Top Level Buttons
	void OnLaunchSMAPIClick(wxCommandEvent& event);
	void OnLaunchVanillaClick(wxCommandEvent& event);
	void OnLaunchModSiteClick(wxCommandEvent& event);
	void OnRefreshClick(wxCommandEvent& event);

	// TODO Rename?
	int ID_BUTTON_NEXUS = wxNewId();
	int ID_BUTTON_FORUMS = wxNewId();

	// Right side buttons
	wxButton* m_button_launch_smapi = nullptr;
	wxButton* m_button_launch_vanilla = nullptr;
	wxButton* m_button_add_mod = nullptr;
	wxButton* m_button_nexus_download = nullptr;
	wxButton* m_button_forums_download = nullptr;
	wxButton* m_button_refresh_mods = nullptr;
	wxBoxSizer* m_sizer_buttons_right = nullptr;


};