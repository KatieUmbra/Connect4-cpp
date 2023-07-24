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
		static auto count_contiguous_cells(std::vector<cell*>& line, cell_content kind) -> int;
		[[nodiscard]] auto get_quadrants(int row, int column) const -> std::array<int, 4UL>;
		auto get_row(int row) -> std::vector<cell*>; //done
		auto get_column(int column) -> std::vector<cell*>; //done
		auto get_diagonal(int row, int column, diagonal_direction direction) -> std::vector<cell*>;
		explicit board(unsigned short, unsigned short);
		void set_value(std::pair<unsigned int, unsigned int>, cell_content); //done
		auto operator[](std::pair<unsigned int, unsigned int>) -> cell*; // done
		[[nodiscard]] auto coordinates_from_position(unsigned int) const -> std::pair<int, int>;
		[[nodiscard]] auto position_from_coordinates(unsigned int, unsigned int) const -> unsigned int;
	};
}
