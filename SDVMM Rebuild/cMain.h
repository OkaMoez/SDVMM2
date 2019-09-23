#pragma once

#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include <wx/listctrl.h>
#include <string>


class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	wxMenuBar* menubar;
	wxMenu* file;
	wxMenu* help;

	// Right side buttons
	wxButton* m_btn_launchSMAPI = nullptr;
	wxButton* m_btn_launchSDV = nullptr;
	wxButton* m_btn_addMod = nullptr;
	wxButton* m_btn_dlMod = nullptr;
	wxButton* m_btn_delMod = nullptr;

	// Left default tab 
	wxListBox* m_list_activeMods = nullptr;
	wxListBox* m_list_inactiveMods = nullptr;
	wxButton* m_btn_openAMods = nullptr;
	wxButton* m_btn_openIMods = nullptr;
	wxButton* m_btn_refreshMods = nullptr;


	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

