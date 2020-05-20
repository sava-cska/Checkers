#ifndef _BoardCell_HPP_
#define _BoardCell_HPP_

#include <utility>

struct BoardCell {
public:
  int x, y;

public:
  BoardCell(int a = 0, int b = 0);
  BoardCell(const BoardCell &cell);
  bool operator==(BoardCell oth) const;
  bool operator!=(BoardCell oth) const;
};

struct Move {
public:
  BoardCell from, to;

public:
  Move(const BoardCell &cfrom = BoardCell(),
       const BoardCell &cto = BoardCell());
};

#endif
