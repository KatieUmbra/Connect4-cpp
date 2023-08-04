#pragma once
#include "player.hpp"
#include "player_pair.hpp"
#include "scores.hpp"
#include "board.hpp"

namespace c4
{
	void run_game();

	void init();

	void game(player_pair& players);

	auto input_prompt(player& plr, board& p_board) -> std::pair<int, int>;

	void main_loop(player_pair& players, board& p_board);

	auto scores_handler(score p_score) -> std::array<score, 5>;
}
