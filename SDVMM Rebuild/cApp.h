#pragma once

#include <wx/wx.h>
#include <fstream>
#include <filesystem>
#include <fileapi.h>
#include <algorithm>
#include "cMain.h"
using std::istream;

class cApp : public wxApp
{
public:
	cApp();
	~cApp();

private:
	cMain* m_frame1 = nullptr;

	bool IniExists(cMain* m_frame);

public:
	virtual bool OnInit(); 
};

