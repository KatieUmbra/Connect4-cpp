#include "../include/color.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <ranges>
#include <sstream>
#include <ostream>

namespace c4::color
{
	std::string code_string(const code input)
	{
		switch (input)
		{
		// ReSharper disable once CommentTypo
		case code::c033:  // NOLINT(bugprone-branch-clone)
			return {"\033"};
		case code::ce:
			return {"\e"};  // NOLINT(clang-diagnostic-pedantic)
		case code::cx1b:
			return {"\x1b"};
		}
		return {};
	}

	rgb::rgb(const int r, const int g, const int b)
		: r(r)
		, g(g)
		, b(b)
		{}

	std::string colored_str::gen_complete_code(const rgb& color)
	{
		std::string result;
		if (set_code_)
		{
			std::stringstream ss;
			ss << code_string(working_code_);
			ss << "[38;2;";
			ss << color.r << ";";
			ss << color.g << ";";
			ss << color.b << "m";
			result = ss.str();
		}
		else
		{
			result = "";
		}
		return result;
	}

	std::string colored_str::gen_complete_code(int color)
	{
		std::string result;
		if (set_code_)
		{
			std::stringstream ss;
			ss << code_string(working_code_);
			ss << "[";
			ss << color;
			ss << "m";
			result = ss.str();
		}
		else
		{
			result = "";
		}
		return result;
	}

	std::string colored_str::gen_reset_code()
	{
		std::string result;
		if(set_code_)
		{
			result = code_string(working_code_) + "[0m";
		}
		else
		{
			result = "";
		}
		return result;
	}

	colored_str::colored_str(const rgb& color)
		:reset_code_(gen_reset_code())
		,complete_code_(gen_complete_code(color))
	{}

	colored_str::colored_str(const int color)
		:reset_code_(gen_reset_code())
		,complete_code_(gen_complete_code(color))
	{}

	void colored_str::colorize_str(std::string& str) const
	{
		if (set_code_)
		{
			std::string new_str(complete_code_);
			new_str.append(str);
			new_str.append(reset_code_);
			str = std::move(new_str);
		}
	}

	void colored_str::color_prompt()
	{
		if (!set_code_)
		{
			// ReSharper disable once CppTooWideScopeInitStatement
			std::pair<std::string, code> prompts[] = {
				{"\033[38;2;255;105;190m test \033[0m", code::c033},
				{"\e[38;2;255;105;190m test \e[0m", code::ce},  // NOLINT(clang-diagnostic-pedantic)
				{"\x1b[38;2;255;105;190m test \x1b[0m", code::cx1b}
			};
			for (const auto& [fst, snd] : prompts)
			{
				std::string answer;
				std::cout << "Is the following text pink?:" << fst << std::endl;
				while (answer != "Y" && answer != "N")
				{
					std::cout << "Please answer [Y] or [N] :" << std::endl;
					std::cin >> answer;
					std::transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
				}
				if (answer == "Y")
				{
					set_code_ = true;
					working_code_ = snd;
					break;
				}
			}
		}
	}
}
