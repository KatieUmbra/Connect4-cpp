// ReSharper disable CppRedundantAccessSpecifier
#pragma once

#include <string>
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
		explicit player(const int max_score, std::string name, const c4::token token);

		// getters
		[[nodiscard]] std::string name() const;
		[[nodiscard]] std::string token() const;
		[[nodiscard]] int max_score() const;

		// setter
		void set_max_score(const int& max_score);
	};
}
