#include <algorithm>
#include <array>
#include <cstddef>
#include <exception>
#include <iterator>
#include <list>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include "board.hpp"
#include "cell.hpp"
#include "color.hpp"

namespace c4
{
	board::board(const unsigned short width, unsigned short height)
		: width_(width)
		, height_(height)
	{
		for (int i = 0; i < width * height; i++)
		{
			this->cells_.emplace_back(cell_content::Empty);
		}
	}

	auto board::operator[](std::pair<unsigned int, unsigned int> index) -> cell*
	{
		const unsigned int m_index = index.second * width_ + index.first;
		if (m_index >= this->cells_.size()) //NOLINT
			throw std::invalid_argument("The provided index is invalid");

		return &(this->cells_[m_index]);
	}

	//NOLINTBEGIN
	void board::set_value(std::pair<unsigned int, unsigned int> index, cell_content content)
	{
		const unsigned int m_index = index.second * width_ + index.first;

		if (content == cell_content::Empty) 
			throw std::invalid_argument("cannot set a board cell content's to empty");
		
		if (m_index >= this->cells_.size()) 
			throw std::invalid_argument("The provided index is invalid");
		
		if(this->cells_[m_index].get_cell_content() != cell_content::Empty)
			throw std::invalid_argument("this cell already has content");
		
		this->cells_[m_index].set_cell_content(content);
	}
	//NOLINTEND

	auto board::get_row(int row) -> std::vector<cell*>
	{
		const int start = this->width_ * row;
		std::vector<cell*> returned{static_cast<std::size_t>(this->width_)};
		for (int i = 0; i < this->width_; i++)
		{
			returned[i] = &(this->cells_[start+i]);
		}
		return returned;
	}

	auto board::get_column(int column) -> std::vector<cell*>
	{

		std::vector<cell*> returned {static_cast<std::size_t>(this->height_)};
		for (int i = 0; i < this->height_; i++)
		{
			returned[i] = &(this->cells_[(i * width_) + column]);
		}
		return returned;
	}	

	auto board::get_diagonal(const int row, int column, diagonal_direction direction) -> std::vector<cell*> //NOLINT
	{
		auto quadrants = this->get_quadrants(row, column);
		int q_1;
		int q_2;
		int direction_sign;
		unsigned int difference;
		if (direction == c4::diagonal_direction::Negative)
		{
			q_1 = quadrants[0];
			q_2 = quadrants[3];
			direction_sign = 1;
			difference = this->width_ + 1;
		}
		else
		{
			q_1 = quadrants[1];
			q_2 = quadrants[2];
			direction_sign = -1;
			difference = this->width_ - 1;
		}
		std::vector<cell*> diagonal{static_cast<size_t>(q_1 + q_2 + 1), nullptr};
		auto center = q_1;
		auto center_position = position_from_coordinates(row, column);
		diagonal[center] = &(this->cells_[center_position]);
		for (int i = 1; i <= q_1; i++)
		{
			diagonal[center - i] = &this->cells_[center_position - (difference * i)];
		}
		for (int i = 1; i <= q_2; i++)
		{
			diagonal[center + i] = &this->cells_[center_position + (difference * i)];
		}
		return diagonal;
	}

	auto board::count_contiguous_cells(std::vector<cell*>& line, cell_content kind) -> int
	{
		auto count = 0;
		auto max = 0;
		for (auto* cell : line)
		{
			if (cell->get_cell_content() == kind)
			{
				count++;
				if (count > max)
				{
					max = count;
				}
			} 
			else 
			{
				count = 0;
			}
		}
		return max;
	}

	auto board::get_quadrants(const int row, int column) const -> std::array<int, 4UL> 
{
		std::array<int, 4UL> returned {0, 0, 0, 0};
		std::array x = {row,		std::max(this->width_ - (row + 1), 0)};
		std::array y = {column,		std::max(this->height_ - (column + 1), 0)};
		//NOLINTBEGIN(bugprone-narrowing-conversions)
		returned[0] = std::min(y[0], x[0]);
		returned[1] = std::min(y[0], x[1]);
		returned[2] = std::min(y[1], x[0]);
		returned[3] = std::min(y[1], x[1]);
	//NOLINTEND(bugprone-narrowing-conversions)
		return returned;
	}

	auto board::coordinates_from_position(unsigned int position) const -> std::pair<int, int>
	{
		auto x = position / this->width_;
		auto y = position % this->width_;
		return std::pair(y, x);
	}

	auto board::position_from_coordinates(const unsigned int row, unsigned int column) const -> unsigned int
	{
		return this->width_ * column + row;
	}

	void board::print_board()
	{
		auto numbers_stream = std::ostringstream{};
		numbers_stream << board_characters::Empty;

		auto line_stream = std::ostringstream{};
		line_stream << board_characters::Corner;
		for(int i = 0; i < this->width_; i++)
		{
			line_stream << board_characters::Horizontal;
			numbers_stream << i + 1;
		}
		line_stream << board_characters::Corner;
		numbers_stream << board_characters::Empty;

		const std::string horizontal_line = line_stream.str();
		const std::string number_line = numbers_stream.str();

		std::vector<std::string> lines{};
		lines.emplace_back(number_line);
		lines.emplace_back(horizontal_line);
		auto x_color = color::colored_str{color::const_colors::Red};
		auto o_color = color::colored_str{color::const_colors::Blue};
		for(int i = 1; i <= this->height_; i++)
		{
			auto row_stream = std::ostringstream{};
			row_stream << board_characters::Vertical;
			auto row = this->get_row(i - 1);
			for (auto* cell : row)
			{
				auto cell_content = cell->get_cell_content();
				if(cell_content != cell_content::Empty)
				{
					//std::cout << "Cell Content: " << static_cast<int>(cell_content) << std::endl;
					row_stream << ((cell_content == cell_content::X)
						? x_color.colorize_str("X")
						: o_color.colorize_str("O"));
				}
				else
				{
					row_stream << board_characters::Empty;
				}
			}
			row_stream << board_characters::Vertical;
			lines.emplace_back(row_stream.str());
		}
		lines.emplace_back(horizontal_line);

		for (auto& line : lines)
		{
			std::cout << line << std::endl;
		}
	}

	auto board::place_in_column(unsigned int column, cell_content content) -> std::pair<bool, std::pair<int, int>>
	{
		if (column >= this->width_)
		{
			return {false, {0, 0}};
		}
		auto m_column = this->get_column(static_cast<int>(column));
		auto last_free_index = -1;
		for (int i = 0; i < this->height_; i++)
		{
			if (m_column[i]->get_cell_content() == cell_content::Empty)
			{
				last_free_index = i;
			}
			else
			{
				break;
			}
		}
		if(last_free_index == -1)
		{
			return {false, {0, 0}};
		}
		this->set_value({column, last_free_index}, content);
		return {true, {column, last_free_index}};
	}
};
