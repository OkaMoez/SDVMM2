#include "MainFrame.h"

#include "LauncherButtonPanel.h"
#include "MenuBar.h"
#include "ModBrowserPanel.h"
#include "SettingsPanel.h"

#include "strip.h"

MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Stardew Valley Mod Manager 2",
	wxDefaultPosition, wxSize(750, 500),
	wxDEFAULT_FRAME_STYLE)
{
	SetMinSize(wxSize(750, 500));

	//---------------------------
	//  Notebook Implementation
	//---------------------------
	m_notebook = new wxNotebook(this, -1);

	m_mod_browser_panel = new ModBrowserPanel(m_notebook, wxID_ANY, this);
	m_notebook->AddPage(m_mod_browser_panel, "SMAPI Mods", true);

	m_settings_panel = new SettingsPanel(m_notebook, wxID_ANY, this);
	m_notebook->AddPage(m_settings_panel, "Settings", false);

	//---------------------------------
	//  Additional GUI Implementation
	//---------------------------------

	// Launcher buttons
	m_launcher_panel = new LauncherButtonPanel(this, wxID_ANY, this);

	// Horizontal layout
	m_sizer_main_horizontal = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_main_horizontal->Add(m_notebook, 2, wxEXPAND | wxLEFT | wxRIGHT, 10);
	m_sizer_main_horizontal->Add(m_launcher_panel, 1, wxEXPAND | wxRIGHT, 10);

	// Menubar - File, Help, etc
	m_menubar = new MenuBar(this);
	SetMenuBar(m_menubar);

	// Title banner
	wxImage::AddHandler(new wxPNGHandler);
	m_bitmap_banner = new wxStaticBitmap(this, wxID_ANY, wxBitmap("SDVMM2.png", wxBITMAP_TYPE_PNG)); // TODO save in code?
	wxImage::CleanUpHandlers();
	m_sizer_banner_horizontal = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_banner_horizontal->Add(m_bitmap_banner, 0, wxEXPAND, 0);
	m_sizer_banner_horizontal->AddStretchSpacer(1);

	// Status Bar - Version Info & Mod Count
	m_stext_smapi_version = new wxStaticText(this, wxID_ANY, "SMAPI Version: " + m_settings_panel->version_smapi()); // TODO getters/setters
	m_stext_this_version = new wxStaticText(this, wxID_ANY, "SDVMM2 Version: " + m_settings_panel->version_this_mm());
	m_stext_mod_count = new wxStaticText(this, wxID_ANY,
		std::to_string(mod_count_[mod_status::loaded]) + "/" + std::to_string(mod_count_[mod_status::total]) + " Mods Loaded");
	m_sizer_mod_count = new wxBoxSizer(wxVERTICAL);
	m_sizer_mod_count->Add(m_stext_mod_count, 0, wxALIGN_RIGHT, 0);
	m_sizer_version_info = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_version_info->Add(m_stext_this_version, 10, wxEXPAND | wxLEFT, 15);
	m_sizer_version_info->Add(m_stext_smapi_version, 10, wxEXPAND | wxLEFT, 5);
	m_sizer_version_info->AddStretchSpacer(10);
	m_sizer_version_info->Add(m_sizer_mod_count, 5, wxEXPAND | wxRIGHT, 10);

	// Vertical layout
	m_sizer_main_vertical = new wxBoxSizer(wxVERTICAL);
	m_sizer_main_vertical->Add(m_sizer_banner_horizontal, 0, wxEXPAND | wxALL , 10);
	m_sizer_main_vertical->Add(m_sizer_main_horizontal, 40, wxEXPAND, 0);
	m_sizer_main_vertical->Add(m_sizer_version_info, 0, wxEXPAND, 0); // for static text
	SetSizer(m_sizer_main_vertical);

	// Setting background colour as needed
	SetBackgroundColour(wxColour(240, 240, 240, wxALPHA_OPAQUE));

	SelfInitialize();
}

//-------------------
// MEMBER FUNCTIONS
//-------------------
MainFrame::~MainFrame()
{
}

