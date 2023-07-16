#pragma once

#include "cell.hpp"
#include <utility>
#include <vector>

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

		auto count_horizontal(int row) -> int;
		auto count_vertical(int column) -> int;
		auto count_diagonal(int row, int column, diagonal_direction direction) -> int;
		auto get_row(int row) -> std::vector<cell*>;
		auto get_column(int column) -> std::vector<cell*>;
		auto get_diagonal(int row, int column, diagonal_direction direction) -> std::vector<cell*>;
		public:
		explicit board(int, int);
		void set_value(std::pair<unsigned int, unsigned int>, cell_content);
		auto operator[](std::pair<unsigned int, unsigned int>) -> cell*;
	};
}
