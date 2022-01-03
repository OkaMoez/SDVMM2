#include "MainFrame.h"

#include "LauncherButtonPanel.h"
#include "MenuBar.h"
#include "ModBrowserPanel.h"
#include "SettingsPanel.h"

#include "JsonCleaner.h"

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Stardew Valley Mod Manager 2",
	wxDefaultPosition, wxSize(750, 500),
	wxDEFAULT_FRAME_STYLE)
{
	SetMinSize(wxSize(750, 500));

	//---------------------------
	//  Notebook Implementation
	//---------------------------
	mTabbedNotebook = new wxNotebook(this, -1);

	mModBrowserPanel = new ModBrowserPanel(mTabbedNotebook, wxID_ANY, this);
	mTabbedNotebook->AddPage(mModBrowserPanel, "SMAPI Mods", true);

	mSettingsPanel = new SettingsPanel(mTabbedNotebook, wxID_ANY, this);
	mTabbedNotebook->AddPage(mSettingsPanel, "Settings", false);

	//---------------------------------
	//  Additional GUI Implementation
	//---------------------------------

	// Launcher buttons
	mLauncherPanel = new LauncherButtonPanel(this, wxID_ANY, this);

	// Horizontal layout
	mMainFrameHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
	mMainFrameHorizontalSizer->Add(mTabbedNotebook, 2, wxEXPAND | wxLEFT | wxRIGHT, 10);
	mMainFrameHorizontalSizer->Add(mLauncherPanel, 1, wxEXPAND | wxRIGHT, 10);

	// Menubar - File, Help, etc
	mMenubar = new MenuBar(this);
	SetMenuBar(mMenubar);

	// Title banner
	wxImage::AddHandler(new wxPNGHandler);
	mBitmapBanner = new wxStaticBitmap(this, wxID_ANY, wxBitmap("SDVMM2.png", wxBITMAP_TYPE_PNG)); // TODO save in code?
	wxImage::CleanUpHandlers();
	mHorizontalBannerSizer = new wxBoxSizer(wxHORIZONTAL);
	mHorizontalBannerSizer->Add(mBitmapBanner, 0, wxEXPAND, 0);
	mHorizontalBannerSizer->AddStretchSpacer(1);

	// Status Bar - Version Info & Mod Count
	mVersionSmapiStext = new wxStaticText(this, wxID_ANY, "SMAPI Version: " + mSettingsPanel->versionSmapi()); // TODO getters/setters
	mModManagerStext = new wxStaticText(this, wxID_ANY, "SDVMM2 Version: " + mSettingsPanel->versionModManager());
	mModCountStext = new wxStaticText(this, wxID_ANY,
		std::to_string(mModCount[ModStatus::loaded]) + "/" + std::to_string(mModCount[ModStatus::total]) + " Mods Loaded");
	mModCountSizer = new wxBoxSizer(wxVERTICAL);
	mModCountSizer->Add(mModCountStext, 0, wxALIGN_RIGHT, 0);
	mVersionSizer = new wxBoxSizer(wxHORIZONTAL);
	mVersionSizer->Add(mModManagerStext, 10, wxEXPAND | wxLEFT, 15);
	mVersionSizer->Add(mVersionSmapiStext, 10, wxEXPAND | wxLEFT, 5);
	mVersionSizer->AddStretchSpacer(10);
	mVersionSizer->Add(mModCountSizer, 5, wxEXPAND | wxRIGHT, 10);

	// Vertical layout
	mMainFrameVerticalSizer = new wxBoxSizer(wxVERTICAL);
	mMainFrameVerticalSizer->Add(mHorizontalBannerSizer, 0, wxEXPAND | wxALL , 10);
	mMainFrameVerticalSizer->Add(mMainFrameHorizontalSizer, 40, wxEXPAND, 0);
	mMainFrameVerticalSizer->Add(mVersionSizer, 0, wxEXPAND, 0); // for static text
	SetSizer(mMainFrameVerticalSizer);

	// Setting background colour as needed
	SetBackgroundColour(wxColour(240, 240, 240, wxALPHA_OPAQUE));

	tryLoadSettings();
}

//-------------------
// MEMBER FUNCTIONS
//-------------------
MainFrame::~MainFrame()
{
}

