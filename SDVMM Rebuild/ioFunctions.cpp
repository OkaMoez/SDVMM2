#include "ioFunctions.h"

string getDirectory(FILE* ini)
{
	char iniBuffer[100];
	fgets(iniBuffer, 100, ini);
	string temp_string = string(iniBuffer);
	size_t temp_pos = temp_string.find('=');
	temp_string = temp_string.substr(temp_pos + 1, temp_string.size());
	temp_string.erase(std::remove(temp_string.begin(), temp_string.end(), '"'), temp_string.end());
	return temp_string;
}

bool existsFile(string file_path)
{
	if (FILE * iniFile = fopen(file_path.c_str(), "r")) {
		fclose(iniFile);
		return true;
	}
	else {
		return false;
	}
}

void formatOldVersion(json& manifest)
{
	string temp_v = "";
	if (manifest.at("Version").is_object())
	{
		int temp_v1 = NULL;
		int temp_v2 = NULL;
		int temp_v3 = NULL;
		manifest["Version"]["MajorVersion"].get_to(temp_v1);
		manifest["Version"]["MinorVersion"].get_to(temp_v2);
		manifest["Version"]["PatchVersion"].get_to(temp_v3);
		temp_v = std::to_string(temp_v1)
			+ "." + std::to_string(temp_v2)
			+ "." + std::to_string(temp_v3);
		manifest.erase("Version");
		manifest["Version"] = temp_v;
	}
	else
		manifest.at("Version").get_to(temp_v);

	D(
		if (report_got_version) {
			wxMessageDialog* m_pBox2 = new wxMessageDialog(NULL,
				("got version: " + temp_v), wxT("File Check"),
				wxOK, wxDefaultPosition);
			m_pBox2->ShowModal();
			delete m_pBox2;
		}
		else {}
	)
}

void refreshModLists(fs::path path_in, wxDataViewListCtrl* mod_list)
{
	wxWindowUpdateLocker noUpdates(mod_list);
	loadModsFromDir(path_in, "\\Mods\\", mod_list);
	loadModsFromDir(path_in, "\\Mods_disabled\\", mod_list);
}

void loadModsFromDir(fs::path path_in, string folder_name, wxDataViewListCtrl* mod_list)
{
	json json_manifest;
	bool is_good_json = false;
	bool is_active = (folder_name == "\\Mods\\");
	fs::path temp_dir = (path_in);
	temp_dir += folder_name;
	fs::path temp_path;
	for (auto& p : fs::directory_iterator(temp_dir))
	{
		is_good_json = false;
		temp_path = p.path();
		temp_path += "\\manifest.json";


		D(
			if (report_looped_path) {
				wxMessageDialog* m_pBox6 = new wxMessageDialog(NULL,
					(temp_path.string()), wxT("Path Check"),
					wxOK, wxDefaultPosition);
				m_pBox6->ShowModal();
				delete m_pBox6;
			}
			else {}
		)

			int json_problem = NULL;
		ifstream json_stream(temp_path.c_str());
		try {
			json_manifest = json::parse(json_stream); // TODO prompt user to handle trailing commas
			is_good_json = true;
		}
		catch (json::parse_error & e) {
			is_good_json = false;
			string temp_exc = e.what();

			if (e.id == 101) { // TODO use exception id
				json_problem = 1;
			}
			else {
				json_problem = 2;
			}

			D(
				if (report_parse_exception) {
					wxMessageDialog* m_pBox2 = new wxMessageDialog(NULL,
						temp_exc, wxT("Exception Report"),
						wxOK, wxDefaultPosition);
					m_pBox2->ShowModal();
					delete m_pBox2;
				}
				else {}
			)

		}

		formatOldVersion(json_manifest);

		if (existsFile(temp_path.string()) and is_good_json == true) // TODO Review
		{
			D(
				if (report_parsed_mod_data) {
					string temp_msg1 = "";
					string temp_msg2 = "";
					json_manifest["Name"].get_to(temp_msg1);
					json_manifest["Version"].get_to(temp_msg2);
					wxMessageDialog* m_pBox2 = new wxMessageDialog(NULL,
						(temp_msg1 + " exists, " + temp_msg2),
						wxT("File Check"), wxOK, wxDefaultPosition);
					m_pBox2->ShowModal();
					delete m_pBox2;
				}
				else {}
			)

			cMod aMod(json_manifest);
			wxVector<wxVariant> thisMod;
			thisMod.push_back(wxVariant(is_active));
			thisMod.push_back(wxVariant(aMod.mod_name()));
			thisMod.push_back(wxVariant(aMod.mod_author()));
			thisMod.push_back(wxVariant(aMod.mod_version()));
			mod_list->AppendItem(thisMod);
			thisMod.clear();

			D(
				if (report_mod_object_data) {
					wxMessageDialog* m_pBox2 = new wxMessageDialog(NULL,
						(aMod.infoString()), wxT("Mod Object"),
						wxOK, wxDefaultPosition);
					m_pBox2->ShowModal();
					delete m_pBox2;
				}
				else {}
			)
		}
		else if (is_good_json == false)
		{
			if (json_problem == 1)
			{
				wxMessageDialog* init_eBox1 = new wxMessageDialog(NULL,
					wxT("Bad Format: Illegal trailing comma at:\n" + temp_path.string()),
					wxT("manifest.json error"),	wxOK, wxDefaultPosition);
				init_eBox1->ShowModal();
				delete init_eBox1;
			}
			else if (json_problem)
			{
				wxMessageDialog* init_eBox2 = new wxMessageDialog(NULL,
					wxT("Bad Format: I dunno yet."), wxT("manifest.json error"),
					wxOK, wxDefaultPosition);
				init_eBox2->ShowModal();
				delete init_eBox2;
			}
			else {}
		}
	}
}

