#include "../include/vector2.hpp"

namespace c4
{
	vector2::vector2(const int& x, const int& y)
		: x_(x), y_(y)
	{}

	int vector2::get_x() const
	{
		return x_;
	}

	int vector2::get_y() const
	{
		return y_;
	}


}
