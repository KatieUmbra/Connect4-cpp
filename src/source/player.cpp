#include "player.hpp"

#include <iostream>
#include "token.hpp"

namespace c4
{
	std::string translate_token(const token tk)
	{
		std::string result;
		switch (tk)
		{
		case token::x:
			result = "X";
			break;
		case token::o:
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

	int player::max_score() const
	{
		return max_score_;
	}

	std::string player::name() const
	{
		return name_;
	}

	std::string player::token() const
	{
		return token_;
	}

	void player::set_max_score(const int& max_score)
	{
		max_score_ = max_score;
	}


}
