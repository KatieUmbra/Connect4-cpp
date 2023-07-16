#include "../include/player.hpp"

#include <iostream>
#include "../include/token.hpp"

namespace c4
{
	auto translate_token(const token tk) -> std::string
	{
		std::string result;
		switch (tk)
		{
		case token::X:
			result = "X";
			break;
		case token::O:
			result = "O";
			break;
		}
		return result;
	}

	player::player
	(
		const int max_score,
		std::string name,
		const c4::token token
	)
		: name_(std::move(name))
		, token_(translate_token(token))
		, max_score_(max_score)
	{}

	auto player::max_score() const -> int
	{
		return max_score_;
	}

	auto player::name() const -> std::string
	{
		return name_;
	}

	auto player::token() const -> std::string
	{
		return token_;
	}

	void player::set_max_score(const int& max_score)
	{
		max_score_ = max_score;
	}


}
