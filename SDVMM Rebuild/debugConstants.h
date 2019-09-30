#pragma once
// Define R for reports, and Q for quiet
//#define myLOUD
#ifdef myLOUD
#define myREPORT(x) x
#define myQUIET(y)
#else
#define myREPORT(x)
#define myQUIET(y) y
#endif


// Individual Debug Toggles
// cApp
const bool report_mode = true;

myREPORT(
	const bool report_ini_exists = true;
	const bool report_game_directory = true;
	const bool report_filepath = false;
	const bool report_json_name = false;
	const bool report_looped_path = false;
	const bool report_parse_exception = false;
	const bool report_got_version = false;
	const bool report_version_exception = false;
	const bool report_parsed_mod_data = false;
	const bool report_mod_object_data = false;
	const bool report_mod_directories = false;
	const bool report_cbox_event = false;
	const bool report_file_move_event = false;
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
	const bool report_parsed_mod_data = false;
	const bool report_mod_object_data = false;
	const bool report_mod_directories = false;
	const bool report_cbox_event = false;
	const bool report_file_move_event = false;
)
