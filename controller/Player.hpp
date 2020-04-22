//
// Created by pospelov on 21.04.2020.
//

#ifndef CHECKERS_CONTROLLER_PLAYER_HPP_
#define CHECKERS_CONTROLLER_PLAYER_HPP_

#include "game.hpp"
#include "Network.hpp"
#include <queue>

namespace Controller {

class IPlayer {
private:
  std::queue<std::pair<board_cell, board_cell>> moves;
public:
  number_of_player turn;

public:
  IPlayer(number_of_player);
  virtual ~IPlayer();

  virtual bool send_move(const board_cell &, const board_cell &) = 0;
  virtual void add_move(const board_cell &, const board_cell &);
  virtual bool check_move() const;
  virtual std::pair<board_cell, board_cell> get_move() const;
  virtual void pop_move();
};

class Player : public IPlayer {
private:
  Game_state &game_state;
public:
  Player(number_of_player, Game_state);
  ~Player() override;

  bool send_move(const board_cell &, const board_cell &) override;
};

class NetworkPlayer : public IPlayer {
private:
  Network &network;
public:
  NetworkPlayer(number_of_player, Network &);
  ~NetworkPlayer() override;

  bool send_move(const board_cell &, const board_cell &) override;
};

}

#endif // CHECKERS_CONTROLLER_PLAYER_HPP_
