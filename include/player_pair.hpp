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
		
		static auto init() -> player_pair;
		auto operator[](const unsigned int&) const -> player;

	private:

		player_pair(const std::pair<std::string, std::string>&, const std::pair<token, token>&);
		void print_tokens() const;
		static auto ask_name(const int&) -> std::string;
		static auto ask_token(const std::pair<std::string, std::string>&, const int&) -> std::pair<token, token>;
	};
	
}
