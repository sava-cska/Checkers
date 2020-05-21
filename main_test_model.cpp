#include "test_model/TestBoardCell.hpp"
#include "test_model/TestGame.hpp"
#include "test_model/TestGameState.hpp"

int main() {
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(TestBoardCell::suite());
  runner.addTest(TestGameState::suite());
  runner.addTest(TestGame::suite());
  runner.run();
  return 0;
}
