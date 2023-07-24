#include <algorithm>
#include <array>
#include <cstddef>
#include <exception>
#include <iterator>
#include <list>
#include <stdexcept>
#include <utility>
#include "board.hpp"
#include "cell.hpp"

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

	//TODO(Katie)
	auto board::get_diagonal(const int row, int column, diagonal_direction direction) -> std::vector<cell*> //NOLINT
	{
		std::vector<cell*> diagonal{static_cast<size_t>(std::min(width_, height_)), nullptr};
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
		auto center = q_1;
		auto center_position = position_from_coordinates(row, column);
		diagonal[center] = &this->cells_[center_position];
		for (int i = 0; i < q_1; i--)
		{
			diagonal[center - 1 - i] = &this->cells_[center_position - (difference * i)];
		}
		for (int i = 1; i < q_2; i++)
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
		std::array y = {row,		this->height_ - row};
		std::array x = {column,		this->width_ - column};
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
};
