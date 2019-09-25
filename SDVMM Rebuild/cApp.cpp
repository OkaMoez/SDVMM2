#ifdef _DEBUG 
#define D(x) x
#include "debugConstants.h"
#else 
#define D(x)
#endif

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
		D(
			if (report_ini_exists) {
				wxMessageDialog* m_pBox1 = new wxMessageDialog(NULL,
					wxT("No .ini file was found."), wxT("INI Not Found"),
					wxOK, wxDefaultPosition);
				m_pBox1->ShowModal();
				delete m_pBox1;
			}
			else {}
		)
	}
	else
	{
		string myPath = m_frame1->gamepath();
		D(
			if (report_game_directory) {
				wxMessageDialog* m_pBox1 = new wxMessageDialog(NULL,
					myPath, wxT("Game Directory"),
					wxOK, wxDefaultPosition);
				m_pBox1->ShowModal();
				delete m_pBox1;
			}
			else {}
		)
	}

	fs::path temp_path = m_frame1->gamepath();
	temp_path += "\\Mods\\";
	//printDir(m_frame1->m_list_activeMods, temp_path);
	m_frame1->Show(true);
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

				ifstream i(temp_path.c_str());
				try {
					json_manifest = json::parse(i); // TODO prompt user to handle trailing commas
				}
				catch (std::exception & e) {
					string temp_exc = e.what();
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

				if (fileExists(temp_path.string()))
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
					D(
						if (report_mod_object_data) {
							wxMessageDialog* m_pBox2 = new wxMessageDialog(NULL,
								(aMod.infoString()),
								wxT("Mod Object"), wxOK, wxDefaultPosition);
							m_pBox2->ShowModal();
							delete m_pBox2;
						}
						else {}
					)

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