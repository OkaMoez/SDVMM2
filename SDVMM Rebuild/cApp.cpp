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
	// Band-aid fix for intial render issues (flips pages once)
	m_frame1->m_notebook->SetSelection(1);
	m_frame1->m_notebook->SetSelection(0);
	return true;
}