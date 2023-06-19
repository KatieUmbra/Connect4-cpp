#include "../include/color.hpp"
#include "../include/player.hpp"
#include "../include/player_pair.hpp"

#include <cctype>
#include <iostream>
#include <algorithm>
#include <map>
#include <random>
#include <stdexcept>
#include <string>

namespace c4
{
	player_pair::player_pair
	(
		const std::pair<std::string, std::string>& names,
		const std::pair<token, token>& tokens
	)
		: player_1(0, names.first, tokens.first)
		, player_2(0, names.second, tokens.second)
	{}

	player_pair player_pair::init()
	{
		const std::string player_1_name = ask_name(1);
		const std::string player_2_name = ask_name(2);
		const std::pair player_name_pair(player_1_name, player_2_name);

		//random stuff
		std::random_device random_device;
		std::mt19937 rng(random_device());
		std::uniform_int_distribution uniform_int_distribution(0, 1);
		const int first_player = uniform_int_distribution(rng);

		const std::pair player_tokens(ask_token(player_name_pair, first_player));
		player_pair pair(player_name_pair, player_tokens);
		pair.print_tokens();
		return pair;
	}

	void player_pair::print_tokens() const
	{
		auto player_name_color = c4::color::colored_str(c4::color::const_colors::magenta);
		auto x_color = c4::color::colored_str(c4::color::const_colors::red);
		auto o_color = c4::color::colored_str(c4::color::const_colors::green);
		for (int i = 0; i < 2; i++)
		{
			const player current_player = (*this)[i];
			auto current_player_name = current_player.name();
			auto current_player_token = current_player.token();
			player_name_color.colorize_str(current_player_name);
			if (current_player_token == "X")
			{
				x_color.colorize_str(current_player_token);
			}
			else 
			{
				o_color.colorize_str(current_player_token);
			}
			std::cout
				<< current_player_name
				<< ", you're playing with the token: "
				<< current_player_token
				<< "."
				<< std::endl;
		}
	}


	std::pair<token, token> player_pair::ask_token(const std::pair<std::string, std::string>& names, const int& first)
	{
		auto x_color = c4::color::colored_str(c4::color::const_colors::red);
		auto o_color = c4::color::colored_str(c4::color::const_colors::green);
		std::string x = "[X]";
		std::string o = "[O]";
		x_color.colorize_str(x);
		o_color.colorize_str(o);
		std::cout
			<< "Hello "
			<< names.first
			<< ", Please choose between "
			<< x
			<<" or "
			<< o
			<<":" 
			<< std::endl;
		std::string choice;
		std::cin >> choice;
		std::transform(choice.begin(), choice.end(), choice.begin(), ::toupper);
		if (choice == "X" || choice == "O")
		{
			if (choice == "X")
				return std::make_pair(token::x, token::o);
			return std::make_pair(token::o, token::x);
		}
		return ask_token(names, first);
	}

	std::string player_pair::ask_name(const int& id)
	{
		auto player_id_color = c4::color::colored_str(c4::color::const_colors::blue);
		std::string player_id(std::to_string(id));
		player_id_color.colorize_str(player_id);
		std::string returned_value;
		std::cout
			<< "Hello player "
			<< player_id
			<< ", What's your name?: "
			<< std::endl;
		std::cin >> returned_value;
		return returned_value;
	}

	player player_pair::operator[](const unsigned int& index) const
	{
		switch (index)
		{
		case 0:
			return player_1;
		case 1:
			return player_2;
		default:
			throw std::invalid_argument("There are only [0, 1] players, argument was out of bounds.");
		}
	}

}
