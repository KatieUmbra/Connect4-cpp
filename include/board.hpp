#pragma once

#include "cell.hpp"
#include <array>
#include <pch.hpp>

namespace c4 
{
	enum class diagonal_direction {
		Positive,
		Negative
	};

	class board
	{
		const int width_, height_;
		std::vector<cell> cells_;
		public:
		explicit board(unsigned short, unsigned short);
		void print_board();
		// Counters
		static auto count_contiguous_cells(std::vector<cell*>& line, cell_content kind) -> int;
		auto is_board_full() -> bool;
		auto get_score() -> int;
		// Getters
		[[nodiscard]] auto get_quadrants(int row, int column) const -> std::array<int, 4UL>;
		auto get_row(int row) -> std::vector<cell*>; //done
		auto get_column(int column) -> std::vector<cell*>; //done
		auto get_diagonal(int row, int column, diagonal_direction direction) -> std::vector<cell*>;
		auto get_size() -> int;
		// Setters
		void set_value(std::pair<unsigned int, unsigned int>, cell_content); //done 
		auto place_in_column(unsigned int column, cell_content) -> std::pair<bool, std::pair<int, int>>;
		auto operator[](std::pair<unsigned int, unsigned int>) -> cell*; // done
		// Helpers
		[[nodiscard]] auto coordinates_from_position(unsigned int) const -> std::pair<int, int>;
		[[nodiscard]] auto position_from_coordinates(unsigned int, unsigned int) const -> unsigned int;
	};

	namespace board_characters {
		constexpr char Corner = '+';
		constexpr char Vertical = '|';
		constexpr char Horizontal = '-';
		constexpr char Empty = ' ';
		constexpr auto Spacer = "            ";
	}
}
