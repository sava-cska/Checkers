//
// Created by pospelov on 18.04.2020.
//

#ifndef CHECKERS_NETWORK_NETWORK_HPP_
#define CHECKERS_NETWORK_NETWORK_HPP_

#include <SFML/Network.hpp>
#include <utility>
//#include "model.hpp"


class Network {
public:
  Network(int);

  bool setup_server();

  bool connect_to_player(const sf::IpAddress &);

  bool send_move(const std::pair<int, int> &, const std::pair<int, int> &);

  bool get_enemy_move(std::pair<int, int> &, std::pair<int, int> &);

private:
  const int PORT;
  sf::TcpSocket enemy_socket;
};

#endif // CHECKERS_NETWORK_NETWORK_HPP_
