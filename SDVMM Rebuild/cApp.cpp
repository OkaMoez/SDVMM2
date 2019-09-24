#include "cApp.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{

}

cApp::~cApp()
{

}

bool cApp::OnInit()
{
	m_frame1 = new cMain();
	m_frame1->Show(true);
	if (!StartCheck(m_frame1))
	{
		wxMessageDialog* m_pBox1 = new wxMessageDialog(NULL,
			wxT("No .ini file was found."), wxT("File Not Found"),
			wxOK, wxDefaultPosition);
		m_pBox1->ShowModal();
		delete m_pBox1;
	}
	else
	{
		string myPath = m_frame1->gamepath();
		wxMessageDialog* m_pBox1 = new wxMessageDialog(NULL,
			myPath, wxT("Game Location"),
			wxOK, wxDefaultPosition);
		m_pBox1->ShowModal();
		delete m_pBox1;
	}

	return true;
}

bool cApp::StartCheck(cMain* m_frame)
{
	string file_name = "SDVMM2.ini";
	if (fileExists(file_name))
	{
		if (FILE * iniFile = fopen(file_name.c_str(), "r")) {
			m_frame->set_gamepath(getDirectory(iniFile));
			fs::path temp_path = (m_frame->gamepath());
			temp_path += "\\Mods";
			//temp_path += "\\AutoGate\\manifest.json";
			
			json json_manifest;
			for (auto& p : fs::directory_iterator(temp_path))
			{
				temp_path = p.path();
				temp_path += "\\manifest.json";

				ifstream i(temp_path);
				try {
					json_manifest = json::parse(i);
				}
				catch (json::type_error& e) {
					std::cerr << e.what() << std::endl;
				}
				if (fileExists(temp_path.string()))
				{
					wxMessageDialog* m_pBox2 = new wxMessageDialog(NULL, //test
						(string(json_manifest["Name"]) + " exists"), wxT("File Check"),
						wxOK, wxDefaultPosition);
					m_pBox2->ShowModal();
					delete m_pBox2;

					cMod* test_mod = new cMod(json_manifest);
					delete test_mod;
				}
			}
			fclose(iniFile);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}