bool existsModFolders(fs::path path_in)
{
	fs::path mod_path = path_in;
	fs::path mod_d_path = path_in;
	fs::path game_file_path = path_in;
	mod_path += "\\Mods";
	mod_d_path += "\\Mods_disabled";
	game_file_path += "\\Stardew Valley.exe"; // TODO Make crossplatform

	if (!(fs::exists(game_file_path) and fs::is_regular_file(game_file_path)))
	{
		D(
			wxMessageDialog * init_mfBox1 = new wxMessageDialog(NULL,
				wxT("Game executable not found on path:\n" + game_file_path.string()),
				wxT("wrong directory"), wxOK, wxDefaultPosition);
			init_mfBox1->ShowModal();
			delete init_mfBox1;
		)
		return false;
	}
	else
	{
		if (!(fs::exists(mod_path) and fs::is_directory(mod_path)))
		{
			fs::create_directory(mod_path);
			D(
				if (report_mod_directories) {
					wxMessageDialog* init_mdBox1 = new wxMessageDialog(NULL,
						mod_path.string(), wxT("Mods Directory Created"),
						wxOK, wxDefaultPosition);
					init_mdBox1->ShowModal();
					delete init_mdBox1;
				}
				else {}
			)
		}
		else
		{
			D(
				if (report_mod_directories) {
					wxMessageDialog* init_mdBox1 = new wxMessageDialog(NULL,
						mod_path.string(), wxT("Mods Directory Found"),
						wxOK, wxDefaultPosition);
					init_mdBox1->ShowModal();
					delete init_mdBox1;
				}
				else {}
			)
		}
		if (!(fs::exists(mod_d_path) and fs::is_directory(mod_d_path)))
		{
			fs::create_directory(mod_d_path);
			D(
				if (report_mod_directories) {
					wxMessageDialog* init_mdBox1 = new wxMessageDialog(NULL,
						mod_d_path.string(), wxT("Mods_d Directory Created"),
						wxOK, wxDefaultPosition);
					init_mdBox1->ShowModal();
					delete init_mdBox1;
				}
				else {}
			)
		}
		else
		{
			D(
				if (report_mod_directories) {
					wxMessageDialog* init_mdBox1 = new wxMessageDialog(NULL,
						mod_d_path.string(), wxT("Mods_d Directory Found"),
						wxOK, wxDefaultPosition);
					init_mdBox1->ShowModal();
					delete init_mdBox1;
				}
				else {}
			)
		}
	}
	return true;
}