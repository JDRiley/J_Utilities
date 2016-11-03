#ifndef MOVEWINDOW_SETTINGS_H
#define MOVEWINDOW_SETTINGS_H

#include "J_Fwd_Decl.h"


namespace jomike{


class movewindow_settings{
public:
	movewindow_settings(int argc, char* argv[]);

	void set_window_name(const std::string& irk_window_name);
	
	
	const std::string& window_name()const;
	enum class Position_Type{
		LEFT, RIGHT, UP, DOWN, POSITION, SWITCH_DESKTOP, ERROR
	};


	void set_position_type(const Position_Type& irk_position_type);
	
	
	const Position_Type& position_type()const;

	void set_parent_window_name(const std::string& irk_child_window_name);
	
	
	const std::string& parent_window_name()const;

	void set_wait_timeout(const j_llint& irk_wait_timeout){
		M_wait_timeout = irk_wait_timeout;
	}
	
	
	const j_llint& wait_timeout()const{
		return M_wait_timeout;
	}


	void set_destination_desktop(const j_llint& irk_destination_desktop){
		M_destination_desktop = irk_destination_desktop;
	}
	
	
	const j_llint& destination_desktop()const{
		return M_destination_desktop;
	}

private:
	std::string M_window_name;
	std::string M_parent_window_name;
	j_llint M_destination_desktop = 0;
	j_llint M_wait_timeout = 0;

	Position_Type M_position_type = Position_Type::ERROR;
};



}

#endif //MOVEWINDOW_SETTINGS_H


