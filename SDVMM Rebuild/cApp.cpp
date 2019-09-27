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
	m_frame1->Show(true);
	return true;
}

bool cApp::StartCheck(cMain* m_frame)
{
	string ini_name = "SDVMM2.ini";
	if (existsFile(ini_name))
	{
		if (FILE* iniFile = fopen(ini_name.c_str(), "r")) {
			m_frame->set_gamepath(GetIniDirectory(iniFile));
			fclose(iniFile);
			if (m_frame->ExistsModFolders())
			{
				m_frame->RefreshModLists();
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