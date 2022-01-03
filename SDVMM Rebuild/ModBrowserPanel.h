#pragma once
#include <wx/wx.h>
#include <wx/dataview.h>

class MainFrame;

class ModBrowserPanel : public wxPanel
{
public:
	ModBrowserPanel(wxWindow* parent, wxWindowID windowID, MainFrame* parentWindow);

	wxDataViewListCtrl* m_dataviewlistctrl_mods = nullptr;

private:
	MainFrame* mainWindow = nullptr;

	// Mod List Buttons
	void OnToggleClick(wxDataViewEvent& event);
	void OnSortClick(wxDataViewEvent& event);
	wxBoxSizer* m_sizer_notebook_tab1a_mods = nullptr;
	wxBoxSizer* m_sizer_notebook_tab1 = nullptr;
	wxBoxSizer* m_sizer_notebook_tab1a = nullptr;
	wxBoxSizer* m_sizer_notebook_tab1b = nullptr;
};