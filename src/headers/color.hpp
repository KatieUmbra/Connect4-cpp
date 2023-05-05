#pragma once

#include <string>
#include <unordered_map>

#define CONST_COLOR inline const rgb

namespace c4::color
{
	enum class code
	{
		c033,
		ce,
		cx1b,
	};

	std::string code_string(const code input);
	inline constexpr code default_code = code::c033;

	struct rgb
	{
		int r, g, b;
		rgb(int r, int g, int b);
	};

	class colored_str
	{
		const std::string reset_code_;
		const std::string complete_code_;

		inline static bool set_code_ = false;
		inline static code working_code_;

		static std::string gen_complete_code(const rgb&);
		static std::string gen_complete_code(int);

		static std::string gen_reset_code();

	public:
		explicit colored_str(const rgb&);
		explicit colored_str(int);
		void colorize_str(std::string&) const;
		static void color_prompt();
	};

	namespace const_colors
	{
		CONST_COLOR white(255, 255, 255);
		CONST_COLOR red(255, 0, 0);
	}
}
