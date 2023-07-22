#include <algorithm>
#include <array>
#include <cstddef>
#include <exception>
#include <iostream>
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
		std::cout << "m_index: " << m_index << std::endl;
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
		std::cout << "Getting row: " << row << std::endl;
		const int start = this->width_ * row;
		std::vector<cell*> returned{static_cast<std::size_t>(this->width_)};
		for (int i = 0; i < this->width_; i++)
		{
			std::cout << "Index: " << start + i << std::endl;
			try {
				returned.emplace_back(&(this->cells_[start+i]));
			}
			catch(std::exception&) {
				std::cout << "oops!" << std::endl;
			}
		}
		return returned;
	}

	auto board::get_column(int column) -> std::vector<cell*>
	{
		std::cout << "Getting Column: " << column << std::endl;
		std::vector<cell*> returned {static_cast<std::size_t>(this->height_)};
		for (int i = 0; i < this->height_; i++)
		{
			
			returned.emplace_back(&(this->cells_[(i * width_) + column]));
		}
		return returned;
	}

	auto board::get_diagonal(const int row, int column, diagonal_direction direction) -> std::vector<cell*>
	{
		std::cout << "Getting Diagonal: " << row << ", " << column << std::endl;
		auto center = column * this->width_ + row;
		std::vector<cell*> diagonal{};
		diagonal.reserve(std::min(width_, height_));
		auto quadrants = this->get_quadrants(row, column);
		int center_pos = 0;
		if (direction == c4::diagonal_direction::Positive)
		{
			center_pos = quadrants[3];
			auto count = this->width_ - 1;
			for(auto i = 1; i <= quadrants[2]; i++)
			{
				diagonal[center_pos + i] = &(this->cells_[center - count * i]);
			}
			for (auto i = 1; i <= quadrants[3]; i++)
			{
				diagonal[center_pos - i] =  &(this->cells_[center + count * i]);
			}

		}
		else
		{
			auto count = this->width_ + 1;
			center_pos = quadrants[4];
			for(auto i = 1; i <= quadrants[1]; i++)
			{
				diagonal[center_pos + i] = &(this->cells_[center + count * i]);
			}
			for (auto i = 1; i <= quadrants[4]; i++)
			{
				diagonal[center_pos - i] = &(this->cells_[center - count * i]);
			}
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

	auto board::get_quadrants(const unsigned int row, unsigned int column) const -> std::array<int, 4UL> 
	{
		std::cout << "Getting quadrants: " << row << ", " << column << std::endl;
		std::array<int, 4UL> returned {0, 0, 0, 0}; 
		std::array y = {row,		static_cast<unsigned int>(this->height_ - row - 1)};
		std::array x = {column,		static_cast<unsigned int>(this->width_ - column - 1)};
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
};
