#include "ModManagerApp.h"

wxIMPLEMENT_APP(ModManagerApp);

ModManagerApp::ModManagerApp() {

}

bool ModManagerApp::OnInit() {
	_mMainFrame = new MainFrame();
	_mMainFrame->Show(true);
	// HACK (okamoez): Band-aid fix for intial render issues (flips pages once)
	_mMainFrame->mTabbedNotebook->SetSelection(1);
	_mMainFrame->mTabbedNotebook->SetSelection(0);
	return true;
}