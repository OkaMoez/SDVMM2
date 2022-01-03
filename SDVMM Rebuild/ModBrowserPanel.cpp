#include "ModBrowserPanel.h"

#include "cMain.h"
#include "SettingsPanel.h"

ModBrowserPanel::ModBrowserPanel(wxWindow* parent, wxWindowID windowID, cMain* parentWindow)
	: wxPanel(parent, windowID)
	, mainWindow(parentWindow)
{
	// Tab 1 - List Control - Creation w/ Columns
	m_dataviewlistctrl_mods = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(465, 200), wxLC_REPORT);
	m_dataviewlistctrl_mods->AppendToggleColumn("Active", wxDATAVIEW_CELL_ACTIVATABLE, 50, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE);
	m_dataviewlistctrl_mods->AppendTextColumn("Name", wxDATAVIEW_CELL_INERT, 200, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE);
	m_dataviewlistctrl_mods->AppendTextColumn("Author", wxDATAVIEW_CELL_INERT, 135, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE);
	m_dataviewlistctrl_mods->AppendTextColumn("Version", wxDATAVIEW_CELL_INERT, 80, wxALIGN_LEFT, 0);
	m_dataviewlistctrl_mods->AppendTextColumn("Location", wxDATAVIEW_CELL_INERT, 500, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE);
	// TODO Either hide scroll bar or hide location data?
	m_dataviewlistctrl_mods->Bind(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, &ModBrowserPanel::OnToggleClick, this);
	m_dataviewlistctrl_mods->Bind(wxEVT_DATAVIEW_COLUMN_HEADER_CLICK, &ModBrowserPanel::OnSortClick, this);

	// Tab 1 - List - Vertical Sizers + Title Text
	m_sizer_notebook_tab1a_mods = new wxBoxSizer(wxVERTICAL);
	m_sizer_notebook_tab1a_mods->AddSpacer(5);
	m_sizer_notebook_tab1a_mods->Add(m_dataviewlistctrl_mods, 1, wxEXPAND, 0);
	m_sizer_notebook_tab1a_mods->AddSpacer(6);

	// Tab 1 - List - Horizontal Sizer
	m_sizer_notebook_tab1a = new wxBoxSizer(wxHORIZONTAL);
	m_sizer_notebook_tab1a->AddSpacer(8);
	m_sizer_notebook_tab1a->Add(m_sizer_notebook_tab1a_mods, 1, wxEXPAND, 0);
	m_sizer_notebook_tab1a->AddSpacer(10);

	// Tab 1 - Top-level Vertical Sizer
	m_sizer_notebook_tab1 = new wxBoxSizer(wxVERTICAL);
	m_sizer_notebook_tab1->AddSpacer(5);
	m_sizer_notebook_tab1->Add(m_sizer_notebook_tab1a, 1, wxEXPAND | wxBOTTOM, 3);
	this->SetSizer(m_sizer_notebook_tab1);
}
// Mod List Buttons
void ModBrowserPanel::OnToggleClick(wxDataViewEvent& event)
{
	event.Skip();

	D(
		if (report_cbox_event) {
			wxMessageDialog* event_toggle_box1 = new wxMessageDialog(NULL,
				wxT("Mod toggled."), wxT("Event captured"),
				wxOK, wxDefaultPosition);
			event_toggle_box1->ShowModal();
			delete event_toggle_box1;
		}
		else {}
	);
	wxVariant temp_path("");
	m_dataviewlistctrl_mods->GetValue(temp_path, m_dataviewlistctrl_mods->GetSelectedRow(), 4);
	fs::path mod_path = string(temp_path);
	fs::path parent_path = mod_path.parent_path();
	fs::path folder_name = mod_path.filename();
	while (parent_path != ((mainWindow->m_settings_panel->game_directory()) += "\\Mods")
		and parent_path != ((mainWindow->m_settings_panel->game_directory()) += "\\Mods_disabled"))
	{

		folder_name = (parent_path.filename() += ("\\" + folder_name.string()));
		parent_path = parent_path.parent_path();
	}


	D(
		OutputDebugString(_T("Mod toggle called.\n"));
	OutputDebugStringA(parent_path.string().c_str());
	OutputDebugString(_T("\n"));
	OutputDebugStringA(folder_name.string().c_str());
	OutputDebugString(_T("\n"));
	);

	if (parent_path == ((mainWindow->m_settings_panel->game_directory()) += "\\Mods"))
	{
		D(
			OutputDebugStringA(mod_path.string().c_str());
			OutputDebugString(_T("\n"));
			OutputDebugStringA((string(mainWindow->m_settings_panel->game_directory().string() += "\\Mods_disabled\\") += folder_name.string()).c_str());
			OutputDebugString(_T("\n"));
		);

		// Build required parent folders for move
		while (!fs::is_directory(((mainWindow->m_settings_panel->game_directory() += "\\Mods_disabled\\") += folder_name).parent_path()))
		{
			fs::path rrename_path = ((mainWindow->m_settings_panel->game_directory() += "\\Mods_disabled\\") += folder_name).parent_path();
			while (!fs::is_directory(rrename_path.parent_path()))
			{
				rrename_path = rrename_path.parent_path();
			}
			fs::create_directory(rrename_path);
		}
		fs::rename(mod_path, (fs::path(mainWindow->m_settings_panel->game_directory() += "\\Mods_disabled\\") += folder_name));

		// Delete empty nested folders
		fs::path clean_path = mod_path.parent_path();
		std::error_code ec;
		while (fs::is_empty(clean_path) and (clean_path != ((mainWindow->m_settings_panel->game_directory()) += "\\Mods")))
		{
			fs::remove(clean_path, ec);
			D(
				OutputDebugString(_T("Empty folder deleted.\n"));
			OutputDebugStringA(clean_path.string().c_str());
			OutputDebugString(_T("\n"));
			);
			clean_path = clean_path.parent_path();
		}
	}
	else if (parent_path == ((mainWindow->m_settings_panel->game_directory()) += "\\Mods_disabled"))
	{
		D(
			OutputDebugStringA(mod_path.string().c_str());
			OutputDebugString(_T("\n"));
			OutputDebugStringA((string(mainWindow->m_settings_panel->game_directory().string() += "\\Mods\\") += folder_name.string()).c_str());
			OutputDebugString(_T("\n"));
		);

		// Build required parent folders for move
		while (!fs::is_directory(((mainWindow->m_settings_panel->game_directory() += "\\Mods\\") += folder_name).parent_path()))
		{
			fs::path rrename_path = ((mainWindow->m_settings_panel->game_directory() += "\\Mods\\") += folder_name).parent_path();
			while (!fs::is_directory(rrename_path.parent_path()))
			{
				rrename_path = rrename_path.parent_path();
			}
			fs::create_directory(rrename_path);
		}

		fs::rename(mod_path, (fs::path(mainWindow->m_settings_panel->game_directory() += "\\Mods\\") += folder_name));

		// Delete empty nested folders
		fs::path clean_path = mod_path.parent_path();
		std::error_code ec;
		while (fs::is_empty(clean_path) and (clean_path != ((mainWindow->m_settings_panel->game_directory()) += "\\Mods_disabled")))
		{
			fs::remove(clean_path, ec);
			D(
				OutputDebugString(_T("Empty folder deleted.\n"));
				OutputDebugStringA(clean_path.string().c_str());
				OutputDebugString(_T("\n"));
			);
			clean_path = clean_path.parent_path();
		}
	}
	else
	{
		D(
			if (report_file_move_event) {
				wxMessageDialog* event_toggle_ebox1 = new wxMessageDialog(NULL,
					wxT("Bad path"), wxT("Event item info"),
					wxOK, wxDefaultPosition);
				event_toggle_ebox1->ShowModal();
				delete event_toggle_ebox1;
			}
			else {}
		);
	}
	mainWindow->RefreshModLists();
}

