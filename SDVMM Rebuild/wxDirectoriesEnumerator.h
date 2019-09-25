#pragma once

#include <string>
#include <wx/dir.h>

// Found at:
// https://stackoverflow.com/questions/20655601/wxwidgets-write-all-folders-into-a-listbox/20667534

class myDirectoriesEnumerator : public wxDirTraverser {
public:
	wxArrayString* dirs;
	myDirectoriesEnumerator(wxArrayString* dirs_) { dirs = dirs_; }
	virtual wxDirTraverseResult OnFile(const wxString& filename) { return wxDIR_CONTINUE; }
	virtual wxDirTraverseResult OnDir(const wxString& dirname) { dirs->Add(dirname); return wxDIR_IGNORE; }
};