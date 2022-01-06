#include "LauncherButtonPanel.h"

#include "MainFrame.h"
#include "SettingsPanel.h"

LauncherButtonPanel::LauncherButtonPanel(MainFrame* main, wxWindow* parent, wxWindowID windowID)
	: wxPanel(parent, windowID)
	, _mMainWindow(main) {
	_mLaunchSmapiButton = new wxButton(this, wxID_ANY, "Launch SMAPI with Mods");
	_mLaunchVanillaButton = new wxButton(this, wxID_ANY, "Launch Stardew Valley");
	_mAddModButton = new wxButton(this, wxID_ANY, ""); // TODO "Add Mod from File/Archive" // REMOVED FOR 0.5.0-ALPHA RELEASE
	_mVisitNexusButton = new wxButton(this, ID_BUTTON_NEXUS, "Visit Nexus Mods");
	_mVisitForumsButton = new wxButton(this, ID_BUTTON_FORUMS, "Visit Mod Forums");
	_mRefreshModListButton = new wxButton(this, wxID_ANY, "Refresh Mod List");
	_mLaunchSmapiButton->Bind(wxEVT_BUTTON, &LauncherButtonPanel::OnLaunchSMAPIClick, this);
	_mLaunchVanillaButton->Bind(wxEVT_BUTTON, &LauncherButtonPanel::OnLaunchVanillaClick, this);
	_mVisitNexusButton->Bind(wxEVT_BUTTON, &LauncherButtonPanel::OnLaunchModSiteClick, this);
	_mVisitForumsButton->Bind(wxEVT_BUTTON, &LauncherButtonPanel::OnLaunchModSiteClick, this);
	_mRefreshModListButton->Bind(wxEVT_BUTTON, &LauncherButtonPanel::OnRefreshClick, this);

	// Right side button - sizer
	int buttonSizeRelative = 10;
	int gapSizeRelative = 1;
	_mLauncherButtonsSizer = new wxBoxSizer(wxVERTICAL);
	_mLauncherButtonsSizer->Add(_mLaunchSmapiButton, buttonSizeRelative, wxEXPAND, 0);
	_mLauncherButtonsSizer->AddStretchSpacer(gapSizeRelative);
	_mLauncherButtonsSizer->Add(_mLaunchVanillaButton, buttonSizeRelative, wxEXPAND, 0);
	_mLauncherButtonsSizer->AddStretchSpacer(gapSizeRelative);
	_mLauncherButtonsSizer->Add(_mAddModButton, (buttonSizeRelative / 2), wxEXPAND, 0);
	_mLauncherButtonsSizer->AddStretchSpacer(gapSizeRelative);
	_mLauncherButtonsSizer->Add(_mVisitNexusButton, (buttonSizeRelative / 2), wxEXPAND, 0);
	_mLauncherButtonsSizer->AddStretchSpacer(gapSizeRelative);
	_mLauncherButtonsSizer->Add(_mVisitForumsButton, (buttonSizeRelative / 2), wxEXPAND, 0);
	_mLauncherButtonsSizer->AddStretchSpacer(gapSizeRelative);
	_mLauncherButtonsSizer->Add(_mRefreshModListButton, buttonSizeRelative, wxEXPAND, 0);
	this->SetSizer(_mLauncherButtonsSizer);
	this->SetMaxSize(wxSize(250, 500));

}

// Top Level Buttons
void LauncherButtonPanel::OnLaunchSMAPIClick(wxCommandEvent& event) { // TODO Steam Launcher option
	event.Skip();
	if (_mMainWindow->mErrorChecks[ModErrors::smapi] == true) {
		_mLaunchSmapiButton->Disable();
		_mLaunchSmapiButton->SetLabel("SMAPI Not Found!");
	}
	else {
		if (_mMainWindow->mSettingsPanel->shouldLaunchWithSteam()) {
			std::string testString = ((_mMainWindow->mSettingsPanel->steamDirectory().string() + "\\Steam.exe")) + " -applaunch 413150" +
				" \"" + _mMainWindow->mSettingsPanel->gameDirectory().string() + "//StardewValleyAPI.exe\" %command%";
			const char* openCommand = (testString.c_str());
			wxExecute(openCommand, wxEXEC_ASYNC, NULL);

		}
		else {
			wxString temp = wxGetCwd();
			wxSetWorkingDirectory(_mMainWindow->mSettingsPanel->gameDirectory().string());
			std::string testString = ((_mMainWindow->mSettingsPanel->gameDirectory().string() + "\\StardewModdingAPI"));
			const char* openCommand = (testString.c_str());
			wxExecute(openCommand, wxEXEC_ASYNC, NULL);
			wxSetWorkingDirectory(temp);
		}
	}
}

void LauncherButtonPanel::OnLaunchVanillaClick(wxCommandEvent& event) { // TODO Steam Launcher option
	event.Skip();
	if (_mMainWindow->mSettingsPanel->shouldLaunchWithSteam()) {
		std::string testString = ((_mMainWindow->mSettingsPanel->steamDirectory().string() + "\\Steam.exe")) + " -applaunch 413150";
		const char* openCommand = (testString.c_str());
		wxExecute(openCommand, wxEXEC_ASYNC, NULL);
		wxExecute(openCommand, wxEXEC_ASYNC, NULL);
	}
	else {
		wxString temp = wxGetCwd();
		wxSetWorkingDirectory(_mMainWindow->mSettingsPanel->gameDirectory().string());
		std::string testString = ((_mMainWindow->mSettingsPanel->gameDirectory().string() + "\\Stardew Valley"));
		const char* openCommand = (testString.c_str());
		wxExecute(openCommand, wxEXEC_ASYNC, NULL);
		wxSetWorkingDirectory(temp);
	}

}

void LauncherButtonPanel::OnLaunchModSiteClick(wxCommandEvent& event) {

	if (event.GetId() == ID_BUTTON_NEXUS) {
		wxLaunchDefaultBrowser("https://www.nexusmods.com/stardewvalley");
	}
	else if (event.GetId() == ID_BUTTON_FORUMS) {
		wxLaunchDefaultBrowser("https://community.playstarbound.com/forums/mods.215/");
	}
	event.Skip();
}

void LauncherButtonPanel::OnRefreshClick(wxCommandEvent& event) { // TODO give some indication of the refresh
	event.Skip();
	_mMainWindow->mRefreshModLists();
}