void MainFrame::SelfInitialize()
{
	DPRINT("SelfInit - Begin\n");
	wxFileName f(wxStandardPaths::Get().GetExecutablePath());
	fs::path appPath = string(wxString(f.GetPath() + wxT("\\SDVMM2.ini")));

	DPRINT("SelfInit - Checking for .ini at:\n" + appPath.string() + "\n");
	m_settings_panel->config_ini = new wxFileConfig(wxEmptyString, wxEmptyString, appPath.string());
	m_settings_panel->config_ini->SetPath("/General");

	if (fs::exists(appPath))
	{
		m_settings_panel->SelfInitialize();
	}
	else
	{
		D("SelfInit - No .ini Found\n");
	}
}

//--------------------
// Backend Functions
//--------------------
void MainFrame::CleanManifest(json& manifest, fs::path error_path) // TODO move check to refresh and make flag
{
	if (!manifest.contains("Name"))
	{
		error_check_[mod_errors::format] = true;
		error_check_[mod_errors::format_local] = true;
		error_count_[mod_errors::format]++;
		string temp = "";
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
		error_check_[mod_errors::format] = true;
		error_check_[mod_errors::format_local] = true;
		error_count_[mod_errors::format]++;
		string temp = "";
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
		error_check_[mod_errors::format] = true;
		error_check_[mod_errors::format_local] = true;
		error_count_[mod_errors::format]++;
		string temp = "";
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
		error_check_[mod_errors::semvar] = true;
		error_count_[mod_errors::semvar]++;
		error_locations_ += "\n" + error_path.string() + " - Depreciated Versioning";
		string temp = "";
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
		error_check_[mod_errors::format] = true;
		error_check_[mod_errors::format_local] = true;
		error_count_[mod_errors::format]++;
		string temp = "";
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
		error_check_[mod_errors::format] = true;
		error_check_[mod_errors::format_local] = true;
		error_count_[mod_errors::format]++;
		string temp = "";
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
	if (error_check_[mod_errors::format_local] == true)
	{
		mod_count_[mod_status::errored]++;
		error_locations_ += "\n" + error_path.string() + " - Manifest Formatting";
	}
}

void MainFrame::RefreshModLists()
{
	ResetRefreshErrors();
	wxWindowUpdateLocker noUpdates(m_mod_browser_panel->m_dataviewlistctrl_mods);
	m_mod_browser_panel->m_dataviewlistctrl_mods->DeleteAllItems();
	try { LoadModsFromDir("\\Mods\\"); }
	catch (...) {
		wxMessageDialog* error_load_mods = new wxMessageDialog(NULL,
			wxT("Fatal error attempting to refresh active mods."),
			wxT("Refresh Error"), wxOK, wxDefaultPosition);
		error_load_mods->ShowModal();
		delete error_load_mods;
	}
	try { LoadModsFromDir("\\Mods_disabled\\"); }
	catch (...) {
		wxMessageDialog* error_load_modsd = new wxMessageDialog(NULL,
			wxT("Fatal error attempting to refresh inactive mods."),
			wxT("Refresh Error"), wxOK, wxDefaultPosition);
		error_load_modsd->ShowModal();
		delete error_load_modsd;
	}
	m_mod_browser_panel->m_dataviewlistctrl_mods->GetModel()->Resort();
	// Pull out this from the main contructor
	string temp_mod = std::to_string(mod_count_[mod_status::loaded]) + "/" +
		std::to_string(mod_count_[mod_status::total]) + " Mods Successfully Loaded";
	m_stext_mod_count->SetLabel(temp_mod);
	ShowRefreshErrors();
}

void MainFrame::LoadModsFromDir(string folder_name) 
{
	// TODO group and report errors in scrollable dialogue (bad jsons, incompatible mods, etc.)
	// TODO replace custom ioFunctions with filesystem?
	fs::path temp_dir = (m_settings_panel->game_directory());
	temp_dir += folder_name;
	fs::path temp_path;
	fs::path error_path;
	bool is_active = (folder_name == "\\Mods\\");
	int error_json = 0; // 0 = no error, 1 = bad comma, 2 = other

	DPRINT("LoadModsFromDir - Begin Iterator at:\n" + m_settings_panel->game_directory().string() + "\n");
	for (auto& dir_iter : fs::recursive_directory_iterator(temp_dir))
	{
		error_check_[mod_errors::json] = false;
		error_check_[mod_errors::format_local] = false;
		error_path = dir_iter.path().filename();
		temp_path = dir_iter.path();
		DPRINTIF(report_mod_directory, temp_path.string() + "\n");
		if (fs::is_directory(temp_path))
		{
			DPRINTIF(report_mod_directory & report_identify_directories, " - Is Directory\n");
			temp_path += "\\manifest.json";
			if (fs::exists(temp_path))
			{
				mod_count_[mod_status::total]++;
				ifstream json_stream(temp_path.c_str());
				json json_manifest;
				try
				{
					try
					{ // Parse json
						json_manifest = json::parse(json_stream); // TODO handle trailing commas
						// Handle some minor typos and missing fields in manifest
						CleanManifest(json_manifest, error_path);
					}
					catch (json::parse_error & e)
					{ // On fail, output error and skip to next mod
						error_check_[mod_errors::json] = true;
						error_count_[mod_errors::json]++;
						mod_count_[mod_status::errored]++;
						string temp_exc = e.what();
						if (e.id == 101) {
							error_locations_ += "\n" + error_path.string() + " - JSON Unexpected Char";
							// TODO clean commas and comments, then try again
							///*
							DPRINT("Json Fix Attempt\n");
							//std::stringstream json_sstream;
							//json_sstream << json_stream.rdbuf();
							string json_string = "New\n";
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
								string temp = e.what();
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
								CleanManifest(json_manifest, error_path);
								error_check_[mod_errors::json] = false;
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
							error_locations_ += "\n" + error_path.string() + " - JSON Formatting";
							continue;
						}
					}

					if (fs::exists(temp_path) and (error_check_[mod_errors::json] == false)) // TODO Review
					{
						DPRINTIF(report_on_mod_parsed, 
							json_manifest["Name"].get<std::string>() + " exists, " 
							+ json_manifest["Version"].get<std::string>() + "\n");

						cMod aMod(json_manifest);
						wxVector<wxVariant> thisMod;
						thisMod.push_back(wxVariant(is_active));
						thisMod.push_back(wxVariant(aMod.mod_name()));
						thisMod.push_back(wxVariant(aMod.mod_author()));
						thisMod.push_back(wxVariant(aMod.mod_version()));
						thisMod.push_back(wxVariant((dir_iter.path()).string()));
						m_mod_browser_panel->m_dataviewlistctrl_mods->AppendItem(thisMod);
						mod_count_[mod_status::loaded]++;
						thisMod.clear();

						/*
						wxStringClientData *ldata = new wxStringClientData(wxT("MyID123"));
						m_listCtrl->AppendItem(data, (wxUIntPtr)ldata);

						wxStringClientData *pStrData = (wxStringClientData*) m_listCtrl->GetItemData(m_listCtrl->GetCurrentItem());
							if(!pStrData)
						wxString id = pStrData->GetData();
						*/

						DPRINTIF(report_verbose_mod_object_data, aMod.infoString());
					}
				}
				catch (...)
				{
					error_locations_ += "\n" + error_path.string() + " - Fatal";
				}
			}
		}
		else 
		{
			DPRINTIF(report_identify_directories, " - Is NOT Directory\n");
		}
	}
}

bool MainFrame::ExistsModFolders()
{
	fs::path mod_path = m_settings_panel->game_directory();
	fs::path mod_d_path = m_settings_panel->game_directory();
	fs::path game_file_path = m_settings_panel->game_directory();
	mod_path += "\\Mods";
	mod_d_path += "\\Mods_disabled";
	game_file_path += "\\Stardew Valley.exe"; // TODO Make crossplatform?

	DPRINT("ExistsModFolders - Begin Checking Mod Folders\n");

	if (!(fs::exists(game_file_path) and fs::is_regular_file(game_file_path)))
	{
		DPRINT("ExistsModFolders - Game Executable not Found on Path:\n"
			+ game_file_path.string() + "\n" + "ExistsModFolders - Bad Game Directory\n");
		return false;
	}
	else
	{
		if (!(fs::exists(mod_path) and fs::is_directory(mod_path)))
		{
			DPRINT("ExistsModFolders - Mods Folder not Found\n");
			fs::create_directory(mod_path);
			DPRINT("ExistsModFolders - Mods Folder Created at:\n" + mod_path.string() + "\n");
		}
		else
		{
			DPRINT("ExistsModFolders - Mods Directory Found on Path:\n" + mod_path.string() + "\n");
		}
		if (!(fs::exists(mod_d_path) and fs::is_directory(mod_d_path)))
		{
			DPRINT("ExistsModFolders - Mods_disabled Folder not Found\n");
			fs::create_directory(mod_d_path);
			DPRINT("ExistsModFolders - Mods_disabled Folder Created at:\n" + mod_d_path.string() + "\n");
		}
		else
		{
			DPRINT("ExistsModFolders - Mods Directory Found on Path:\n" + mod_d_path.string() + "\n");
		}
	}
	return true;
}

void MainFrame::CheckSmapiVersion()
{
	string version = "";
	fs::path path_smapi_logs = string(wxStandardPaths::Get().GetUserConfigDir());
	path_smapi_logs += "\\StardewValley\\ErrorLogs\\SMAPI-latest.txt";
	if (fs::exists(path_smapi_logs) and fs::is_regular_file(path_smapi_logs))
	{
		DPRINT("CheckSmapiVersion - Logs Found\n");
		wxTextFile smapi_logs;
		smapi_logs.Open(wxString(path_smapi_logs));
		wxString temp_string = smapi_logs.GetFirstLine();
		size_t temp_version_start = temp_string.Find("] ") + 8;
		size_t temp_version_end = temp_string.Find(" with Stardew") - 1;
		version = temp_string.SubString(temp_version_start, temp_version_end);
		DPRINT("CheckSmapiVersion - Version: " + version + "\n");
	}
	else
	{
		DPRINT("CheckSmapiVersion - No Logs Found\n");
		version = "not found";
	}
	m_stext_smapi_version->SetLabel("SMAPI Version: " + version);
}

void MainFrame::ResetRefreshErrors() 
{
	error_locations_ = "Errors at: ";
	error_check_[mod_errors::json] = false;
	error_check_[mod_errors::semvar] = false;
	error_check_[mod_errors::format] = false;
	error_check_[mod_errors::format_local] = false;
	error_count_[mod_errors::json] = 0;
	error_count_[mod_errors::semvar] = 0;
	error_count_[mod_errors::format] = 0;
	mod_count_[mod_status::total] = 0;
	mod_count_[mod_status::errored] = 0;
	mod_count_[mod_status::loaded] = 0;
}

void MainFrame::ShowRefreshErrors()
{
	if ((m_settings_panel->error_mute_["on_refresh"] == false) and
		((error_count_[mod_errors::json] != 0) or (error_count_[mod_errors::semvar] != 0) or (error_count_[mod_errors::format] != 0)))
	{
		// Error counter dialogue prep
		string error_mod_loop_title = "Errors in Mods";
		string error_mod_loop_message =
			("Manifests with incorrect .json format: " + std::to_string(error_count_[mod_errors::json]) +
				"\nManifests with depreciated versioning: " + std::to_string(error_count_[mod_errors::semvar]) +
				"\nManifests with other formatting errors: " + std::to_string(error_count_[mod_errors::format]));
		// if (!is_active) { final_error_title += "_disabled"; };
		// Error counter dialogue
		wxMessageDialog* error_mod_loop = new wxMessageDialog(NULL,
			error_mod_loop_message, error_mod_loop_title, wxOK, wxDefaultPosition);
		error_mod_loop->ShowModal();
		delete error_mod_loop;
		if (error_check_[mod_errors::semvar]) 
		{
			error_locations_ += "\n[SMAPI does not load mods with depreciated versioning.]";
		}
		wxMessageDialog* error_mod_loop_detailed = new wxMessageDialog(NULL,
			error_locations_, error_mod_loop_title, wxOK, wxDefaultPosition);
		error_mod_loop_detailed->ShowModal();
		delete error_mod_loop_detailed;
	}
}
