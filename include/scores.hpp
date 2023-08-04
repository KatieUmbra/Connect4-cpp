#include <array>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <toml++/impl/node_view.h>
#include <toml++/impl/table.h>

#ifdef _WIN32
#define HOME "USERPROFILE"
#else
#define HOME "HOME"
#endif

#define RETURN_CASE std::pair<int, std::string>

namespace c4
{
	using std::pair;

	inline const std::string HomeFolder = getenv(HOME);
	inline const std::string ScoresLocation = "/.scores.toml";
	inline const std::map<std::string, int> Position {
		{"First", 0},
		{"Second", 1},
		{"Third", 2},
		{"Fourth", 3},
		{"Fifth", 4}
	};

	inline auto file_exists(const std::string& name) -> bool
	{
		if(FILE* file = fopen(name.c_str(), "r"))
		{
			fclose(file);
			return true;
		}
		return false;
	}
	inline auto read_file_into_string(std::string_view path) -> std::string
	{
		auto ss = std::ostringstream{};
		std::ifstream input_file{path};
		ss << input_file.rdbuf();
		return ss.str();
	}

	auto write_empty_scores_file() -> RETURN_CASE;
	auto is_scores_file_valid() -> RETURN_CASE;

	struct score
	{
		score(std::string& p_name, int p_score);
		score(std::string_view p_name, int p_score);
		std::string name;
		int score_value;
		static auto score_from_toml(toml::table& source, std::string_view name) -> std::optional<score>;
	};

	auto load_scores_from_file() -> std::array<score, 5>;
	void save_scores_to_file(std::array<score, 5>& scores);
	void insert_score_into_array(std::array<score, 5>& p_score_array, score p_score);
}
