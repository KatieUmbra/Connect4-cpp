// ReSharper disable CppRedundantAccessSpecifier
#pragma once

#include <pch.hpp>
#include "token.hpp"

namespace c4
{
	class player
	{
	private:
		const std::string name_;
		const std::string token_;
		int max_score_;
	public:
		explicit player(int max_score, std::string name, c4::token token);

		// getters
		[[nodiscard]] auto name() const -> std::string;
		[[nodiscard]] auto token() const -> std::string;
		[[nodiscard]] auto max_score() const -> int;
		[[nodiscard]] auto get_token_enum() const -> c4::token;

		// setter
		void set_max_score(int max_score);
	};
}
