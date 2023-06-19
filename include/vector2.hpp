#pragma once

namespace c4
{
	class vector2
	{
	private:
		int x_;
		int y_;
	public:
		vector2(const int& x, const int& y);
		[[nodiscard]] int get_x() const;
		[[nodiscard]] int get_y() const;
	};
}