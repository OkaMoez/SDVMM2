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
	if (!IniExists(m_frame1))
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

bool cApp::IniExists(cMain* m_frame)
{
	string iniName = "SDVMM2.ini";
	char iniBuffer[100];
	if (FILE* iniFile = fopen(iniName.c_str(), "r")) {
		fgets(iniBuffer, 100, iniFile);
		string temp_string = string(iniBuffer);
		size_t temp_pos = temp_string.find('=');
		temp_string = temp_string.substr(temp_pos+1,temp_string.size());
		temp_string.erase(std::remove(temp_string.begin(), temp_string.end(), '"'), temp_string.end());
		string iniString = temp_string;
		m_frame->set_gamepath(temp_string);
		fclose(iniFile);
		return true;
	}
	else {
		return false;
	}
}