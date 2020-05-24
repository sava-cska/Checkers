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
                               BoardCell to, bool &die) const {
  die = false;
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
           board[from.x + dx][from.y + dy] == oth2)) {
        die = true;
        return true;
      }
  return false;
}

bool GameState::check_queen(number_of_player player, BoardCell from,
                            BoardCell to, bool &die) const {
  die = false;
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
  die = (cntw + cntb > 0);
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
                           BoardCell to, bool &die) const {
  if (!inside(from) || !inside(to))
    return false;
  if (board[from.x][from.y] == '.')
    return false;
  if (board[to.x][to.y] != '.')
    return false;

  if (board[from.x][from.y] == 'w' || board[from.x][from.y] == 'b')
    return check_ordinary(player, from, to, die);

  return check_queen(player, from, to, die);
}

bool GameState::kill(number_of_player who, BoardCell pos) const {
  char small = (who == FIRST ? 'w' : 'b');
  char big = (who == FIRST ? 'W' : 'B');
  if (!inside(pos) || (board[pos.x][pos.y] != small && board[pos.x][pos.y] != big))
    return false;
  if (board[pos.x][pos.y] == small) {
      for (int sgn1 = -1; sgn1 <= 1; sgn1 += 2)
        for (int sgn2 = -1; sgn2 <= 1; sgn2 += 2) {
          bool die = false;
          if (check_move(who, pos, BoardCell(pos.x + 2 * sgn1, pos.y + 2 * sgn2), die))
            if (die)
              return true;
        }
    return false;
  }
  for (int c = 2; c <= SIZE; c++)
    for (int sgn1 = -1; sgn1 <= 1; sgn1 += 2)
      for (int sgn2 = -1; sgn2 <= 1; sgn2 += 2) {
        bool die = false;
        if (check_move(who, pos, BoardCell(pos.x + c * sgn1, pos.y + c * sgn2), die))
          if (die)
            return true;
        }
  return false;
}

bool GameState::find_kill(number_of_player who) const {
  char small = (who == FIRST ? 'w' : 'b');
  char big = (who == FIRST ? 'W' : 'B');
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      if ((board[i][j] == small || board[i][j] == big) && kill(who, BoardCell(i, j)))
        return true;
  return false;
}

char GameState::get_cell(BoardCell cell) const {
  if (!inside(cell)) assert(0);
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
  bool die = false;
  if (who_moves() != player)
    return;
  if (!check_move(player, from, to, die))
    return;
  if (player == who_last)
    if (from != last_move)
      return;

  int dy = (to.x + to.y == from.x + from.y ? -1 : 1);
  BoardCell cop = to;
  while (cop != from) {
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
    if (find_kill(player)) {
      return; // Запрещаю не рубить
      //board[pos.x][pos.y] = '.'; // Зафук
    }
    who_last = player;
    if (board[from.x][from.y] == 'W' || board[from.x][from.y] == 'B')
      move_to_draw++;
    type_last = 0;
    last_move = to;
    std::swap(board[to.x][to.y], board[from.x][from.y]);
  }
  if (player == FIRST && to.x == 0 && board[to.x][to.y] == 'w')
    board[to.x][to.y] = 'W';
  if (player == SECOND && to.x == 7 && board[to.x][to.y] == 'b')
    board[to.x][to.y] = 'B';
  return;
}

void GameState::get_list_of_correct_moves(number_of_player player, BoardCell from,
                                          std::vector <BoardCell> &moves) const {
  if (who_moves() != player)
    return;
  if (player == who_last && from != last_move)
    return;
  bool fl = kill(player, from);
  if (!fl && find_kill(player)) //Запрещаем не рубить
    return;
  
  int bound = (board[from.x][from.y] >= 'a' && board[from.x][from.y] <= 'z' ? 2 : SIZE);
  for (int c = 1; c <= bound; c++)
    for (int sgn1 = -1; sgn1 <= 1; sgn1 += 2)
      for (int sgn2 = -1; sgn2 <= 1; sgn2 += 2) {
        bool die = false;
        if (check_move(player, from, BoardCell(from.x + c * sgn1, from.y + c * sgn2), die)) {
          if (!fl || die)
            moves.push_back(BoardCell(from.x + c * sgn1, from.y + c * sgn2));
      }
    }
  return;
}

state GameState::check_win() const {
  if (move_to_draw >= DRAW_MOVE)
    return DRAW;
  number_of_player player = who_moves();
  char small = (player == FIRST ? 'w' : 'b');
  char big = (player == FIRST ? 'W' : 'B');
  for (int i1 = 0; i1 < SIZE; i1++)
    for (int j1 = 0; j1 < SIZE; j1++) {
      if (board[i1][j1] != small && board[i1][j1] != big)
        continue;
      for (int i2 = 0; i2 < SIZE; i2++)
        for (int j2 = 0; j2 < SIZE; j2++) {
          bool die = false;
          if (check_move(player, BoardCell(i1, j1), BoardCell(i2, j2), die))
            return GAME;
        }
    }
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
