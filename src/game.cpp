#include "game.hpp"
#include "board.hpp"
#include "cell.hpp"
#include "player_pair.hpp"
#include "global.hpp"
#include "color.hpp"
#include "token.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <sstream>
#include <string_view>

#define val const auto
#define var auto

void c4::init()
{
	color::colored_str::color_prompt();
	game();
};

void c4::game()
{
	auto playing = true;
	while(playing)
	{
		clear_console();
		auto pp = player_pair::init();
		wait_for_input();
		board m_board{6, 6};
		playing = main_loop(pp, m_board);
	}
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
		std::string input;
		std::cin >> input;
		std::stringstream ss(input);
		int column = 0;
		ss >> column;
		column--;
		if(ss.fail())
		{
			std::cout << input << " is not a number, please introduce a valid number." << '\n';
			continue;
		}
		auto result = p_board.place_in_column(column, plr.token() == "X" ? cell_content::X : cell_content::O);
		if(result.first)
		{
			position = result.second;
			break;
		}
		std::cout << column + 1 << " is full or is out of bounds, please try again." << '\n';
	}
	return position;
}

auto c4::scores_handler(score&& p_score) -> std::array<score, 5>
{
	if(auto sc = is_scores_file_valid(); sc.first != 0)
	{
		write_empty_scores_file();
	}
	auto stored_scores = load_scores_from_file();
	insert_score_into_array(stored_scores, p_score);
	save_scores_to_file(stored_scores);
	return stored_scores;
}

auto c4::main_loop(player_pair& players, board& p_board) -> bool
{
	var has_player_won = false;
	var ended_in_tie = false;
	var current_player = 0;
	int iter = 0;
	const int size = p_board.get_size();
	while(!has_player_won && iter < size)
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
		ended_in_tie = p_board.is_board_full();
		current_player = (current_player + 1) % 2;
		iter++;
	}
	clear_console();
	p_board.print_board();
	int score = 0;
	if (!has_player_won)
	{
		std::cout << "Game ended in a tie!" << '\n';
	}
	else
	{
		score = p_board.get_score();
		current_player = (current_player + 1) % 2;
		std::cout << players[current_player].name() << " won!, Congratulations" << '\n';
	}
	auto scores = scores_handler(c4::score(players[current_player].name(), score));
	std::cout << "Score: " << score << '\n';
	print_scores(std::move(scores));
	std::cout << "Do you wish to play again? [Y] or [N]: " << '\n';
	auto play_again = false;
	auto answer = false;
	while(!answer)
	{
		std::string input;
		std::cin >> input;
		std::transform(input.begin(), input.end(), input.begin(), ::toupper);
		if(input == "Y" || input == "N")
		{
			if (input == "Y")
			{
				play_again = true;
			}
			answer = true;
		}
	}
	return play_again;
}

void c4::print_scores(std::array<score, 5>&& scores)
{
	std::cout << " ===== Top Scores: ===== " << '\n';
	for (const auto& sc : scores)
	{
		std::cout << "- " << sc.name << ": " << sc.score_value << '\n';
	}
}

void c4::run_game()
{
	init();
}
