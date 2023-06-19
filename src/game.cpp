#include "../include/game.hpp"
#include "../include/player_pair.hpp"
#include "../include/global.hpp"
#include "../include/color.hpp"
#include <iostream>

void c4::game()
{
	color::colored_str::color_prompt();
	clear_console();
	player_pair player_pair = player_pair::init();
	wait_for_input();
}
