#include "test_board_cell.hpp"
#include "test_game_state.hpp"
#include "test_game.hpp"

int main()
{
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(Test_board_cell::suite());
	runner.addTest(Test_game_state::suite());
	runner.addTest(Test_game::suite());
	runner.run();
	return 0;
}
