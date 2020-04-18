//
// Created by pospelov on 18.04.2020.
//

#include "Network.hpp"
#include <iostream>

using std::pair;

Network::Network(int port) : PORT(port) {
}

bool Network::setup_server() {
  sf::TcpListener listener;

  if (listener.listen(PORT) != sf::Socket::Done) {
    std::cerr << "Server error!\n";
    return false;
  }

  std::cerr << "OK!\n";

  if (listener.accept(enemy_socket) != sf::Socket::Done) {
    std::cerr << "Connecting error!\n";
    return false;
  }

  std::cerr << "OK!?\n";

//  listener.close();

  std::cerr << enemy_socket.getRemoteAddress() << " has successfully connected!\n";
  enemy_socket.setBlocking(false);

  return true;
}

bool Network::connect_to_player(const sf::IpAddress &ip_address) {
  if (enemy_socket.connect(ip_address, PORT) != sf::Socket::Done) {
    std::cerr << "Can't connect!\n";
    return false;
  }
  enemy_socket.setBlocking(false);
  std::cerr << "Successfully connected!";

  return true;
}

bool Network::send_move(const board_cell &from, const board_cell &to) {
  sf::Packet packet;
  packet << from.x << from.y << to.x << to.y;
  sf::Socket::Status status = enemy_socket.send(packet);
  while (status == sf::Socket::Partial) {
    status = enemy_socket.send(packet);
  }
  return status == sf::Socket::Done;
}

bool Network::get_enemy_move(board_cell &from, board_cell &to) {
  sf::Packet packet;
  if (enemy_socket.receive(packet) == sf::Socket::NotReady) {
    return false;
  }
  packet >> from.x >> from.y >> to.x >> to.y;
  return true;
}