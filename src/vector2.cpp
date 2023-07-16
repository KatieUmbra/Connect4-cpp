#include "../include/vector2.hpp"

namespace c4
{
	vector2::vector2(const int x, int y)
		: x_(x), y_(y)
	{}

	auto vector2::get_x() const -> int
	{
		return x_;
	}

	auto vector2::get_y() const -> int
	{
		return y_;
	}
}
