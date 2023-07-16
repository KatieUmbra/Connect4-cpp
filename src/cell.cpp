#include "../include/cell.hpp"

namespace c4
{
	cell::cell()
		:value_(cell_content::Empty)
	{}

	auto cell::get_cell_content() -> cell_content {
		return this->value_;
	}

	void cell::set_cell_content(cell_content content) {
		this->value_ = content;
	}
}
