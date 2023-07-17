#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "../include/board.hpp"

namespace c4
{
	board::board(const int width, int height)
		: width_(width)
		, height_(height) 
	{
		for (int i = 0; i < width * height; i++)
		{
			this->cells_.emplace_back();
		}
	}

	auto board::operator[](std::pair<unsigned int, unsigned int> index) -> cell*
	{
		const unsigned int m_index = index.second * width_ + index.first;
		if (m_index > this->cells_.size()) throw std::invalid_argument("The provided index is invalid");
		return &(this->cells_[m_index]);
	}

	void board::set_value(std::pair<unsigned int, unsigned int> index, cell_content content)
	{
		if (content == cell_content::Empty) throw std::invalid_argument("cannot set a board sell content's to empty");
		const unsigned int m_index = index.second * width_ + index.first;
		if (m_index > this->cells_.size()) throw std::invalid_argument("The provided index is invalid");
		if (this->cells_[m_index].get_cell_content() == cell_content::Empty)
		{
			this->cells_[m_index].set_cell_content(content);
		}
		else throw std::invalid_argument("this cell already has content");
	}

	auto board::get_row(int row) -> std::vector<cell*>
	{
		const int start = this->width_ * row;
		std::vector<cell*> returned { std::vector<cell*>() };
		for (int i = 0; i < this->width_; i++)
		{
			returned.emplace_back(&(this->cells_[start+i]));
		}
		return returned;
	}

	auto board::get_column(int column) -> std::vector<cell*>
	{
		auto returned { std::vector<cell*>() };
		for (int i = 1; i <= this->height_; i++)
		{
			returned.emplace_back(&(this->cells_[static_cast<size_t>(column)*i]));
		}
		return returned;
	}
};
