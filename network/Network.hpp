//
// Created by pospelov on 18.04.2020.
//

#ifndef CHECKERS_NETWORK_NETWORK_HPP_
#define CHECKERS_NETWORK_NETWORK_HPP_

#include <SFML/Network.hpp>
#include <utility>
#include "game.hpp"

class Network {
public:
  Network(int = 24310);

  bool setup_server();

  bool connect_to_player(const sf::IpAddress &);

  bool send_move(const board_cell &, const board_cell &);

  bool get_enemy_move(board_cell &, board_cell &);

private:
  const int PORT;
  sf::TcpSocket enemy_socket;
};

#endif // CHECKERS_NETWORK_NETWORK_HPP_
