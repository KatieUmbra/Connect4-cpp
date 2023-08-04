#include "player.hpp"
#include "token.hpp"
#include <string_view>

namespace c4
{
	auto translate_token(const token tk) -> std::string_view
	{
		using namespace std::literals;
		return tk == token::X ? "X"sv : "O"sv;
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

	auto player::get_token_enum() const -> c4::token
	{
		return this->token_ == "X" ? c4::token::X : c4::token::O;
	}

	void player::set_max_score(int max_score)
	{
		max_score_ = max_score;
	}
}
