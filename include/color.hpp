#pragma once

#include "global.hpp"
#include "pch.hpp"
#include <string>
#include <unordered_map>

#define CONST_COLOR inline const rgb

namespace c4::color
{
	enum class code
	{
		C033,
		Ce,
		Cx1b,
	};

	auto code_string(code input) -> std::string;
	inline constexpr code DefaultCode = code::C033;

	struct rgb
	{
		int r, g, b;
		rgb(int r, int g, int b);
	};

	class colored_str
	{
		const std::string reset_code_;
		const std::string complete_code_;

		inline static bool set_code = false;
		inline static code working_code;

		static auto gen_complete_code(const rgb&) -> std::string;
		static auto gen_complete_code(int) -> std::string;

		static auto gen_reset_code() -> std::string;

	public:
		explicit colored_str(const rgb&);
		explicit colored_str(int);
		void colorize_str(std::string&) const;
		[[nodiscard]]auto colorize_char(char) const -> std::string;
		auto colorize_str(const char*) const -> std::string;
		static void color_prompt();
	};

	namespace const_colors
	{
		CONST_COLOR White(255, 255, 255);
		CONST_COLOR Red(255, 0, 0);
		CONST_COLOR Blue(0, 0, 255);
		CONST_COLOR Green(0, 255, 0);
		CONST_COLOR Black(0, 0, 0);
		CONST_COLOR Yellow(255, 255, 0);
		CONST_COLOR Magenta(255, 0, 255);
		CONST_COLOR Aqua(0, 255, 255);
	}
}
