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
			fclose(iniFile);

			fs::path temp_dir = (m_frame->gamepath());
			temp_dir += "\\Mods";
			fs::path temp_path = temp_dir;
			fs::path temp_stop = temp_dir +="\\";
			
			json json_manifest;
			for (auto& p : fs::directory_iterator(temp_dir))
			{
				
				temp_path = p.path();
				temp_path += "\\manifest.json";
				
				/*
				wxMessageDialog* m_pBox6 = new wxMessageDialog(NULL, //test
					(temp_path.string()), wxT("Path Check"),
					wxOK, wxDefaultPosition);
				m_pBox6->ShowModal();
				delete m_pBox6;
				*/

				ifstream i(temp_path.c_str());
				try {
					json_manifest = json::parse(i); // TODO prompt user to handle trailing commas
				}
				catch (std::exception& e) {
					string temp_exc = e.what();

					wxMessageDialog* m_pBox2 = new wxMessageDialog(NULL, //test
						temp_exc, wxT("Exception Report"),
						wxOK, wxDefaultPosition);
					m_pBox2->ShowModal();
					delete m_pBox2;
				}

				string temp_v = "";
				try {
					if (json_manifest.at("Version").is_object()) { throw std::exception("obj not str"); }
					else
					json_manifest.at("Version").get_to(temp_v);

					/*
					wxMessageDialog* m_pBox2 = new wxMessageDialog(NULL, //test
						temp_v, wxT("File Check"),
						wxOK, wxDefaultPosition);
					m_pBox2->ShowModal();
					delete m_pBox2;
					*/
				}
				catch (std::exception& e) {
					string temp_exc = e.what();

					
					wxMessageDialog* m_pBox2 = new wxMessageDialog(NULL, //test
						temp_exc, wxT("Exception Report"),
						wxOK, wxDefaultPosition);
					m_pBox2->ShowModal();
					delete m_pBox2;
					

					int temp_v1 = NULL;
					int temp_v2 = NULL;
					int temp_v3 = NULL;
					json_manifest["Version"]["MajorVersion"].get_to(temp_v1);
					json_manifest["Version"]["MinorVersion"].get_to(temp_v2);
					json_manifest["Version"]["PatchVersion"].get_to(temp_v3);
					temp_v = std::to_string(temp_v1) 
						+ "." + std::to_string(temp_v2)
						+ "." + std::to_string(temp_v3);
					json_manifest.erase("Version");
					json_manifest["Version"] = temp_v;
				}

				if (fileExists(temp_path.string()))
				{
					string temp_msg1 = "";
					string temp_msg2 = "";
					json_manifest["Name"].get_to(temp_msg1);
					json_manifest["Version"].get_to(temp_msg2);
					wxMessageDialog* m_pBox2 = new wxMessageDialog(NULL, //test
						(temp_msg1 + " exists, " + temp_msg2),
						wxT("File Check"), wxOK, wxDefaultPosition);
					m_pBox2->ShowModal();
					delete m_pBox2;

					//cMod* test_mod = new cMod(json_manifest);
					//delete test_mod;
				}
			}
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