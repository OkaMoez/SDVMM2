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
		, long style = 65840L);
	
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
	semver::version _mModManagerVersion;
	int _mModsTotal = 0;
	int _mModsLoaded = 0;
};
