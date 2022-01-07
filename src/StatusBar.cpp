#include "StatusBar.h"

#include "MainFrame.h"

StatusBar::StatusBar(MainFrame* parent
	, wxWindowID windowID
	, semver::version smapiVersion /* = semver::version{} */
	, semver::version modManagerVersion /* = semver::version{} */
	, long style /* = wxSTB_DEFAULT_STYLE */)
	: wxStatusBar(parent, windowID, style)
	, _mMainWindow(parent) {
	SetFieldsCount(3);
	setSmapiVersion(smapiVersion);
	setModManagerVersion(modManagerVersion);
}

void StatusBar::setSmapiVersion(semver::version version) {
	std::string smapiVersionText = "SMAPI Version: " + version.to_string();
	SetStatusText(smapiVersionText, FieldIndex::smapiVersion);
}

void StatusBar::setModManagerVersion(semver::version version) {
	std::string modManagerVersionText = "SDVMM2 Version: " + version.to_string();
	SetStatusText(modManagerVersionText, FieldIndex::modManagerVersion);
}

void StatusBar::setModLoadingStatus(int total, int loaded) {
	std::string modLoadingStatusText = std::to_string(loaded) + "/" + std::to_string(total) + " Mods Loaded";
	SetStatusText(modLoadingStatusText, FieldIndex::modLoadingStatus);
}
