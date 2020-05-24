#ifndef _GameState_HPP_
#define _GameState_HPP_

#include "BoardCell.hpp"
#include <expat.h>
#include <fstream>
#include <iostream>
#include <vector>

enum state { GAME, FIRST_WIN, SECOND_WIN, DRAW };
enum number_of_player { FIRST, SECOND };

class GameState {
private:
  static const int SIZE = 8;
  static const int DRAW_MOVE = 15;

  number_of_player who_last;
  int move_to_draw, type_last;
  BoardCell last_move;
  char board[SIZE][SIZE];
  int white_up_down[SIZE][SIZE], white_down_up[SIZE][SIZE];
  int black_up_down[SIZE][SIZE], black_down_up[SIZE][SIZE];

  bool check_ordinary(number_of_player player, BoardCell from, BoardCell to, bool &die) const;
  bool check_queen(number_of_player player, BoardCell from, BoardCell to, bool &die) const;
  bool inside(BoardCell cell) const;
  bool kill(number_of_player who, BoardCell pos) const;
  bool find_kill(number_of_player who) const;

  void change_prefix(BoardCell pos, char news);
  void show() const;

public:
  GameState();
  GameState(const GameState &oth) = default;
  GameState& operator=(const GameState &oth) = default;

  number_of_player who_moves() const;
  bool check_move(number_of_player player, BoardCell from, BoardCell to, bool &die) const;
  void move(number_of_player player, BoardCell from, BoardCell to);
  void get_list_of_correct_moves(number_of_player player, BoardCell from, std::vector <BoardCell> &moves) const;
  state check_win() const;
  char get_cell(BoardCell cell) const;

  friend bool operator!=(const GameState &fir, const GameState &sec);

  void save_to_file(std::ofstream &os) const;
  friend void XMLCALL dataElement(void *userData, const XML_Char *s, int len);

  friend class TestGameState;
  friend class CompPlayer;
};

#endif
