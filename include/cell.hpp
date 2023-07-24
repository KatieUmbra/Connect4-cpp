#pragma once

#include <string>
namespace c4
{
	enum class cell_content {
		Empty = 0,
		X,
		O
	};

	inline auto to_string(cell_content content) -> std::string
	{
		switch (content) {
			case cell_content::Empty: return "Empty";
			case cell_content::X: return "X";
			case cell_content::O: return "O";
		}
		return "Null";
	}

	struct cell
	{
		cell();
		explicit cell(cell_content content);
		auto get_cell_content() -> cell_content;
		void set_cell_content(cell_content content);
		private:
		cell_content value_;
	};
};
