#pragma once
#include <wx/wx.h>

#include "neargye/semver.hpp"

class MainFrame;

class StatusBar : public wxStatusBar {
public:
	StatusBar(MainFrame* parent
		, wxWindowID windowID
		, semver::version smapiVersion = semver::version{}
		, semver::version modManagerVersion = semver::version{}
		, long style = wxSTB_DEFAULT_STYLE);
	
	void setSmapiVersion(semver::version version);
	void setModManagerVersion(semver::version version);
	void setModLoadingStatus(int total, int loaded);

private:

	enum FieldIndex {
		smapiVersion,
		modManagerVersion,
		modLoadingStatus
	};

	MainFrame* _mMainWindow = nullptr;

	semver::version _mSmapiVersion;
	semver::version _mModManagerVersion; // TODO: not being set? fix it
	int _mModsTotal = 0;
	int _mModsLoaded = 0;
};
