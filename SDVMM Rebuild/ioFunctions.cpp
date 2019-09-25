#ifdef _DEBUG 
#define D(x) x
#include "debugConstants.h"
#else 
#define D(x)
#endif

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

bool fileExists(string file_name)
{
	if (FILE * iniFile = fopen(file_name.c_str(), "r")) {
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
	try {
		if (manifest.at("Version").is_object()) { throw std::exception("obj not str"); }
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
	catch (std::exception & e) {
		string temp_exc = e.what();
		D(
			if (report_version_exception) {
				wxMessageDialog* m_pBox2 = new wxMessageDialog(NULL,
					temp_exc, wxT("Exception Report"),
					wxOK, wxDefaultPosition);
				m_pBox2->ShowModal();
				delete m_pBox2;
			}
			else {}
		)

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
}

void printDir(wxListBox* ListBox1, fs::path modDir)
{
	string temp_path = modDir.string();
	wxArrayString dirList;
	myDirectoriesEnumerator traverser(&dirList);
	wxDir dir(temp_path);
	if (dir.IsOpened()) 
	{
		dir.Traverse(traverser);
		ListBox1->Clear();
		for (unsigned int i = 0; i < dirList.GetCount(); i++) {
			//The name is what follows the last \ or /
			ListBox1->Append(dirList.Item(i).AfterLast('\\').AfterLast('/'));
		}
	}
}

void loadModsFromDir(fs::path path_in, wxDataViewListCtrl* mod_list)
{
	fs::path temp_dir = (path_in);
	temp_dir += "\\Mods";
	fs::path temp_path = temp_dir;
	fs::path temp_stop = temp_dir;
	temp_dir += "\\";

	json json_manifest;
	mod_list->Freeze();
	for (auto& p : fs::directory_iterator(temp_dir))
	{

		temp_path = p.path();
		temp_path += "\\manifest.json";

		/*
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
		*/

		ifstream i(temp_path.c_str());
		try {
			json_manifest = json::parse(i); // TODO prompt user to handle trailing commas
		}
		catch (std::exception& e) {
			string temp_exc = e.what();
			/*
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
			*/
		}

		formatOldVersion(json_manifest);

		if (fileExists(temp_path.string()))
		{
			/*
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
			*/

			cMod aMod(json_manifest);
			wxVector<wxVariant> thisMod;
			thisMod.push_back(wxVariant(true));
			thisMod.push_back(wxVariant(aMod.mod_name()));
			thisMod.push_back(wxVariant(aMod.mod_author()));
			thisMod.push_back(wxVariant(aMod.mod_version()));
			mod_list->AppendItem(thisMod);
			/*
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
			*/

			//cMod* test_mod = new cMod(json_manifest);
			//delete test_mod;
		}
	}
	mod_list->Thaw();
}