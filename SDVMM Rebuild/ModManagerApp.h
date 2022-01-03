#pragma once

#include <wx/wx.h>
#include "MainFrame.h"

class ModManagerApp : public wxApp
{
public:
	ModManagerApp();

private:
	MainFrame* m_frame1 = nullptr;
public:
	virtual bool OnInit(); 
};

