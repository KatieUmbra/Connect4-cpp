#pragma once

namespace c4
{
	class vector2
	{
	private:
		int x_;
		int y_;
	public:
		vector2(int x, int y);
		[[nodiscard]] auto get_x() const -> int;
		[[nodiscard]] auto get_y() const -> int;
	};
}