void MainFrame::tryLoadSettings()
{
	DPRINT("SelfInit - Begin\n");
	wxFileName f(wxStandardPaths::Get().GetExecutablePath());
	fs::path appPath = std::string(wxString(f.GetPath() + wxT("\\SDVMM2.ini")));

	DPRINT("SelfInit - Checking for .ini at:\n" + appPath.string() + "\n");
	mSettingsPanel->configIni = new wxFileConfig(wxEmptyString, wxEmptyString, appPath.string());
	mSettingsPanel->configIni->SetPath("/General");

	if (fs::exists(appPath))
	{
		mSettingsPanel->tryLoadSettings();
	}
	else
	{
		D("SelfInit - No .ini Found\n");
	}
}

//--------------------
// Backend Functions
//--------------------
void MainFrame::mCleanManifest(json& manifest, fs::path error_path) // TODO move check to refresh and make flag
{
	if (!manifest.contains("Name"))
	{
		mErrorChecks[ModErrors::format] = true;
		mErrorChecks[ModErrors::format_local] = true;
		mErrorCount[ModErrors::format]++;
		std::string temp = "";
		if (manifest.contains("name"))
		{
			manifest["name"].get_to(temp);
			manifest["Name"] = temp;
			manifest.erase("name");
		}
		else
		{
			manifest["Name"] = temp;
		}
		DPRINT(error_path.string() + " Manifest Error - Name\n");
	}
	if (!manifest.contains("Author"))
	{
		mErrorChecks[ModErrors::format] = true;
		mErrorChecks[ModErrors::format_local] = true;
		mErrorCount[ModErrors::format]++;
		std::string temp = "";
		if (manifest.contains("author"))
		{
			manifest["author"].get_to(temp);
			manifest["Author"] = temp;
			manifest.erase("author");
		}
		else
		{
			manifest["Author"] = temp;
		}
		DPRINT(error_path.string() + " Manifest Error - Author\n");
	}
	if (!manifest.contains("Version"))
	{
		mErrorChecks[ModErrors::format] = true;
		mErrorChecks[ModErrors::format_local] = true;
		mErrorCount[ModErrors::format]++;
		std::string temp = "";
		if (manifest.contains("version"))
		{
			manifest["version"].get_to(temp);
			manifest["Version"] = temp;
			manifest.erase("version");
		}
		else
		{
			manifest["Version"] = temp;
		}
		DPRINT(error_path.string() + " Manifest Error - Version\n");
	}
	else if (manifest["Version"].is_object())
	{
		// flag outdated version object and make readable
		mErrorChecks[ModErrors::semvar] = true;
		mErrorCount[ModErrors::semvar]++;
		mErrorLocations += "\n" + error_path.string() + " - Depreciated Versioning";
		std::string temp = "";
		int temp_v1 = NULL;
		int temp_v2 = NULL;
		int temp_v3 = NULL;
		manifest["Version"]["MajorVersion"].get_to(temp_v1);
		manifest["Version"]["MinorVersion"].get_to(temp_v2);
		manifest["Version"]["PatchVersion"].get_to(temp_v3);
		temp = std::to_string(temp_v1)
			+ "." + std::to_string(temp_v2)
			+ "." + std::to_string(temp_v3);
		manifest.erase("Version");
		manifest["Version"] = temp;
	}
	if (!manifest.contains("Description"))
	{
		mErrorChecks[ModErrors::format] = true;
		mErrorChecks[ModErrors::format_local] = true;
		mErrorCount[ModErrors::format]++;
		std::string temp = "";
		if (manifest.contains("description"))
		{
			manifest["description"].get_to(temp);
			manifest["Description"] = temp;
			manifest.erase("description");
		}
		else
		{
			manifest["Description"] = temp;
		}
		DPRINT(error_path.string() + " Manifest Error - Description\n");
	}
	if (!manifest.contains("UniqueID"))
	{
		mErrorChecks[ModErrors::format] = true;
		mErrorChecks[ModErrors::format_local] = true;
		mErrorCount[ModErrors::format]++;
		std::string temp = "";
		if (manifest.contains("uniqueID"))
		{
			// if bad case, fix case (more work needed)
		}
		else
		{
			manifest["UniqueID"] = temp;
		}
		DPRINT(error_path.string() + " Manifest Error - UniqueID\n");
	}
	if (mErrorChecks[ModErrors::format_local] == true)
	{
		mModCount[ModStatus::errored]++;
		mErrorLocations += "\n" + error_path.string() + " - Manifest Formatting";
	}
}

