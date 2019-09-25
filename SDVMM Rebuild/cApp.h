#pragma once

#include <wx/wx.h>
#include <algorithm>
#include "ioFunctions.h"

class cApp : public wxApp
{
public:
	cApp();
	~cApp();

private:
	cMain* m_frame1 = nullptr;

	bool StartCheck(cMain* m_frame);

public:
	virtual bool OnInit(); 
};

