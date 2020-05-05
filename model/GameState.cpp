#include "GameState.hpp"
#include <cassert>
#include <iostream>

GameState::GameState() {
  who_last = SECOND;
  move_to_draw = type_last = 0;
  last_move = BoardCell(-1, -1);

  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      board[i][j] = '.';
  for (int j = 0; j < SIZE; j += 2)
    board[1][j] = 'b', board[SIZE - 3][j] = 'w', board[SIZE - 1][j] = 'w';
  for (int j = 1; j < SIZE; j += 2)
    board[0][j] = 'b', board[2][j] = 'b', board[SIZE - 2][j] = 'w';
  return;
}

bool GameState::inside(BoardCell cell) const {
  return (cell.x >= 0 && cell.x < SIZE && cell.y >= 0 && cell.y < SIZE);
}

bool GameState::check_ordinary(number_of_player player, BoardCell from,
                               BoardCell to) const {
  if ((player == SECOND && board[from.x][from.y] == 'w') ||
      (player == FIRST && board[from.x][from.y] == 'b'))
    return false;
  int dx;
  char oth1, oth2;
  if (player == FIRST)
    dx = -1, oth1 = 'B', oth2 = 'b';
  else
    dx = 1, oth1 = 'W', oth2 = 'w';

  if (to == BoardCell(from.x + dx, from.y - 1) ||
      to == BoardCell(from.x + dx, from.y + 1))
    return true;
  for (int dx = -1; dx <= 1; dx += 2)
    for (int dy = -1; dy <= 1; dy += 2)
      if (to == BoardCell(from.x + dx * 2, from.y + dy * 2) &&
          (board[from.x + dx][from.y + dy] == oth1 ||
           board[from.x + dx][from.y + dy] == oth2))
        return true;
  return false;
}

bool GameState::check_queen(number_of_player player, BoardCell from,
                            BoardCell to) const {
  if ((player == SECOND && board[from.x][from.y] == 'W') ||
      (player == FIRST && board[from.x][from.y] == 'B'))
    return false;
  if (to.x + to.y != from.x + from.y && to.x - to.y != from.x - from.y)
    return false;

  int cntb = 0, cntw = 0, dy = (to.x + to.y == from.x + from.y ? -1 : 1);
  while (to != from) {
    if (board[to.x][to.y] == 'w' || board[to.x][to.y] == 'W')
      cntw++;
    if (board[to.x][to.y] == 'b' || board[to.x][to.y] == 'B')
      cntb++;
    if (to.x < from.x)
      to.x++, to.y += dy;
    else
      to.x--, to.y -= dy;
  }
  if (player == FIRST)
    if (cntw == 0 && cntb <= 1)
      return true;
    else
      return false;
  else if (cntb == 0 && cntw <= 1)
    return true;
  else
    return false;
}

bool GameState::check_move(number_of_player player, BoardCell from,
                           BoardCell to) const {
  if (!inside(from) || !inside(to))
    return false;
  if (board[from.x][from.y] == '.')
    return false;
  if (board[to.x][to.y] != '.')
    return false;

  if (board[from.x][from.y] == 'w' || board[from.x][from.y] == 'b')
    return check_ordinary(player, from, to);

  return check_queen(player, from, to);
}

bool GameState::kill(number_of_player who, BoardCell pos) const {
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++) {
      if (!check_move(who, pos, BoardCell(i, j)))
        continue;
      BoardCell cur = BoardCell(i, j);
      bool fl = false;
      int dy = (i + j == pos.x + pos.y ? -1 : 1);
      while (cur.x != pos.x) {
        if (board[cur.x][cur.y] != '.')
          fl = true;
        if (cur.x < pos.x)
          cur.x++, cur.y += dy;
        else
          cur.x--, cur.y -= dy;
      }
      if (fl)
        return true;
    }
  return false;
}

BoardCell GameState::find_kill(number_of_player who) const {
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      if (kill(who, BoardCell(i, j)))
        return BoardCell(i, j);
  return BoardCell(-1, -1);
}

bool GameState::is_kill(number_of_player who, BoardCell from,
                        BoardCell to) const {
  if (!check_move(who, from, to))
    return false;

  bool fl = false;
  int dy = (from.x + from.y == to.x + to.y ? -1 : 1);
  BoardCell cur = to;
  while (cur.x != from.x) {
    if (board[cur.x][cur.y] != '.')
      fl = true;
    if (cur.x < from.x)
      cur.x++, cur.y += dy;
    else
      cur.x--, cur.y -= dy;
  }
  return fl;
}