void MainFrame::mRefreshModLists()
{
	mResetRefreshErrors();
	wxWindowUpdateLocker noUpdates(mModBrowserPanel->m_dataviewlistctrl_mods);
	mModBrowserPanel->m_dataviewlistctrl_mods->DeleteAllItems();
	try { mLoadModsFromDir("\\Mods\\"); }
	catch (...) {
		wxMessageDialog* error_load_mods = new wxMessageDialog(NULL,
			wxT("Fatal error attempting to refresh active mods."),
			wxT("Refresh Error"), wxOK, wxDefaultPosition);
		error_load_mods->ShowModal();
		delete error_load_mods;
	}
	try { mLoadModsFromDir("\\Mods_disabled\\"); }
	catch (...) {
		wxMessageDialog* error_load_modsd = new wxMessageDialog(NULL,
			wxT("Fatal error attempting to refresh inactive mods."),
			wxT("Refresh Error"), wxOK, wxDefaultPosition);
		error_load_modsd->ShowModal();
		delete error_load_modsd;
	}
	mModBrowserPanel->m_dataviewlistctrl_mods->GetModel()->Resort();
	// Pull out this from the main contructor
	std::string temp_mod = std::to_string(mModCount[ModStatus::loaded]) + "/" +
		std::to_string(mModCount[ModStatus::total]) + " Mods Successfully Loaded";
	mModCountStext->SetLabel(temp_mod);
	mShowRefreshErrors();
}

