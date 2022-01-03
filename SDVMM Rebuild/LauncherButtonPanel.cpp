#include "LauncherButtonPanel.h"

#include "MainFrame.h"
#include "SettingsPanel.h"

LauncherButtonPanel::LauncherButtonPanel(wxWindow* parent, wxWindowID windowID, MainFrame* parentWindow)
	: wxPanel(parent, windowID)
	, _mMainWindow(parentWindow)
{
	m_button_launch_smapi = new wxButton(this, wxID_ANY, "Launch SMAPI with Mods");
	m_button_launch_vanilla = new wxButton(this, wxID_ANY, "Launch Stardew Valley");
	m_button_add_mod = new wxButton(this, wxID_ANY, ""); // TODO "Add Mod from File/Archive" // REMOVED FOR 0.5.0-ALPHA RELEASE
	m_button_nexus_download = new wxButton(this, ID_BUTTON_NEXUS, "Visit Nexus Mods");
	m_button_forums_download = new wxButton(this, ID_BUTTON_FORUMS, "Visit Mod Forums");
	m_button_refresh_mods = new wxButton(this, wxID_ANY, "Refresh Mod List");
	m_button_launch_smapi->Bind(wxEVT_BUTTON, &LauncherButtonPanel::OnLaunchSMAPIClick, this);
	m_button_launch_vanilla->Bind(wxEVT_BUTTON, &LauncherButtonPanel::OnLaunchVanillaClick, this);
	m_button_nexus_download->Bind(wxEVT_BUTTON, &LauncherButtonPanel::OnLaunchModSiteClick, this);
	m_button_forums_download->Bind(wxEVT_BUTTON, &LauncherButtonPanel::OnLaunchModSiteClick, this);
	m_button_refresh_mods->Bind(wxEVT_BUTTON, &LauncherButtonPanel::OnRefreshClick, this);

	// Right side button - sizer
	int proportion_button = 10;
	int proportion_spacer = 1;
	m_sizer_buttons_right = new wxBoxSizer(wxVERTICAL);
	m_sizer_buttons_right->Add(m_button_launch_smapi, proportion_button, wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(proportion_spacer);
	m_sizer_buttons_right->Add(m_button_launch_vanilla, proportion_button, wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(proportion_spacer);
	m_sizer_buttons_right->Add(m_button_add_mod, (proportion_button / 2), wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(proportion_spacer);
	m_sizer_buttons_right->Add(m_button_nexus_download, (proportion_button / 2), wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(proportion_spacer);
	m_sizer_buttons_right->Add(m_button_forums_download, (proportion_button / 2), wxEXPAND, 0);
	m_sizer_buttons_right->AddStretchSpacer(proportion_spacer);
	m_sizer_buttons_right->Add(m_button_refresh_mods, proportion_button, wxEXPAND, 0);
	this->SetSizer(m_sizer_buttons_right);
	this->SetMaxSize(wxSize(250, 500));

}

// Top Level Buttons
void LauncherButtonPanel::OnLaunchSMAPIClick(wxCommandEvent& event) { // TODO Steam Launcher option
	event.Skip();
	if (_mMainWindow->mErrorChecks[ModErrors::smapi] == true) {
		m_button_launch_smapi->Disable();
		m_button_launch_smapi->SetLabel("SMAPI Not Found!");
	}
	else {
		if (_mMainWindow->mSettingsPanel->shouldLaunchWithSteam()) {
			std::string test_str = ((_mMainWindow->mSettingsPanel->steamDirectory().string() + "\\Steam.exe")) + " -applaunch 413150" +
				" \"" + _mMainWindow->mSettingsPanel->gameDirectory().string() + "//StardewValleyAPI.exe\" %command%";
			const char* open_command = (test_str.c_str());
			wxExecute(open_command, wxEXEC_ASYNC, NULL);

		}
		else {
			wxString temp = wxGetCwd();
			wxSetWorkingDirectory(_mMainWindow->mSettingsPanel->gameDirectory().string());
			std::string test_str = ((_mMainWindow->mSettingsPanel->gameDirectory().string() + "\\StardewModdingAPI"));
			const char* open_command = (test_str.c_str());
			wxExecute(open_command, wxEXEC_ASYNC, NULL);
			wxSetWorkingDirectory(temp);
		}
	}
}

void LauncherButtonPanel::OnLaunchVanillaClick(wxCommandEvent& event) { // TODO Steam Launcher option
	event.Skip();
	if (_mMainWindow->mSettingsPanel->shouldLaunchWithSteam()) {
		std::string test_str = ((_mMainWindow->mSettingsPanel->steamDirectory().string() + "\\Steam.exe")) + " -applaunch 413150";
		const char* open_command = (test_str.c_str());
		wxExecute(open_command, wxEXEC_ASYNC, NULL);
		wxExecute(open_command, wxEXEC_ASYNC, NULL);
	}
	else {
		wxString temp = wxGetCwd();
		wxSetWorkingDirectory(_mMainWindow->mSettingsPanel->gameDirectory().string());
		std::string test_str = ((_mMainWindow->mSettingsPanel->gameDirectory().string() + "\\Stardew Valley"));
		const char* open_command = (test_str.c_str());
		wxExecute(open_command, wxEXEC_ASYNC, NULL);
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

