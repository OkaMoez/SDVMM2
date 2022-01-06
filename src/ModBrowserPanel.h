#pragma once
#include <wx/wx.h>
#include <wx/dataview.h>

class MainFrame;

class ModBrowserPanel : public wxPanel
{
public:
	ModBrowserPanel(MainFrame* main, wxWindow* parent, wxWindowID windowID);

	wxDataViewListCtrl* mModBrowserDataviewlistctrl = nullptr;

private:
	MainFrame* _mMainWindow = nullptr;

	// Mod List Buttons
	void OnToggleClick(wxDataViewEvent& event);
	void OnSortClick(wxDataViewEvent& event);
	wxBoxSizer* _mModBrowserSizer = nullptr;
	wxBoxSizer* _mModBrowserHorizontalSizer = nullptr;
	wxBoxSizer* _mModBrowserVerticalSizer = nullptr;
};