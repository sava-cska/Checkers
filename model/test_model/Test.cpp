#include "TestBoardCell.hpp"
#include "TestGame.hpp"
#include "TestGameState.hpp"

int main() {
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(TestBoardCell::suite());
  runner.addTest(TestGameState::suite());
  runner.addTest(TestGame::suite());
  runner.run();
  return 0;
}
