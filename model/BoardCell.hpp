#ifndef _BoardCell_HPP_
#define _BoardCell_HPP_

struct BoardCell {
public:
  int x, y;

public:
  BoardCell(int a = 0, int b = 0);
  bool operator==(BoardCell oth) const;
  bool operator!=(BoardCell oth) const;
};

#endif
