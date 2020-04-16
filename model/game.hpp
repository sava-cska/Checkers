#ifndef _GAME_HPP_
#define _GAME_HPP_

#include "game_state.hpp"

class Game {
private:
  std::vector<Game_state> game;
  Game_state current;
public:
  Game();

  int number_of_states() const;
  void return_to_state(int number);
  Game_state watch_state(int number) const;
  Game_state return_current_state() const;

  void move(number_of_player player, board_cell from, board_cell to);

  void load_from_file(const std::string &file);
  void save_to_file(const std::string &file) const;

  friend void XMLCALL endElement(void *userData, const XML_Char *name);
};

#endif
