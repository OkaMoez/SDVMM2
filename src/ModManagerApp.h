#pragma once

#include <wx/wx.h>
#include "MainFrame.h"

class ModManagerApp : public wxApp
{
public:
	ModManagerApp();

private:
	MainFrame* _mMainFrame = nullptr;
public:
	virtual bool OnInit(); 
};

