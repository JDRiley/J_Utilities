//
#include <window_management.h>
//
#include "movewindow_settings.h"
//
#include <J_Error.h>
//
//
#include <thread>

//
#include <iostream>

using std::cerr; using std::cout; using std::endl; using std::wcerr;
using std::wcout;

using namespace jtl;

static bool list_windows();

//TODO: Add regexpressing to window names. so you can find windows that match an expression

int main(int argc, char* argv[]){
	try{
		movewindow_settings settings(argc, argv);


		auto start_time = std::chrono::system_clock::now();
		bool do_continue = true;

		while(do_continue){
			bool success = true;
			do_continue = false;
			switch(settings.position_type()){

			case movewindow_settings::Base_Command_Type::LEFT:
				if(!move_window_left(settings.window_name(), settings.parent_window_name())){
					wcerr << "\nCould Not move window, waiting...";
					success = false;
				}
				break;
			case movewindow_settings::Base_Command_Type::RIGHT:
				if(!move_window_right(settings.window_name(), settings.parent_window_name())){
					wcerr << "\nCould Not move window, waiting...";
					success = false;
				}
				break;
			case movewindow_settings::Base_Command_Type::UP:
				assert(!"This position type not implemented");
			case movewindow_settings::Base_Command_Type::DOWN:
				assert(!"This position type not implemented");
			case movewindow_settings::Base_Command_Type::POSITION:
				if(!set_window_pos(
					settings.window_name(), settings.parent_window_name()
					, settings.x_pos(), settings.y_pos())){
					wcerr << "\nCould Not Move window, waiting...";
					success = false;
				}
				break;
			case movewindow_settings::Base_Command_Type::SWITCH_DESKTOP:
				if(!switch_desktop(safe_int_cast(settings.destination_desktop()))){
					throw J_Error_T(L"Could Not switch desktop");
				}
				break;
			case movewindow_settings::Base_Command_Type::LIST_WINDOWS:
				success = list_windows();
				break;
			case movewindow_settings::Base_Command_Type::MAXIMIZE:
				if(!maximize_window(settings.window_name(), settings.parent_window_name())){
					wcerr << "\nCould Not move window, waiting...";
					success = false;
				}
				break;
			default:
				assert(!"This position type not implemented");
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			auto time_running = std::chrono::duration_cast<std::chrono::milliseconds>
				(std::chrono::system_clock::now() - start_time);

			if(time_running.count() < settings.wait_timeout()){
				//only run again if we weren't successful
				do_continue = !success;
			}

			if(!do_continue && !success){
				throw J_Error_T(J_STR("Could Not Complete Task"));
			}


		};

	} catch(J_Error_T& e){
		e.print();
		return 1;
	}





	return 0;
}

bool list_windows(){
	print_all_windows(wcout);
	return true;

}