#define BOOST_TEST_MODULE Board Test 
#include "boost-test-pch.hpp"
#include "cell.hpp"
#include "board.hpp"

//NOLINTBEGIN(readability-convert-member-functions-to-static)
class board_test
{
public:
	void test_horizontal()
	{
		c4::board my_board{3, 3};
		my_board.set_value(std::pair(0, 0), c4::cell_content::O);
		my_board.set_value(std::pair(1, 0), c4::cell_content::O);
		my_board.set_value(std::pair(2, 0), c4::cell_content::O);
		auto row = my_board.get_row(0);
		auto cond_1 = row[0]->get_cell_content() == c4::cell_content::O;
		auto cond_2 = row[1]->get_cell_content() == c4::cell_content::O;
		auto cond_3 = row[2]->get_cell_content() == c4::cell_content::O;
		auto cond_4 = my_board[std::pair(0, 1)]->get_cell_content() == c4::cell_content::Empty;
		auto final_cond = cond_1 && cond_2 && cond_3 && cond_4;
		BOOST_TEST(final_cond);
	}

	void test_vertical()
	{
		c4::board my_board{2, 2};
		my_board.set_value(std::pair(1, 0), c4::cell_content::X);
		my_board.set_value(std::pair(1, 1), c4::cell_content::X);
		auto column = my_board.get_column(1);
		auto cond_1 = column[0]->get_cell_content() == c4::cell_content::X;
		auto cond_2 = column[1]->get_cell_content() == c4::cell_content::X;
		auto cond_3 = my_board.get_column(0)[0]->get_cell_content() == c4::cell_content::Empty;
		auto final_cond = cond_1 && cond_2 && cond_3;
		BOOST_TEST(final_cond);
	}
	void test_diagonal()
	{
		c4::board my_board{3, 3};
		my_board.set_value(std::pair(0, 0), c4::cell_content::X);
		my_board.set_value(std::pair(1, 1), c4::cell_content::X);
		my_board.set_value(std::pair(2, 2), c4::cell_content::X);
		auto diagonal = my_board.get_diagonal(0, 0, c4::diagonal_direction::Negative);
		auto cond_1 = diagonal[0]->get_cell_content() == c4::cell_content::X;
		auto cond_2 = diagonal[1]->get_cell_content() == c4::cell_content::X;
		auto cond_3 = diagonal[2]->get_cell_content() == c4::cell_content::X;
		auto cond_4 = my_board[std::pair(0, 1)]->get_cell_content() == c4::cell_content::Empty;
		auto final_cond = cond_1 && cond_2 && cond_3 && cond_4;
		BOOST_TEST(final_cond);
	}
	void test_count()
	{
		c4::board my_board{4, 4};
		my_board.set_value(std::pair(0, 1), c4::cell_content::X);
		my_board.set_value(std::pair(1, 1), c4::cell_content::X);
		auto diagonal = my_board.get_row(1);
		auto final_cond = c4::board::count_contiguous_cells(diagonal, c4::cell_content::X) == 2;
		BOOST_TEST(final_cond);
	}
};
//NOLINTEND(readability-convert-member-functions-to-static)


auto init_unit_test_suite(int, char **) -> boost::unit_test::test_suite*
{
	using boost::unit_test::framework::master_test_suite;
	std::shared_ptr<board_test> board_tester(new board_test);

	master_test_suite().add(BOOST_TEST_CASE([board_tester] { board_tester->test_horizontal(); }));
	master_test_suite().add(BOOST_TEST_CASE([board_tester] { board_tester->test_vertical(); }));
	master_test_suite().add(BOOST_TEST_CASE([board_tester] { board_tester->test_diagonal(); }));
	master_test_suite().add(BOOST_TEST_CASE([board_tester] { board_tester->test_count(); }));
	return nullptr; 
}

