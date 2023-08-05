#pragma once
#include "game.hpp"
#include "cell.hpp"
#include "global.hpp"
#include "color.hpp"
#include "token.hpp"
#include "player.hpp"
#include "player_pair.hpp"
#include "scores.hpp"
#include "board.hpp"
#include "pch.hpp"
#include "figlet.hpp"

namespace c4
{
	void run_game();
	
	void init();
	
	void game();
	
	auto input_prompt(player& plr, board& p_board) -> std::pair<int, int>;
	
	auto main_loop(player_pair& players, board& p_board) -> bool;
	
	auto scores_handler(score&& p_score) -> std::array<score, 5>;
	
	void print_scores(std::array<score, 5>&& scores);
	
	void intro();
}