void MainFrame::mLoadModsFromDir(std::string folder_name)
{
	// TODO group and report errors in scrollable dialogue (bad jsons, incompatible mods, etc.)
	// TODO replace custom ioFunctions with filesystem?
	fs::path temp_dir = (mSettingsPanel->gameDirectory());
	temp_dir += folder_name;
	fs::path temp_path;
	fs::path error_path;
	bool is_active = (folder_name == "\\Mods\\");
	int error_json = 0; // 0 = no error, 1 = bad comma, 2 = other

	DPRINT("mLoadModsFromDir - Begin Iterator at:\n" + mSettingsPanel->gameDirectory().string() + "\n");
	for (auto& dir_iter : fs::recursive_directory_iterator(temp_dir))
	{
		mErrorChecks[ModErrors::json] = false;
		mErrorChecks[ModErrors::format_local] = false;
		error_path = dir_iter.path().filename();
		temp_path = dir_iter.path();
		DPRINTIF(REPORT_MOD_DIRECTORY, temp_path.string() + "\n");
		if (fs::is_directory(temp_path))
		{
			DPRINTIF(REPORT_MOD_DIRECTORY & REPORT_IDENTIFY_DIRECTORIES, " - Is Directory\n");
			temp_path += "\\manifest.json";
			if (fs::exists(temp_path))
			{
				mModCount[ModStatus::total]++;
				ifstream json_stream(temp_path.c_str());
				json json_manifest;
				try
				{
					try
					{ // Parse json
						json_manifest = json::parse(json_stream); // TODO handle trailing commas
						// Handle some minor typos and missing fields in manifest
						mCleanManifest(json_manifest, error_path);
					}
					catch (json::parse_error & e)
					{ // On fail, output error and skip to next mod
						mErrorChecks[ModErrors::json] = true;
						mErrorCount[ModErrors::json]++;
						mModCount[ModStatus::errored]++;
						std::string temp_exc = e.what();
						if (e.id == 101) {
							mErrorLocations += "\n" + error_path.string() + " - JSON Unexpected Char";
							// TODO clean commas and comments, then try again
							///*
							DPRINT("Json Fix Attempt\n");
							//std::stringstream json_sstream;
							//json_sstream << json_stream.rdbuf();
							std::string json_string = "New\n";
							//json_string = json_sstream.str();
							ifstream json_stream2(temp_path.c_str(), std::ios::in | std::ios::binary);
							json_stream2.seekg(0, std::ios::end);
							json_string.resize(json_stream2.tellg());
							json_stream2.seekg(0, std::ios::beg);
							json_stream2.read(&json_string[0], json_string.size());
							json_stream2.close();

							DPRINT("Json Fix RAW\n" + json_string + "\n");

								try
							{
								json_string = stripComments(json_string, true);
							}
							catch (...)
							{
								DPRINT("Json Fix Comment Clean Failure\n");
							}

							DPRINT("Json Fix Comment Cleaned\n" + json_string + "\n");

								try
							{
								json_string = stripTrailingCommas(json_string, true);
							}
							catch (const std::regex_error & e)
							{
								std::string temp = e.what();
								DPRINT("Json Fix Comma Clean Failure: " + temp + "\n");
							}
							//json_sstream.clear();
							//json_sstream.str(string());
							//json_sstream << json_string;

							DPRINT("Json Fix Comma Cleaned\n" + json_string + "\n");

								try
							{
								json_manifest = json::parse(json_string); // TODO handle trailing commas
								// Handle some minor typos and missing fields in manifest
								mCleanManifest(json_manifest, error_path);
								mErrorChecks[ModErrors::json] = false;
								DPRINT("Json Fix Reparse Success\n");
							}
							catch (...)
							{
								DPRINT("Json Fix Reparse Failure\n");
								continue;
							}
							//*/
						}
						else {
							mErrorLocations += "\n" + error_path.string() + " - JSON Formatting";
							continue;
						}
					}

					if (fs::exists(temp_path) and (mErrorChecks[ModErrors::json] == false)) // TODO Review
					{
						DPRINTIF(REPORT_ON_MOD_PARSED, 
							json_manifest["Name"].get<std::string>() + " exists, " 
							+ json_manifest["Version"].get<std::string>() + "\n");

						SmapiMod aMod(json_manifest);
						wxVector<wxVariant> thisMod;
						thisMod.push_back(wxVariant(is_active));
						thisMod.push_back(wxVariant(aMod.name()));
						thisMod.push_back(wxVariant(aMod.author()));
						thisMod.push_back(wxVariant(aMod.version()));
						thisMod.push_back(wxVariant((dir_iter.path()).string()));
						mModBrowserPanel->m_dataviewlistctrl_mods->AppendItem(thisMod);
						mModCount[ModStatus::loaded]++;
						thisMod.clear();

						/*
						wxStringClientData *ldata = new wxStringClientData(wxT("MyID123"));
						m_listCtrl->AppendItem(data, (wxUIntPtr)ldata);

						wxStringClientData *pStrData = (wxStringClientData*) m_listCtrl->GetItemData(m_listCtrl->GetCurrentItem());
							if(!pStrData)
						wxString id = pStrData->GetData();
						*/

						DPRINTIF(REPORT_VERBOSE_MOD_OBJECTS, aMod.infoString());
					}
				}
				catch (...)
				{
					mErrorLocations += "\n" + error_path.string() + " - Fatal";
				}
			}
		}
		else 
		{
			DPRINTIF(REPORT_IDENTIFY_DIRECTORIES, " - Is NOT Directory\n");
		}
	}
}

bool MainFrame::mExistsModFolders()
{
	fs::path mod_path = mSettingsPanel->gameDirectory();
	fs::path mod_d_path = mSettingsPanel->gameDirectory();
	fs::path game_file_path = mSettingsPanel->gameDirectory();
	mod_path += "\\Mods";
	mod_d_path += "\\Mods_disabled";
	game_file_path += "\\Stardew Valley.exe"; // TODO Make crossplatform?

	DPRINT("mExistsModFolders - Begin Checking Mod Folders\n");

	if (!(fs::exists(game_file_path) and fs::is_regular_file(game_file_path)))
	{
		DPRINT("mExistsModFolders - Game Executable not Found on Path:\n"
			+ game_file_path.string() + "\n" + "mExistsModFolders - Bad Game Directory\n");
		return false;
	}
	else
	{
		if (!(fs::exists(mod_path) and fs::is_directory(mod_path)))
		{
			DPRINT("mExistsModFolders - Mods Folder not Found\n");
			fs::create_directory(mod_path);
			DPRINT("mExistsModFolders - Mods Folder Created at:\n" + mod_path.string() + "\n");
		}
		else
		{
			DPRINT("mExistsModFolders - Mods Directory Found on Path:\n" + mod_path.string() + "\n");
		}
		if (!(fs::exists(mod_d_path) and fs::is_directory(mod_d_path)))
		{
			DPRINT("mExistsModFolders - Mods_disabled Folder not Found\n");
			fs::create_directory(mod_d_path);
			DPRINT("mExistsModFolders - Mods_disabled Folder Created at:\n" + mod_d_path.string() + "\n");
		}
		else
		{
			DPRINT("mExistsModFolders - Mods Directory Found on Path:\n" + mod_d_path.string() + "\n");
		}
	}
	return true;
}