void ModBrowserPanel::OnSortClick(wxDataViewEvent& event)
{
	const unsigned idx = event.GetColumn();

	D(
		OutputDebugString(_T("OnSortClick Event - Col "));
	OutputDebugStringA(std::to_string(idx).c_str());
	)

		// default handling for the column click is to sort by this column or
		// toggle its sort order
		wxDataViewColumn* const col = m_dataviewlistctrl_mods->GetColumn(idx);
	if (!col->IsSortable())
	{
		D(
			OutputDebugString(_T(" - Not Sortable\n"));
		)
			// no default handling for non-sortable columns
			event.Skip();
		return;
	}

	if (col->IsSortKey())
	{
		// already acending order, just change the order
		D(
			OutputDebugString(_T(" - Old"));
		)
			col->ToggleSortOrder();
	}
	else // not using this column for sorting yet
	{
		for (int i = 0; i < 5; i++)
		{
			if (m_dataviewlistctrl_mods->GetColumn(i)->IsSortKey())
			{
				m_dataviewlistctrl_mods->GetColumn(i)->UnsetAsSortKey();
			}
		}
		col->SetSortOrder(false);
		D(
			OutputDebugString(_T(" - New"));
		)
	}

	wxDataViewModel* const model = m_dataviewlistctrl_mods->GetModel();
	if (model)
		model->Resort();

	m_dataviewlistctrl_mods->OnColumnChange(idx);
	D(
		OutputDebugString(_T(" - Sorted\n"));
	)
}

