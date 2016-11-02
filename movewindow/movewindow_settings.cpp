#include "movewindow_settings.h"
//
#include <ex_array.h>
//
#include <j_map.h>
//
#include <tclap/CmdLine.h>
//
#include <iostream>
//
#include <tclap/SwitchArg.h>
//
#include <J_Error.h>

using std::cerr; using std::cout; using std::endl; using std::wcerr;
using std::wcout;
using std::string; using std::wstring;


using std::function; using std::bind;
using std::transform; using std::copy;
using std::mem_fn;

using namespace std::placeholders;

using jtl::ex_array; using jtl::j_map;



namespace jomike{



movewindow_settings::movewindow_settings(int argc, char* argv[]){
	try{
		TCLAP::CmdLine command_line("Move Window", ' ', "1.0", true);

#ifdef _DEBUG
		command_line.setExceptionHandling(false);
#endif //_DEBUG
		ex_array<TCLAP::Arg*> dest_position_args;


		TCLAP::SwitchArg left_switch("", "left", "Move To left of Screen", false);

		dest_position_args.push_back(&left_switch);

		TCLAP::SwitchArg right_switch("", "right", "Move To right of Screen", false);

		dest_position_args.push_back(&right_switch);





		TCLAP::ValueArg<std::string>
			parent_window_name_arg("", "parent", "specifies the parent arg", false, "", "string");

		command_line.add(parent_window_name_arg);


		dest_position_args.apply([&](TCLAP::Arg* y_arg){command_line.add(y_arg); });


		TCLAP::UnlabeledValueArg<std::string> window_name_arg("window-name", "Name of window to move", true, "", "string", false);


		command_line.add(window_name_arg);

		TCLAP::ValueArg<long>
			wait_timeout_arg("w", "wait", "Specifies wait timeout", false, 0, "long int");

		command_line.add(wait_timeout_arg);

		command_line.parse(argc, argv);

		if(parent_window_name_arg.isSet()){
			set_parent_window_name(parent_window_name_arg.getValue());
		}


		if(wait_timeout_arg.isSet()){
			set_wait_timeout(wait_timeout_arg.getValue());
		}

		const j_size_t num_args_set
			= std::count_if(dest_position_args.begin(), dest_position_args.end()
				, [](TCLAP::Arg* y_arg){return y_arg->isSet(); });

		if(1 != num_args_set){
			throw J_Error_T(L"Improper number of destination position args. 1 should be set");
		}



		if(left_switch.isSet()){
			M_position_type = Position_Type::LEFT;
		} else if(right_switch.isSet()){
			M_position_type = Position_Type::RIGHT;
		} else{
			throw J_Error_T(L"Could Not Determine Position Type");
		}

		M_window_name = window_name_arg.getValue();


	} catch(TCLAP::ArgException& e){
		cerr << "\n" << e.what();
		return;
	}
}

void movewindow_settings::set_window_name(const std::string& irk_window_name){
	M_window_name = irk_window_name;
}

const std::string& movewindow_settings::window_name()const{
	return M_window_name;
}

void movewindow_settings::set_position_type(const Position_Type& irk_position_type){
	M_position_type = irk_position_type;
}

const jomike::movewindow_settings::Position_Type& movewindow_settings::position_type()const{
	return M_position_type;
}

void movewindow_settings::set_parent_window_name(const std::string& irk_child_window_name){
	M_parent_window_name = irk_child_window_name;
}

const std::string& movewindow_settings::parent_window_name()const{
	return M_parent_window_name;
}

}




