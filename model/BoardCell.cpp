#include "BoardCell.hpp"

BoardCell::BoardCell(int a, int b) : x(a), y(b) {}

bool BoardCell::operator==(BoardCell oth) const {
  return (x == oth.x) && (y == oth.y);
}

bool BoardCell::operator!=(BoardCell oth) const { return !(*this == oth); }
