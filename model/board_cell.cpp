#include "board_cell.hpp"

board_cell::board_cell(int a, int b) : x(a), y(b) {}

bool board_cell::operator==(board_cell oth) const {
  return (x == oth.x) && (y == oth.y);
}

bool board_cell::operator!=(board_cell oth) const { return !(*this == oth); }