char GameState::get_cell(BoardCell cell) const {
  assert(inside(cell));
  return board[cell.x][cell.y];
}

number_of_player GameState::who_moves() const {
  if (type_last == 0) {
    if (who_last == FIRST)
      return SECOND;
    else
      return FIRST;
  }
  if (kill(who_last, last_move))
    return who_last;
  else {
    if (who_last == FIRST)
      return SECOND;
    else
      return FIRST;
  }
}

void GameState::move(number_of_player player, BoardCell from, BoardCell to) {
  if (who_moves() != player)
    return;
  if (!check_move(player, from, to))
    return;
  if (player == who_last)
    if (from != last_move)
      return;

  int dy = (to.x + to.y == from.x + from.y ? -1 : 1);
  BoardCell cop = to;
  bool die = false;
  while (cop != from) {
    if (board[cop.x][cop.y] != '.')
      die = true;
    board[cop.x][cop.y] = '.';
    if (cop.x < from.x)
      cop.x++, cop.y += dy;
    else
      cop.x--, cop.y -= dy;
  }
  if (die) {
    std::swap(board[to.x][to.y], board[from.x][from.y]);
    who_last = player;
    move_to_draw = 0;
    type_last = 1;
    last_move = to;
  } else {
    BoardCell pos = find_kill(player);
    if (pos != BoardCell(-1, -1))
      board[pos.x][pos.y] = '.';
    std::swap(board[to.x][to.y], board[from.x][from.y]);
    who_last = player;
    if (board[from.x][from.y] == 'W' || board[from.x][from.y] == 'B')
      move_to_draw++;
    type_last = 0;
    last_move = to;
  }
  if (player == FIRST && to.x == 0 && board[to.x][to.y] == 'w')
    board[to.x][to.y] = 'W';
  if (player == SECOND && to.x == 7 && board[to.x][to.y] == 'b')
    board[to.x][to.y] = 'B';
  return;
}

std::vector<BoardCell>
GameState::get_list_of_correct_moves(number_of_player player,
                                     BoardCell from) const {
  std::vector<BoardCell> pos;
  if (who_moves() != player)
    return pos;
  if (player == who_last && from != last_move)
    return pos;

  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      if (check_move(player, from, BoardCell(i, j)))
        pos.push_back(BoardCell(i, j));
  return pos;
}

state GameState::check_win() const {
  if (move_to_draw >= DRAW_MOVE)
    return DRAW;
  number_of_player player = who_moves();
  for (int i1 = 0; i1 < SIZE; i1++)
    for (int j1 = 0; j1 < SIZE; j1++)
      for (int i2 = 0; i2 < SIZE; i2++)
        for (int j2 = 0; j2 < SIZE; j2++)
          if (check_move(player, BoardCell(i1, j1), BoardCell(i2, j2)))
            return GAME;
  if (player == FIRST)
    return SECOND_WIN;
  else
    return FIRST_WIN;
}

void GameState::show() const {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++)
      std::cout << board[i][j];
    std::cout << '\n';
  }
  return;
}

bool operator!=(const GameState &fir, const GameState &sec) {
  if (fir.who_last != sec.who_last)
    return true;
  if (fir.move_to_draw != sec.move_to_draw)
    return true;
  if (fir.type_last != sec.type_last)
    return true;
  if (fir.last_move != sec.last_move)
    return true;

  for (int i = 0; i < fir.SIZE; i++)
    for (int j = 0; j < fir.SIZE; j++)
      if (fir.board[i][j] != sec.board[i][j])
        return true;
  return false;
}

void GameState::save_to_file(std::ofstream &os) const {
  os << "<GameState>\n";

  os << "\t<board>\n";
  for (int i = 0; i < SIZE; i++) {
    os << "\t";
    for (int j = 0; j < SIZE; j++)
      os << board[i][j];
    os << "\n";
  }
  os << "\t</board>\n";

  os << "\t<who_move_last>\n\t";
  if (who_last == FIRST)
    os << 1;
  else
    os << 2;
  os << "\n\t</who_move_last>\n";
  os << "\t<he_kill>\n\t" << type_last << "\n\t</he_kill>\n";
  os << "\t<finish_cell_last_move>\n\t" << last_move.x << ' ' << last_move.y
     << "\n\t</finish_cell_last_move>\n";
  os << "\t<move_to_draw>\n\t" << move_to_draw << "\n\t</move_to_draw>\n";

  os << "</GameState>\n";
  return;
}
