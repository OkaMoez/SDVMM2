#pragma once

#include <wx/wx.h>
#include <wx/dataview.h>

class SettingsPanel : public wxPanel {

	SettingsPanel(wxWindow* parent, wxWindowID windowID);

	// Tab 3 - Launcher Option
	wxStaticText* m_stext_launcher = nullptr;
	wxCheckBox* m_checkbox_launcher = nullptr;
	wxBoxSizer* m_sizer_notebook_tab3_launcher = nullptr;
	// Tab 3 - Game Directory
	wxStaticText* m_stext_game_directory = nullptr;
	wxTextCtrl* m_textctrl_game_directory = nullptr;
	wxDirDialog* m_dirdialog_game_browse = nullptr;
	wxButton* m_button_game_directory_save = nullptr;
	wxButton* m_button_game_directory_browse = nullptr;
	wxBoxSizer* m_sizer_notebook_tab3_game_directory = nullptr;
	// Tab 3 - Steam Directory
	wxStaticText* m_stext_steam_directory = nullptr;
	wxTextCtrl* m_textctrl_steam_directory = nullptr;
	wxFileDialog* m_filedialog_steam_browse = nullptr;
	wxButton* m_button_steam_directory_save = nullptr;
	wxButton* m_button_steam_directory_browse = nullptr;
	wxBoxSizer* m_sizer_notebook_tab3_steam_directory = nullptr;
	// Tab 3 - Error Mute Option
	wxStaticText* m_stext_mute = nullptr;
	wxCheckBox* m_checkbox_mute = nullptr;
	wxBoxSizer* m_sizer_notebook_tab3_mute = nullptr;
	// Tab 3 - Layout
	wxBoxSizer* m_sizer_notebook_tab3_items = nullptr;
	wxBoxSizer* m_sizer_notebook_tab3_left = nullptr;
	wxBoxSizer* m_sizer_notebook_tab3_right = nullptr;
	wxBoxSizer* m_sizer_notebook_tab3 = nullptr;
};
