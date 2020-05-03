#ifndef _Game_HPP_
#define _Game_HPP_

#include "GameState.hpp"

class Game {
private:
  std::vector<GameState> game;
  GameState current;

public:
  Game();

  int number_of_states() const;
  void return_to_state(int number);
  GameState watch_state(int number) const;
  GameState return_current_state() const;

  void move(number_of_player player, BoardCell from, BoardCell to);

  void load_from_file(const std::string &file);
  void save_to_file(const std::string &file) const;

  friend void XMLCALL endElement(void *userData, const XML_Char *name);

  friend class TestGame;
};

#endif
