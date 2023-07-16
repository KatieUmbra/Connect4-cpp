#pragma once

namespace c4
{
	enum class cell_content {
		Empty = 0,
		X,
		O
	};

	struct cell
	{
		cell();
		auto get_cell_content() -> cell_content;
		void set_cell_content(cell_content content);
		private:
		cell_content value_;
	};
};
