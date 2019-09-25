#pragma once

#include <wx/wx.h>
#include <fstream>
#include <iomanip>
#include <fileapi.h>
#include <algorithm>
#include "ioFunctions.h"
using std::istream;
using std::ifstream;

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

