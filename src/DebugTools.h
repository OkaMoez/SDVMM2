#pragma once
#ifdef _DEBUG 
#include <windows.h>
#include <wx/string.h>
#define D(x) x
#define DPRINT(x, ...) OutputDebugString(wxString(x))
#define DPRINTIF(x, y) if(x){OutputDebugString(wxString(y));}

// Define R for reports, and Q for quiet
#define myLOUD
#ifdef myLOUD
#define myREPORT(x) x
#define myQUIET(y)
#else
#define D(x) x
#define DPRINT(x, ...)
#define DPRINTIF(x, y)
#define myREPORT(x)
#define myQUIET(y) y
#endif

// Individual Debug Toggles
myREPORT(
	const bool REPORT_INI_EXISTS = false;
	const bool REPORT_GAME_DIRECTORY = false;
	const bool REPORT_FILEPATH = false;

	const bool REPORT_JSON_PATH = false;
	const bool REPORT_LOOPED_PATH = false;
	const bool REPORT_PARSE_EXCEPTION = false;
	const bool REPORT_GOT_VERSION = false;
	const bool REPORT_VERSION_EXCEPTION = false;

	const bool REPORT_MOD_DIRECTORY = false;
	const bool REPORT_IDENTIFY_DIRECTORIES = false;
	const bool REPORT_JSON_FIX = false;
	const bool REPORT_ON_MOD_PARSED = true;
	const bool REPORT_VERBOSE_MOD_OBJECTS = false;
	const bool REPORT_MOD_DIRECTORIES = true;
	const bool REPORT_CBOX_EVENTS = false;
	const bool REPORT_FILE_MOVE_EVENT = false;
	const bool REPORT_LAUNCHER_CBOX_EVENT = true;
)

myQUIET(
	const bool REPORT_INI_EXISTS = false;
	const bool REPORT_GAME_DIRECTORY = false;
	const bool REPORT_FILEPATH = false;

	const bool REPORT_JSON_PATH = false;
	const bool REPORT_LOOPED_PATH = false;
	const bool REPORT_PARSE_EXCEPTION = true;
	const bool REPORT_GOT_VERSION = false;
	const bool REPORT_VERSION_EXCEPTION = false;

	const bool REPORT_MOD_DIRECTORY = true;
	const bool REPORT_IDENTIFY_DIRECTORIES = false;
	const bool REPORT_JSON_FIX = false;
	const bool REPORT_ON_MOD_PARSED = false;
	const bool REPORT_VERBOSE_MOD_OBJECTS = false;
	const bool REPORT_MOD_DIRECTORIES = false;
	const bool REPORT_CBOX_EVENTS = false;
	const bool REPORT_FILE_MOVE_EVENT = false;
	const bool REPORT_LAUNCHER_CBOX_EVENT = false;
)

#else 
#define D(x)
#endif
