#include "ModBrowserPanel.h"

#include "MainFrame.h"
#include "ManifestParser.h"
#include "SettingsPanel.h"
#include <wx/listctrl.h>

ModBrowserPanel::ModBrowserPanel(MainFrame* main, wxWindow* parent, wxWindowID windowID)
	: wxPanel(parent, windowID)
	, _mMainWindow(main) {
	// Tab 1 - List Control - Creation w/ Columns
	mModBrowserDataviewlistctrl = new wxDataViewListCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(465, 200), wxLC_REPORT);
	mModBrowserDataviewlistctrl->AppendToggleColumn("Active", wxDATAVIEW_CELL_ACTIVATABLE, 50, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE);
	mModBrowserDataviewlistctrl->AppendTextColumn("Name", wxDATAVIEW_CELL_INERT, 200, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE);
	mModBrowserDataviewlistctrl->AppendTextColumn("Author", wxDATAVIEW_CELL_INERT, 135, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE);
	mModBrowserDataviewlistctrl->AppendTextColumn("Version", wxDATAVIEW_CELL_INERT, 80, wxALIGN_LEFT, 0);
	mModBrowserDataviewlistctrl->AppendTextColumn("Location", wxDATAVIEW_CELL_INERT, 500, wxALIGN_LEFT, wxDATAVIEW_COL_SORTABLE);
	// TODO Either hide scroll bar or hide location data?
	mModBrowserDataviewlistctrl->Bind(wxEVT_DATAVIEW_ITEM_VALUE_CHANGED, &ModBrowserPanel::OnToggleClick, this);
	mModBrowserDataviewlistctrl->Bind(wxEVT_DATAVIEW_COLUMN_HEADER_CLICK, &ModBrowserPanel::OnSortClick, this);

	// Tab 1 - List - Vertical Sizers + Title Text
	_mModBrowserSizer = new wxBoxSizer(wxVERTICAL);
	_mModBrowserSizer->AddSpacer(5);
	_mModBrowserSizer->Add(mModBrowserDataviewlistctrl, 1, wxEXPAND, 0);
	_mModBrowserSizer->AddSpacer(6);

	// Tab 1 - List - Horizontal Sizer
	_mModBrowserHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
	_mModBrowserHorizontalSizer->AddSpacer(8);
	_mModBrowserHorizontalSizer->Add(_mModBrowserSizer, 1, wxEXPAND, 0);
	_mModBrowserHorizontalSizer->AddSpacer(10);

	// Tab 1 - Top-level Vertical Sizer
	_mModBrowserVerticalSizer = new wxBoxSizer(wxVERTICAL);
	_mModBrowserVerticalSizer->AddSpacer(5);
	_mModBrowserVerticalSizer->Add(_mModBrowserHorizontalSizer, 1, wxEXPAND | wxBOTTOM, 3);
	this->SetSizer(_mModBrowserVerticalSizer);
}
// Mod List Buttons
void ModBrowserPanel::OnToggleClick(wxDataViewEvent& event) {
	DPRINTIF(REPORT_CBOX_EVENTS, "Event captured - Mod toggled.\n");
	event.Skip();

	wxVariant tempPath("");
	mModBrowserDataviewlistctrl->GetValue(tempPath, mModBrowserDataviewlistctrl->GetSelectedRow(), 4);
	fs::path modPath = std::string(tempPath);
	fs::path parentPath = modPath.parent_path();
	fs::path folderName = modPath.filename();
	while (parentPath != ((_mMainWindow->mSettingsPanel->gameDirectory()) += "\\Mods")
		and parentPath != ((_mMainWindow->mSettingsPanel->gameDirectory()) += "\\Mods_disabled")) {

		folderName = (parentPath.filename() += ("\\" + folderName.string()));
		parentPath = parentPath.parent_path();
	}

	DPRINT("Mod toggle called.\n" + parentPath.string() + "\n" + folderName.string() + "\n");

	if (parentPath == ((_mMainWindow->mSettingsPanel->gameDirectory()) += "\\Mods")) {
		DPRINT(modPath.string() + "\n" + _mMainWindow->mSettingsPanel->gameDirectory().string() 
			+ "\\Mods_disabled\\" + folderName.string() + "\n");

		// Build required parent folders for move
		while (!fs::is_directory(((_mMainWindow->mSettingsPanel->gameDirectory() += "\\Mods_disabled\\") += folderName).parent_path())) {
			fs::path renamePath = ((_mMainWindow->mSettingsPanel->gameDirectory() += "\\Mods_disabled\\") += folderName).parent_path();
			while (!fs::is_directory(renamePath.parent_path())) {
				renamePath = renamePath.parent_path();
			}
			fs::create_directory(renamePath);
		}
		fs::rename(modPath, (fs::path(_mMainWindow->mSettingsPanel->gameDirectory() += "\\Mods_disabled\\") += folderName));

		// Delete empty nested folders
		fs::path cleanPath = modPath.parent_path();
		std::error_code ec;
		while (fs::is_empty(cleanPath) and (cleanPath != ((_mMainWindow->mSettingsPanel->gameDirectory()) += "\\Mods"))) {
			fs::remove(cleanPath, ec);
			DPRINT("Empty folder deleted.\n" + cleanPath.string() + "\n");
			cleanPath = cleanPath.parent_path();
		}
	}
	else if (parentPath == ((_mMainWindow->mSettingsPanel->gameDirectory()) += "\\Mods_disabled")) {
		DPRINT(modPath.string() + "\n" + _mMainWindow->mSettingsPanel->gameDirectory().string() + "\\Mods\\" + folderName.string() + "\n");

		// Build required parent folders for move
		while (!fs::is_directory(((_mMainWindow->mSettingsPanel->gameDirectory() += "\\Mods\\") += folderName).parent_path())) {
			fs::path renamePath = ((_mMainWindow->mSettingsPanel->gameDirectory() += "\\Mods\\") += folderName).parent_path();
			while (!fs::is_directory(renamePath.parent_path())) {
				renamePath = renamePath.parent_path();
			}
			fs::create_directory(renamePath);
		}

		fs::rename(modPath, (fs::path(_mMainWindow->mSettingsPanel->gameDirectory() += "\\Mods\\") += folderName));

		// Delete empty nested folders
		fs::path cleanPath = modPath.parent_path();
		std::error_code ec;
		while (fs::is_empty(cleanPath) and (cleanPath != ((_mMainWindow->mSettingsPanel->gameDirectory()) += "\\Mods_disabled"))) {
			fs::remove(cleanPath, ec);
			DPRINT("Empty folder deleted.\n" + cleanPath.string() + "\n");
			cleanPath = cleanPath.parent_path();
		}
	}
	else {
		DPRINTIF(REPORT_FILE_MOVE_EVENT, "Event item info - Bad path.\n");
	}
	_mMainWindow->mManifestParser->refreshModLists();
}

