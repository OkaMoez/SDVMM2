#pragma once

#include <wx/wx.h>
#include "cMain.h"

class ModManagerApp : public wxApp
{
public:
	ModManagerApp();

private:
	cMain* m_frame1 = nullptr;
public:
	virtual bool OnInit(); 
};

