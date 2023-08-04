#include "game.hpp"
#include "board.hpp"
#include "cell.hpp"
#include "player_pair.hpp"
#include "global.hpp"
#include "color.hpp"
#include "token.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <string_view>

#define val const auto
#define var auto

void c4::init()
{
	color::colored_str::color_prompt();
	clear_console();
	var player_pair = player_pair::init();
	wait_for_input();
	game(player_pair);
};

void c4::game(c4::player_pair& players)
{
	board m_board{6, 8};
	main_loop(players, m_board);
}

auto c4::input_prompt(player& plr, board& p_board) -> std::pair<int, int>
{
	std::shared_ptr<color::colored_str> color;
	if(plr.token() == "X")
	{
		std::shared_ptr<color::colored_str> x_color = std::make_shared<color::colored_str>(color::const_colors::Red);
		color = x_color;
	}
	else
	{
		std::shared_ptr<color::colored_str> o_color = std::make_shared<color::colored_str>(color::const_colors::Green);
		color = o_color;
	}
	std::cout
	<< "Hello "
	<< color->colorize_str(plr.name().c_str())
	<< ", You're playing with the "
	<< color->colorize_str(plr.token().c_str())
	<< " token."
	<< '\n';

	std::cout << "Please introduce the number of the column where you will place your token." << '\n';

	std::pair position = {0, 0};
	while(true)
	{
		auto column = 0;
		std::cin >> column;
		column--;
		auto result = p_board.place_in_column(column, plr.token() == "X" ? cell_content::X : cell_content::O);
		if(result.first)
		{
			position = result.second;
			break;
		}
		std::cout << column << " is full or is out of bounds, try again." << std::endl;
	}
	return position;
}

auto c4::scores_handler(score p_score) -> std::array<score, 5>
{
	if(is_scores_file_valid().first == 0) { write_empty_scores_file(); }
	auto stored_scores = load_scores_from_file();
	insert_score_into_array(stored_scores, p_score);
	save_scores_to_file(stored_scores);
	return stored_scores;
}

void c4::main_loop(player_pair& players, board& p_board)
{
	var score = 0;
	var has_player_won = false;
	var current_player = 0;
	while(!has_player_won)
	{
		auto plr = players[current_player];
		auto tk = plr.get_token_enum() == c4::token::X ? c4::cell_content::X : c4::cell_content::O;
		clear_console();
		p_board.print_board();
		auto inserted_pos = input_prompt(plr, p_board);
		
		auto ver = p_board.get_row(inserted_pos.second);
		auto hor = p_board.get_column(inserted_pos.first);
		auto diag_pos = p_board.get_diagonal(inserted_pos.first, inserted_pos.second, diagonal_direction::Positive);
		auto diag_neg = p_board.get_diagonal(inserted_pos.first, inserted_pos.second, diagonal_direction::Negative);

		has_player_won =
			   board::count_contiguous_cells(ver,		tk) == 4
			|| board::count_contiguous_cells(hor,		tk) == 4
			|| board::count_contiguous_cells(diag_pos,	tk) == 4
			|| board::count_contiguous_cells(diag_neg,	tk) == 4;
		current_player = (current_player + 1) % 2;
	}
	std::cout << "Game finished!" << std::endl;
}

void c4::run_game()
{
	init();
}
