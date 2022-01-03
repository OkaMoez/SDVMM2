#include "ModManagerApp.h"

wxIMPLEMENT_APP(ModManagerApp);

ModManagerApp::ModManagerApp()
{

}

bool ModManagerApp::OnInit()
{
	m_frame1 = new MainFrame();
	m_frame1->Show(true);
	// HACK (okamoez): Band-aid fix for intial render issues (flips pages once)
	m_frame1->m_notebook->SetSelection(1);
	m_frame1->m_notebook->SetSelection(0);
	return true;
}