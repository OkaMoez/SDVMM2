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
	m_frame1->mTabbedNotebook->SetSelection(1);
	m_frame1->mTabbedNotebook->SetSelection(0);
	return true;
}