void ModBrowserPanel::OnSortClick(wxDataViewEvent& event) {
	const unsigned idx = event.GetColumn();

	DPRINT("OnSortClick Event - Col " + std::to_string(idx));

		// default handling for the column click is to sort by this column or
		// toggle its sort order
		wxDataViewColumn* const col = mModBrowserDataviewlistctrl->GetColumn(idx);
	if (!col->IsSortable()) {
		DPRINT(" - Not Sortable\n");
			// no default handling for non-sortable columns
			event.Skip();
		return;
	}

	if (col->IsSortKey()) {
		// already acending order, just change the order
		DPRINT(" - Old");
			col->ToggleSortOrder();
	}
	else { // not using this column for sorting yet
		for (int i = 0; i < 5; i++) {
			if (mModBrowserDataviewlistctrl->GetColumn(i)->IsSortKey()) {
				mModBrowserDataviewlistctrl->GetColumn(i)->UnsetAsSortKey();
			}
		}
		col->SetSortOrder(false);
		DPRINT(" - New");
	}

	wxDataViewModel* const model = mModBrowserDataviewlistctrl->GetModel();
	if (model) {
		model->Resort();
	}

	mModBrowserDataviewlistctrl->OnColumnChange(idx);
	DPRINT(" - Sorted\n");
}

