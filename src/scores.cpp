#include "scores.hpp"
#include <algorithm>
#include <array>
#include <cstring>
#include <fstream>
#include <iterator>
#include <string_view>
#include <utility>
#include <vector>
#include "pch.hpp"
#include "pch_tomlplusplus.hpp"

namespace c4
{
	auto file_name = HomeFolder + ScoresLocation;
	auto is_scores_file_valid() -> RETURN_CASE
	{
		auto file_exists = c4::file_exists(file_name);
		if(file_exists)
		{
			try
			{
				auto str_table = c4::read_file_into_string(file_name.c_str());
				auto result = toml::parse(str_table);
				return pair(0, "File exists and is valid!");
			}
			catch(const toml::parse_error& err)
			{
				return pair(2, "File cannot be parsed!");
			}
		}
		return pair(1, "File doesn't exist!");
	}
	auto write_empty_scores_file() -> RETURN_CASE
	{
		if(remove(file_name.c_str()) == 1)
		{
			return pair(2, "Internal Error: File couldn't be removed.");
		}
		auto scores = toml::table
		{
			{ "First",	toml::table { {"Name", ""}, { "Score", 0 } } },
			{ "Second", toml::table { {"Name", ""}, { "Score", 0 } } },
			{ "Third",	toml::table { {"Name", ""}, { "Score", 0 } } },
			{ "Fourth", toml::table { {"Name", ""}, { "Score", 0 } } },
			{ "Fifth",	toml::table { {"Name", ""}, { "Score", 0 } } }
		};
		auto file_stream = std::ofstream{file_name};
		file_stream << scores;
		file_stream.close();
		return pair(0, "Empty file written successfully");
	}
	
	score::score(std::string& p_name, int p_score)
		: score_value(p_score)
		, name(p_name)
	{}

	score::score(std::string_view p_name, int p_score)
		: score_value(p_score)
		, name(p_name)
	{}
	auto score::score_from_toml(toml::table& source, std::string_view name) -> std::optional<score>
	{
		auto f_name = source[name]["Name"].value<std::string_view>();
		auto score = source[name]["Score"].value<int>();
		if(f_name.has_value() && score.has_value())
		{
			return c4::score(f_name.value(), score.value());
		}	
		return std::optional<c4::score>{};	
	}

	auto load_scores_from_file() -> std::array<score, 5>
	{
		auto empty_score = score("", 0);
		std::array<score, 5> returned_arr{empty_score, empty_score, empty_score, empty_score, empty_score};
		auto file_value = toml::parse_file(HomeFolder + ScoresLocation);
		std::vector<score> scores;
		for(const auto& [k, v] : Position)
		{
			auto val = file_value[k];
			if (is_scores_file_valid().first == 0)
			{
				auto current_score = score::score_from_toml(file_value, k);
				if(current_score.has_value())
				{
					scores.emplace_back(current_score.value());
				}
				else
				{
					scores.emplace_back(empty_score);
				}
			}
			else
			{
				scores.emplace_back(empty_score);
			}
		}
		std::move(scores.begin(), scores.begin() + 5, returned_arr.begin());
		return returned_arr;
	}

	void save_scores_to_file(std::array<score, 5>& scores)
	{
		auto ofs = std::ofstream{};
		ofs.open(file_name, std::ofstream::out | std::ofstream::trunc);
		auto tbl = toml::table{};
		for (auto [k, v] : Position)
		{
			tbl.insert_or_assign(k, toml::table {
				{ "Name",	scores[v].name			},
				{ "Score",	scores[v].score_value	}
			});
		}
		ofs << tbl;
		ofs.close();
	}

	void insert_score_into_array(std::array<score, 5>& p_score_array, score p_score)
	{
		std::vector<score> complete {};
		std::for_each(p_score_array.begin(), p_score_array.end(), 
			[&](auto& it)
			{
				complete.emplace_back(it);
			});

		complete.emplace_back(std::move(p_score));

		std::sort(complete.begin(), complete.end(), 
			[](auto& a, auto& b) -> bool 
			{
				return a.score_value > b.score_value;
			});

		for (int i = 0; i < 5; i++)
		{
			p_score_array[i] = complete[i];
		}
	}
}
