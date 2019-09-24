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