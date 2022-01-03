#pragma once
#ifdef _DEBUG 
#include <wx/string.h>
#include "debugConstants.h"
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
	const bool report_ini_exists = false;
	const bool report_game_directory = false;
	const bool report_filepath = false;

	const bool report_json_name = false;
	const bool report_looped_path = false;
	const bool report_parse_exception = false;
	const bool report_got_version = false;
	const bool report_version_exception = false;

	const bool report_mod_directory = false;
	const bool report_identify_directories = false;
	const bool report_on_mod_parsed = true;
	const bool report_verbose_mod_object_data = false;
	const bool report_mod_directories = true;
	const bool report_cbox_event = false;
	const bool report_file_move_event = false;
	const bool report_launcher_cbox_event = true;
)

myQUIET(
	const bool report_ini_exists = false;
	const bool report_game_directory = false;
	const bool report_filepath = false;

	const bool report_json_name = false;
	const bool report_looped_path = false;
	const bool report_parse_exception = true;
	const bool report_got_version = false;
	const bool report_version_exception = false;

	const bool report_mod_directory = true;
	const bool report_identify_directories = false;
	const bool report_on_mod_parsed = false;
	const bool report_verbose_mod_object_data = false;
	const bool report_mod_directories = false;
	const bool report_cbox_event = false;
	const bool report_file_move_event = false;
	const bool report_launcher_cbox_event = false;
)

#else 
#define D(x)
#endif
