#pragma once

#include "cell.hpp"
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
	
		public:
		auto count_contiguous_cells(std::vector<cell*>& line, cell_content kind) -> int;
		auto get_row(int row) -> std::vector<cell*>; //done
		auto get_column(int column) -> std::vector<cell*>; //done
		auto get_diagonal(int row, int column, diagonal_direction direction) -> std::vector<cell*>;
		explicit board(int, int);
		void set_value(std::pair<unsigned int, unsigned int>, cell_content); //done
		auto operator[](std::pair<unsigned int, unsigned int>) -> cell*; // done
	};
}
