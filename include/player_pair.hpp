// ReSharper disable CppRedundantAccessSpecifier
#pragma once

#include "player.hpp"
#include "color.hpp"

namespace c4
{
	struct player_pair
	{
	public:
		const player player_1;
		const player player_2;
		
		static player_pair init();
		player operator[](const unsigned int&) const;

	private:

		player_pair(const std::pair<std::string, std::string>&, const std::pair<token, token>&);
		void print_tokens() const;
		static std::string ask_name(const int&);
		static std::pair<token, token> ask_token(const std::pair<std::string, std::string>&, const int&);
	};
	
}
