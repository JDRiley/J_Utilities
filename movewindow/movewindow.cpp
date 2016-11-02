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

int main(int argc, char* argv[]){
	try{
		movewindow_settings settings(argc, argv);


		auto start_time = std::chrono::system_clock::now();

		switch(settings.position_type()){

		case jomike::movewindow_settings::Position_Type::LEFT:
			while(!move_window_left(settings.window_name(), settings.parent_window_name())){
				wcerr << "\nCould Not move window, waiting...";
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				
				auto time_running = std::chrono::duration_cast<std::chrono::milliseconds>
					(std::chrono::system_clock::now() - start_time);

				if(time_running.count() > settings.wait_timeout()){
					throw J_Error_T(L"Could Not Move Window");
				}
				
			}
			break;
		case jomike::movewindow_settings::Position_Type::RIGHT:
			while(!move_window_right(settings.window_name(), settings.parent_window_name())){
				wcerr << "\nCould Not move window, waiting...";
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

				auto time_running = std::chrono::duration_cast<std::chrono::milliseconds>
					(std::chrono::system_clock::now() - start_time);

				if(time_running.count() > settings.wait_timeout()){
					throw J_Error_T(L"Could Not Move Window");
				}

			}
			break;
		case jomike::movewindow_settings::Position_Type::UP:
			assert(!"This position type not implemented");
		case jomike::movewindow_settings::Position_Type::DOWN:
			assert(!"This position type not implemented");
		case jomike::movewindow_settings::Position_Type::POSITION:
			assert(!"This position type not implemented");
		default:
			assert(!"This position type not implemented");
		}


		

	} catch(J_Error_T& e){
		e.print();
		return 1;
	}





	return 0;
}