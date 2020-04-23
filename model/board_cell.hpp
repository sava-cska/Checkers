#ifndef _BOARD_CELL_HPP_
#define _BOARD_CELL_HPP_

struct board_cell {
public:
  int x, y;

public:
  board_cell(int a = 0, int b = 0);
  bool operator==(board_cell oth) const;
  bool operator!=(board_cell oth) const;
};

#endif
