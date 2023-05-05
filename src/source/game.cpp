#include "game.hpp"
#include "player_pair.hpp"
#include "global.hpp"
#include "color.hpp"

void c4::game()
{
	color::colored_str::color_prompt();
	clear_console();
	player_pair player_pair = player_pair::init();
	wait_for_input();
}
