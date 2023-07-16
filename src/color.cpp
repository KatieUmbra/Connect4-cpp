#include "../include/color.hpp"

#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <ranges>
#include <sstream>
#include <ostream>
#include <string>
#include <utility>

namespace c4::color
{
	auto code_string(const code input) -> std::string
	{
		switch (input)
		{
			case code::C033: //NOLINT
				return {"\033"};
			case code::Ce:
				return {"\e"};
			case code::Cx1b:
				return {"\x1b"};
		}
		return {};
	}

	rgb::rgb(const int r, int g, const int b)
		: r(r)
		, g(g)
		, b(b)
		{}

	auto colored_str::gen_complete_code(const rgb& color) -> std::string
	{
		std::string result;
		if (set_code)
		{
			std::stringstream ss;
			ss << code_string(working_code);
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

	auto colored_str::gen_complete_code(int color) -> std::string
	{
		std::string result;
		if (set_code)
		{
			std::stringstream ss;
			ss << code_string(working_code);
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

	auto colored_str::gen_reset_code() -> std::string
	{
		std::string result;
		if(set_code)
		{
			result = code_string(working_code) + "[0m";
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
		if (set_code)
		{
			std::string new_str(complete_code_);
			new_str.append(str);
			new_str.append(reset_code_);
			str = std::move(new_str);
		}
	}

	auto colored_str::colorize_str(const char* str) const -> std::string
	{
		if(set_code)
		{
			std::string new_str(complete_code_);
			new_str.append(str);
			new_str.append(reset_code_);
			return new_str;
		}
		return str;
	}

	void colored_str::color_prompt()
	{
		if (!set_code)
		{
			std::array<std::pair<std::string, code>, 3> prompts = {
				std::pair("\033[38;2;255;105;190m test \033[0m", code::C033),
				std::pair("\e[38;2;255;105;190m test \e[0m", code::Ce),
				std::pair("\x1b[38;2;255;105;190m test \x1b[0m", code::Cx1b)
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
					set_code = true;
					working_code = snd;
					break;
				}
			}
		}
	}
}
