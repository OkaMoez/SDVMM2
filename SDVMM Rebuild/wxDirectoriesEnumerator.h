#pragma once
#include <wx/dir.h>

class wxDirectoriesEnumerator : public wxDirTraverser {
public:
	wxArrayString* dirs;
	wxDirectoriesEnumerator(wxArrayString* dirs_);
	virtual wxDirTraverseResult OnFile(const wxString& filename);
	virtual wxDirTraverseResult OnDir(const wxString& dirname);
};