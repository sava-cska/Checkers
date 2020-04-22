//
// Created by pospelov on 18.04.2020.
//

#ifndef CHECKERS_NETWORK_NETWORK_HPP_
#define CHECKERS_NETWORK_NETWORK_HPP_

#include <SFML/Network.hpp>
#include "game.hpp"
#include <utility>
#include <queue>
#include <string>

namespace controller {
  class Event;
}

class Network {
public:
  Network(int = 24310);

  void update();
  bool setup_server();
  bool connect_to_player(const sf::IpAddress &);
  bool send_move(const board_cell &, const board_cell &);

  std::queue<controller::Event *> &get_events();

private:
  const int PORT;
  bool listening_now;
  sf::TcpListener listener;
  sf::TcpSocket enemy_socket;
  std::queue<controller::Event *> events;

private:
};

#endif // CHECKERS_NETWORK_NETWORK_HPP_
