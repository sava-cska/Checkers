#include "BoardCell.hpp"

BoardCell::BoardCell(int a, int b) : x(a), y(b) {}

BoardCell::BoardCell(const BoardCell &cell) { x = cell.x, y = cell.y; }

bool BoardCell::operator==(BoardCell oth) const {
  return (x == oth.x) && (y == oth.y);
}

bool BoardCell::operator!=(BoardCell oth) const { return !(*this == oth); }

Move::Move(const BoardCell &cfrom, const BoardCell &cto)
    : from(cfrom), to(cto) {}
