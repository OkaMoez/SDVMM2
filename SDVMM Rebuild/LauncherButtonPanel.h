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
	wxButton* _mLaunchSmapiButton = nullptr;
	wxButton* _mLaunchVanillaButton = nullptr;
	wxButton* _mAddModButton = nullptr;
	wxButton* _mVisitNexusButton = nullptr;
	wxButton* _mVisitForumsButton = nullptr;
	wxButton* _mRefreshModListButton = nullptr;
	wxBoxSizer* _mLauncherButtonsSizer = nullptr;


};