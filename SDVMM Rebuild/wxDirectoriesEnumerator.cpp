#include "wxDirectoriesEnumerator.h"

// Found at:
// https://stackoverflow.com/questions/20655601/wxwidgets-write-all-folders-into-a-listbox/20667534

class wxDirectoriesEnumerator : public wxDirTraverser {
public:
	wxArrayString* dirs;
	wxDirectoriesEnumerator(wxArrayString* dirs_) {
		dirs = dirs_;
	}
	//This function will be called when a file is found
	virtual wxDirTraverseResult OnFile(const wxString& filename) {
		//Do nothing, continue with the next file or directory
		return wxDIR_CONTINUE;
	}
	//This function will be called when a directory is found
	virtual wxDirTraverseResult OnDir(const wxString& dirname) {
		//Add the directory to the results
		dirs->Add(dirname);
		//Do NOT enter this directory
		return wxDIR_IGNORE;
	}
};