void MainFrame::mCheckSmapiVersion()
{
	std::string version = "";
	fs::path path_smapi_logs = std::string(wxStandardPaths::Get().GetUserConfigDir());
	path_smapi_logs += "\\StardewValley\\ErrorLogs\\SMAPI-latest.txt";
	if (fs::exists(path_smapi_logs) and fs::is_regular_file(path_smapi_logs))
	{
		DPRINT("mCheckSmapiVersion - Logs Found\n");
		wxTextFile smapi_logs;
		smapi_logs.Open(wxString(path_smapi_logs));
		wxString temp_string = smapi_logs.GetFirstLine();
		size_t temp_version_start = temp_string.Find("] ") + 8;
		size_t temp_version_end = temp_string.Find(" with Stardew") - 1;
		version = temp_string.SubString(temp_version_start, temp_version_end);
		DPRINT("mCheckSmapiVersion - Version: " + version + "\n");
	}
	else
	{
		DPRINT("mCheckSmapiVersion - No Logs Found\n");
		version = "not found";
	}
	mVersionSmapiStext->SetLabel("SMAPI Version: " + version);
}

void MainFrame::mResetRefreshErrors() 
{
	mErrorLocations = "Errors at: ";
	mErrorChecks[ModErrors::json] = false;
	mErrorChecks[ModErrors::semvar] = false;
	mErrorChecks[ModErrors::format] = false;
	mErrorChecks[ModErrors::format_local] = false;
	mErrorCount[ModErrors::json] = 0;
	mErrorCount[ModErrors::semvar] = 0;
	mErrorCount[ModErrors::format] = 0;
	mModCount[ModStatus::total] = 0;
	mModCount[ModStatus::errored] = 0;
	mModCount[ModStatus::loaded] = 0;
}

void MainFrame::mShowRefreshErrors()
{
	if ((mSettingsPanel->muteErrors["on_refresh"] == false) and
		((mErrorCount[ModErrors::json] != 0) or (mErrorCount[ModErrors::semvar] != 0) or (mErrorCount[ModErrors::format] != 0)))
	{
		// Error counter dialogue prep
		std::string error_mod_loop_title = "Errors in Mods";
		std::string error_mod_loop_message =
			("Manifests with incorrect .json format: " + std::to_string(mErrorCount[ModErrors::json]) +
				"\nManifests with depreciated versioning: " + std::to_string(mErrorCount[ModErrors::semvar]) +
				"\nManifests with other formatting errors: " + std::to_string(mErrorCount[ModErrors::format]));
		// if (!is_active) { final_error_title += "_disabled"; };
		// Error counter dialogue
		wxMessageDialog* error_mod_loop = new wxMessageDialog(NULL,
			error_mod_loop_message, error_mod_loop_title, wxOK, wxDefaultPosition);
		error_mod_loop->ShowModal();
		delete error_mod_loop;
		if (mErrorChecks[ModErrors::semvar]) 
		{
			mErrorLocations += ("\n\nNOTE:\nSMAPI does not load mods with depreciated versioning.\nSee SMAPI logs or console for more details.");
		}
		wxMessageDialog* error_mod_loop_detailed = new wxMessageDialog(NULL,
			mErrorLocations, error_mod_loop_title, wxOK, wxDefaultPosition);
		error_mod_loop_detailed->ShowModal();
		delete error_mod_loop_detailed;
	}
}
