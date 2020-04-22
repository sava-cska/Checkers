#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

#include "board_cell.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <expat.h>

enum state { GAME, FIRST_WIN, SECOND_WIN, DRAW };
enum number_of_player { FIRST, SECOND };

class Game_state {
private:
  static const int SIZE = 8;
  static const int DRAW_MOVE = 15;

  number_of_player who_last;
  int move_to_draw, type_last;
  board_cell last_move;
  char board[SIZE][SIZE];

  bool check_ordinary(number_of_player player, board_cell from, board_cell to) const;
  bool check_queen(number_of_player player, board_cell from, board_cell to) const;
  bool inside(board_cell cell) const;
  bool kill(number_of_player who, board_cell pos) const;
  board_cell find_kill(number_of_player who) const;
public:
  Game_state();

  number_of_player who_moves() const;
  bool check_move(number_of_player player, board_cell from, board_cell to) const;
  void move(number_of_player player, board_cell from, board_cell to);
  std::vector<board_cell> get_list_of_correct_moves
              (number_of_player player, board_cell from) const;
  state check_win() const;
  char get_cell(board_cell cell) const;

  friend bool operator != (const Game_state &fir, const Game_state &sec);

  void save_to_file(std::ofstream &os) const;
  friend void XMLCALL dataElement (void *userData, const XML_Char *s, int len);

  friend class Test_game_state;
};

#endif
