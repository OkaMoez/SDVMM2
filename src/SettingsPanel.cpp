#include "SettingsPanel.h"

#include "MainFrame.h"
#include "ModBrowserPanel.h"

SettingsPanel::SettingsPanel(MainFrame* main, wxWindow* parent, wxWindowID windowID)
	: wxPanel(parent, windowID)
	, _mMainWindow(main) {
	// Tab 3 - Launcher Sizer
	_mLauncherChoiceStext = new wxStaticText(this, wxID_ANY, "Launch w/ Steam: ");
	_mLauncherChoiceCheckbox = new wxCheckBox(this, wxID_ANY, "  (uncheck if you have the GOG version)");
	_mLauncherChoiceCheckbox->Bind(wxEVT_CHECKBOX, &SettingsPanel::onLauncherToggleClick, this);
	_mLauncherChoiceSizer = new wxBoxSizer(wxHORIZONTAL);
	_mLauncherChoiceSizer->Add(_mLauncherChoiceStext, 0, wxALIGN_CENTER_VERTICAL, 0);
	_mLauncherChoiceSizer->AddSpacer(20);
	_mLauncherChoiceSizer->Add(_mLauncherChoiceCheckbox, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 0);
	_mLauncherChoiceSizer->AddStretchSpacer(1);


	// Tab 3 - Game Directory Sizer
	_mGameDirectoryStext = new wxStaticText(this, wxID_ANY, "Game Folder: ");
	_mGameDirectoryTextctrl = new wxTextCtrl(this, wxID_ANY, "game directory not found");
	_mGameDirectorySaveButton = new wxButton(this, wxID_ANY, "Save", wxDefaultPosition, wxSize(60, 25));
	_mGameDirectoryBrowseButton = new wxButton(this, wxID_ANY, "Browse", wxDefaultPosition, wxSize(60, 25));
	_mGameDirectorySaveButton->Bind(wxEVT_BUTTON, &SettingsPanel::onGameDirectorySaveClick, this);
	_mGameDirectoryBrowseButton->Bind(wxEVT_BUTTON, &SettingsPanel::onGameDirectoryBrowseClick, this);
	_mGameDirectoryDirdialog = new wxDirDialog(this, "Select your 'Stardew Valley' game directory",
		wxEmptyString, wxDD_DIR_MUST_EXIST);
	_mGameDirectorySizer = new wxBoxSizer(wxHORIZONTAL);
	_mGameDirectorySizer->Add(_mGameDirectoryStext, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 2);
	_mGameDirectorySizer->Add(_mGameDirectoryTextctrl, 4, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	_mGameDirectorySizer->Add(_mGameDirectorySaveButton, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	_mGameDirectorySizer->Add(_mGameDirectoryBrowseButton, 1, wxALIGN_CENTER_VERTICAL, 0);

	// Tab 3 - Steam Directory Sizer
	_mSteamDirectoryStext = new wxStaticText(this, wxID_ANY, "Steam Folder: ");
	_mSteamDirectoryTextctrl = new wxTextCtrl(this, wxID_ANY, "steam directory not found");
	_mSteamDirectorySaveButton = new wxButton(this, wxID_ANY, "Save", wxDefaultPosition, wxSize(60, 25));
	_mSteamDirectoryBrowseButton = new wxButton(this, wxID_ANY, "Browse", wxDefaultPosition, wxSize(60, 25));
	_mSteamDirectorySaveButton->Bind(wxEVT_BUTTON, &SettingsPanel::onSteamDirectorySaveClick, this);
	_mSteamDirectoryBrowseButton->Bind(wxEVT_BUTTON, &SettingsPanel::onSteamDirectoryBrowseClick, this);
	_mSteamDirectoryFiledialog = new wxFileDialog(this, "Select the Steam executable/application file (Steam.exe)",
		wxEmptyString, "Steam.exe", wxFileSelectorDefaultWildcardStr, wxFD_FILE_MUST_EXIST);
	_mSteamDirectorySizer = new wxBoxSizer(wxHORIZONTAL);
	_mSteamDirectorySizer->Add(_mSteamDirectoryStext, 0, wxALIGN_CENTER_VERTICAL, 0);
	_mSteamDirectorySizer->Add(_mSteamDirectoryTextctrl, 4, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	_mSteamDirectorySizer->Add(_mSteamDirectorySaveButton, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	_mSteamDirectorySizer->Add(_mSteamDirectoryBrowseButton, 1, wxALIGN_CENTER_VERTICAL, 0);

	// Tab 3 - Error Mute Sizer
	_mmMuteErrorsStext = new wxStaticText(this, wxID_ANY, "Mute Mod List Errors:");
	_mmMuteErrorsCheckbox = new wxCheckBox(this, wxID_ANY, "  (unmute for debugging)");
	_mmMuteErrorsCheckbox->Bind(wxEVT_CHECKBOX, &SettingsPanel::onMuteModToggleClick, this);
	_mmMuteErrorsSizer = new wxBoxSizer(wxHORIZONTAL);
	_mmMuteErrorsSizer->Add(_mmMuteErrorsStext, 0, wxALIGN_CENTER_VERTICAL, 0);
	_mmMuteErrorsSizer->AddSpacer(5);
	_mmMuteErrorsSizer->Add(_mmMuteErrorsCheckbox, 0, wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 0);
	_mmMuteErrorsSizer->AddStretchSpacer(1);

	// Tab 3 - Vertical Sizer // TODO change layout
	_mSettingsFieldsSizer = new wxBoxSizer(wxVERTICAL);
	_mSettingsFieldsSizer->Add(_mLauncherChoiceSizer, 0, wxEXPAND, 0);
	_mSettingsFieldsSizer->AddSpacer(5);
	_mSettingsFieldsSizer->Add(_mGameDirectorySizer, 0, wxEXPAND, 0);
	_mSettingsFieldsSizer->AddSpacer(5);
	_mSettingsFieldsSizer->Add(_mSteamDirectorySizer, 0, wxEXPAND, 0);
	_mSettingsFieldsSizer->AddSpacer(5);
	_mSettingsFieldsSizer->Add(_mmMuteErrorsSizer, 0, wxEXPAND, 0);
	_mSettingsFieldsSizer->AddStretchSpacer(1);

	// Tab 3 - Dummy Sizers for Margins
	_mLeftSpacerSizer = new wxBoxSizer(wxVERTICAL);
	_mLeftSpacerSizer->Add(_mSettingsFieldsSizer, 1, wxEXPAND | wxLEFT, 7);
	_mRightSpacerSizer = new wxBoxSizer(wxVERTICAL);
	_mRightSpacerSizer->Add(_mLeftSpacerSizer, 1, wxEXPAND | wxRIGHT, 9);
	_mSettingsPanelSizer = new wxBoxSizer(wxVERTICAL);
	_mSettingsPanelSizer->AddSpacer(10);
	_mSettingsPanelSizer->Add(_mRightSpacerSizer, 1, wxEXPAND, 0);
	_mSettingsPanelSizer->AddSpacer(10);
	this->SetSizer(_mSettingsPanelSizer);
}

SettingsPanel::~SettingsPanel() {
	delete _mGameDirectoryDirdialog;
	delete _mSteamDirectoryFiledialog;
	delete mConfigIni;
}

void SettingsPanel::tryLoadSettings() {
	// TODO: handle init with/out ini differently
	// have mute init true if no ini is found
	_mIniExists = true;
	DPRINT("SelfInit - .ini Exists\n");

	DPRINT("SelfInit - Open .ini\n");

	// Check game directory
	_mGameDirectory = std::string(mConfigIni->Read("GamePath", "directory not found"));
	_mGameDirectoryTextctrl->ChangeValue(_mGameDirectory.string());
	DPRINT("SelfInit - .ini Game Path Read\n");

	// Check "launch with steam" setting
	_mLaunchWithSteam = mConfigIni->ReadBool("SteamLauncher", true);
	_mLauncherChoiceCheckbox->SetValue(_mLaunchWithSteam["on_refresh"]);
	DPRINT("SelfInit - .ini Launcher Preference Read\n");

	// Check steam directory
	_mSteamDirectory = std::string(mConfigIni->Read("SteamPath", "directory not found"));
	_mSteamDirectoryTextctrl->ChangeValue(_mSteamDirectory.string());
	DPRINT("SelfInit - .ini Steam Path Read\n");

	// Check mute errors setting
	mMuteErrors["on_refresh"] = mConfigIni->ReadBool("mMuteErrors", true);
	_mmMuteErrorsCheckbox->SetValue(mMuteErrors["on_refresh"]);
	DPRINT("SelfInit - .ini Launcher Preference Read\n");

	if (_mMainWindow->mExistsModFolders()) {
		DPRINT("SelfInit - Refreshing Mod List\n");
		_mMainWindow->mModBrowserPanel->mModBrowserDataviewlistctrl->GetColumn(1)->SetSortOrder(true);
		_mMainWindow->mRefreshModLists();
		DPRINT("Refreshed Mod List\n");
	}
	else {
		DPRINT("SelfInit - No Mod Folders Found\n");
	}
	DPRINT("SelfInit - Game Directory\n" + gameDirectory().string() + "\n" + "SelfInit - Checking SMAPI Version\n");
	_mMainWindow->mCheckSmapiVersion();
	DPRINT("SelfInit - Checked SMAPI Version\n");
}

// Settings Buttons
void SettingsPanel::onLauncherToggleClick(wxCommandEvent& event) {
	event.Skip();
	_mLaunchWithSteam = _mLauncherChoiceCheckbox->GetValue();
	mConfigIni->Write("SteamLauncher", _mLauncherChoiceCheckbox->GetValue());
	mConfigIni->Flush();
	if (!fs::exists(std::string(_mSteamDirectoryTextctrl->GetLineText(0)) + "\\Steam.exe")) {
		if (_mLaunchWithSteam) {
			wxMessageDialog* eventLauncherToggleBox1 = new wxMessageDialog(NULL,
				wxT("No Steam files found. \nPlease save the Steam path below and retry."),
				wxT("Launcher Option"), wxOK, wxDefaultPosition);
			eventLauncherToggleBox1->ShowModal();
			delete eventLauncherToggleBox1;
			_mLaunchWithSteam = false;
		}
	}
	if (_mLaunchWithSteam) {
		D(
			if (REPORT_LAUNCHER_CBOX_EVENT) {
				wxMessageDialog* eventLauncherToggleBox1 = new wxMessageDialog(NULL,
					wxT("Launcher toggled on."), wxT("Launcher Option"),
					wxOK, wxDefaultPosition);
				eventLauncherToggleBox1->ShowModal();
				delete eventLauncherToggleBox1;
			}
		)
	}
}

void SettingsPanel::onGameDirectorySaveClick(wxCommandEvent& event) {
	event.Skip();
	if (fs::exists(std::string(_mGameDirectoryTextctrl->GetLineText(0)) + "\\Stardew Valley.exe")) {
		_mGameDirectory = std::string(_mGameDirectoryTextctrl->GetLineText(0));
		mConfigIni->Write("GamePath", wxString(_mGameDirectory.string()));
		mConfigIni->Flush();
		_mMainWindow->mRefreshModLists();
	}
	else {
		wxMessageDialog* eventBadGameDirectory = new wxMessageDialog(NULL,
			wxT("Game files not found in: " + std::string(_mGameDirectoryTextctrl->GetLineText(0))),
			wxT("Game Directory"), wxOK, wxDefaultPosition);
		eventBadGameDirectory->ShowModal();
		delete eventBadGameDirectory;
	}
}

void SettingsPanel::onGameDirectoryBrowseClick(wxCommandEvent& event) {
	event.Skip();
	if (_mGameDirectoryDirdialog->ShowModal() == wxID_OK) {
		std::string browsedGamePath = _mGameDirectoryDirdialog->GetPath().ToStdString();
		bool gameFileExists = fs::exists(browsedGamePath + "\\Stardew Valley.exe");

		if (gameFileExists) {
			_mGameDirectoryDirdialog->SetPath(_mGameDirectoryDirdialog->GetPath());
			_mGameDirectoryTextctrl->ChangeValue(browsedGamePath);
			_mGameDirectory = browsedGamePath;
			mConfigIni->Write("GamePath", wxString(_mGameDirectory.string()));
			mConfigIni->Flush();
			_mMainWindow->mRefreshModLists();
		}
		else {
			_mGameDirectoryDirdialog->SetPath(_mGameDirectoryDirdialog->GetPath());
			wxMessageDialog* gameDirectoryBrowseFail = new wxMessageDialog(NULL,
				("Game executable not found in directory:\n" + std::string(_mGameDirectoryDirdialog->GetPath())),
				wxT("Incorrect Directory"), wxOK, wxDefaultPosition);
			gameDirectoryBrowseFail->ShowModal();
			delete gameDirectoryBrowseFail;
		}
	}
}

void SettingsPanel::onSteamDirectorySaveClick(wxCommandEvent& event) {
	event.Skip();
	_mSteamDirectory = std::string(_mSteamDirectoryTextctrl->GetLineText(0));
	mConfigIni->Write("SteamPath", wxString(_mSteamDirectory.string()));
	mConfigIni->Flush();
	if (!fs::exists(std::string(_mSteamDirectoryTextctrl->GetLineText(0)) + "\\Steam.exe") and
		!fs::exists(std::string(_mSteamDirectoryTextctrl->GetLineText(0)) + "\\steam.exe")) {
		wxMessageDialog* eventBadSteamDirectory = new wxMessageDialog(NULL,
			wxT("Steam files not found in: " + std::string(_mSteamDirectoryTextctrl->GetLineText(0))),
			wxT("Steam Directory"), wxOK, wxDefaultPosition);
		eventBadSteamDirectory->ShowModal();
		delete eventBadSteamDirectory;
	}
}

void SettingsPanel::onSteamDirectoryBrowseClick(wxCommandEvent& event) {
	event.Skip();
	if ((_mSteamDirectoryFiledialog->ShowModal() == wxID_OK)) {
		std::string browsedSteamPath = _mSteamDirectoryFiledialog->GetPath().ToStdString();
		fs::path browsedSteamFile = fs::path(browsedSteamPath).filename();
		bool steamFileExists = fs::exists(browsedSteamPath);
		bool steamExecutableExists = (browsedSteamFile == fs::path("Steam.exe"))
			or (browsedSteamFile == fs::path("steam.exe"));

		if (steamFileExists and steamExecutableExists) {
			std::string browsedSteamDirectory = fs::path(browsedSteamPath).parent_path().string();
			_mSteamDirectoryFiledialog->SetPath(_mSteamDirectoryFiledialog->GetPath());
			_mSteamDirectoryTextctrl->ChangeValue(browsedSteamDirectory);
			_mSteamDirectory = (browsedSteamDirectory);

			mConfigIni->Write("SteamPath", wxString(_mSteamDirectory.string()));
			mConfigIni->Flush();
		}
		else {
			_mSteamDirectoryFiledialog->SetPath(_mSteamDirectoryFiledialog->GetPath());
			wxMessageDialog* _mSteamDirectorybrowse_fail = new wxMessageDialog(NULL,
				("Steam executable not found:\n" + browsedSteamPath),
				wxT("Incorrect Directory"), wxOK, wxDefaultPosition);
			_mSteamDirectorybrowse_fail->ShowModal();
			delete _mSteamDirectorybrowse_fail;
		}
	}
}

void SettingsPanel::onMuteModToggleClick(wxCommandEvent& event) {
	event.Skip();
	bool checkboxValue = _mmMuteErrorsCheckbox->GetValue();
	mConfigIni->Write("mMuteErrors", checkboxValue);
	mConfigIni->Flush();
	mMuteErrors["on_refresh"] = checkboxValue;
}

