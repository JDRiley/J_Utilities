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



void validate_position_args(TCLAP::ValueArg<long>& irk_x_pos, TCLAP::ValueArg<long>& irk_y_pos);

movewindow_settings::movewindow_settings(int argc, char* argv[]){
	try{
		TCLAP::CmdLine command_line("Move Window", ' ', "1.0", true);

#ifdef _DEBUG
		command_line.setExceptionHandling(false);
#endif //_DEBUG
		ex_array<TCLAP::Arg*> base_command_args;


		TCLAP::SwitchArg left_switch("", "left", "Move To left of Screen", false);
		base_command_args.push_back(&left_switch);

		TCLAP::SwitchArg right_switch("", "right", "Move To right of Screen", false);
		base_command_args.push_back(&right_switch);

		TCLAP::SwitchArg pos_switch("", "pos", "Move to pos, requires -x and -y args", false);
		base_command_args.push_back(&pos_switch);

		TCLAP::SwitchArg
			maximize_switch("", "maximize", "switches to specified desktop", false);
		base_command_args.push_back(&maximize_switch);
		
		
		TCLAP::SwitchArg list_windows_switch("", "list-windows", "list Windows", false);
		base_command_args.push_back(&list_windows_switch);

		TCLAP::ValueArg<long>
			destination_desktop_arg("", "switch-to-desktop", "switches to specified desktop", false, 0, "long int");
		base_command_args.push_back(&destination_desktop_arg);

		TCLAP::SwitchArg show_mouse_loc_switch("", "show-mouse-location", "Shows mouse location. Clicking ends program.", false);
		base_command_args.push_back(&show_mouse_loc_switch);

		base_command_args.apply([&](TCLAP::Arg* y_arg){command_line.add(y_arg); });




		TCLAP::ValueArg<std::string>
			parent_window_name_arg("", "parent", "specifies the parent arg", false, "", "string");

		command_line.add(parent_window_name_arg);




		TCLAP::UnlabeledValueArg<std::string> window_name_arg("window-name", "Name of window to move", false, "", "string", false);


		command_line.add(window_name_arg);

		TCLAP::ValueArg<long>
			wait_timeout_arg("w", "wait", "Specifies wait timeout", false, 0, "long int");

		command_line.add(wait_timeout_arg);

	
		TCLAP::ValueArg<long>
			x_pos_arg("x", "x-pos", "Specifies X Pos", false, 0, "Long int");

		command_line.add(x_pos_arg);

		TCLAP::ValueArg<long>
			y_pos_arg("y", "y-pos", "Specifies Y Pos", false, 0, "Long int");


		command_line.add(y_pos_arg);

		

		command_line.parse(argc, argv);


		if(destination_desktop_arg.isSet()){
			M_destination_desktop = destination_desktop_arg.getValue();
			M_base_command = Base_Command_Type::SWITCH_DESKTOP;
		}

		if (show_mouse_loc_switch.isSet()) {
			M_base_command = Base_Command_Type::SHOW_MOUSE_LOCATION;
		}

		if(parent_window_name_arg.isSet()){
			set_parent_window_name(parent_window_name_arg.getValue());
		}


		if(wait_timeout_arg.isSet()){
			set_wait_timeout(wait_timeout_arg.getValue());
		}

		const j_size_t num_args_set
			= std::count_if(base_command_args.begin(), base_command_args.end()
				, [](TCLAP::Arg* y_arg){return y_arg->isSet(); });

		if(1 != num_args_set){
			throw J_Error_T(L"Improper number of work args. 1 should be set");
		}


		if(Base_Command_Type::ERROR != M_base_command){
			//nothing
		}else if(left_switch.isSet()){
			M_base_command = Base_Command_Type::LEFT;
		} else if(right_switch.isSet()){
			M_base_command = Base_Command_Type::RIGHT;
		} else if(pos_switch.isSet()){
			M_base_command = Base_Command_Type::POSITION;
			validate_position_args(x_pos_arg, y_pos_arg);
			set_x_pos(x_pos_arg.getValue());
			set_y_pos(y_pos_arg.getValue());
		}else if(list_windows_switch.isSet()){
			M_base_command = Base_Command_Type::LIST_WINDOWS;
		} else if(maximize_switch.isSet()){
			M_base_command = Base_Command_Type::MAXIMIZE;
		}else{
			throw J_Error_T(L"Could Not Determine Position Type");
		}

		M_window_name = window_name_arg.getValue();


	} catch(TCLAP::ArgException& e){
		cerr << "\n" << e.what();
		return;
	}
}

void validate_position_args(TCLAP::ValueArg<long>& irk_x_pos, TCLAP::ValueArg<long>& irk_y_pos){
	if(!irk_x_pos.isSet()){
		throw J_Error_T(J_STR("X_Pos Not Set. need -x switch"));
	}
	if(!irk_y_pos.isSet()){
		throw J_Error_T(J_STR("Y_Pos Not Set. need -y switch"));
	}

}

void movewindow_settings::set_window_name(const std::string& irk_window_name){
	M_window_name = irk_window_name;
}

const std::string& movewindow_settings::window_name()const{
	return M_window_name;
}

void movewindow_settings::set_position_type(const Base_Command_Type& irk_position_type){
	M_base_command = irk_position_type;
}

const jomike::movewindow_settings::Base_Command_Type& movewindow_settings::position_type()const{
	return M_base_command;
}

void movewindow_settings::set_parent_window_name(const std::string& irk_child_window_name){
	M_parent_window_name = irk_child_window_name;
}

const std::string& movewindow_settings::parent_window_name()const{
	return M_parent_window_name;
}

}




