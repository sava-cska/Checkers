//
// Created by pospelov on 18.04.2020.
//

#include "Network.hpp"
#include "Event.hpp"
#include <iostream>

using std::pair;

Network::Network(int port) : PORT(port), listening_now(0) {}

void Network::update() {
  sf::Packet packet;
  //  std::cerr << "no moves from enemy...\n";
  while (enemy_socket.receive(packet) == sf::Socket::Done) {
    BoardCell from, to;
    packet >> from.x >> from.y >> to.x >> to.y;
    std::cerr << "received move\n";
    events.push(new controller::MoveEvent(from, to));
  }
}

bool Network::setup_server() {
  if (listener.listen(PORT) != sf::Socket::Done) {
    return false;
  }

  std::cerr << "Listening on port: " << PORT << "!\n";

  if (listener.accept(enemy_socket) != sf::Socket::Done) {
    std::cerr << "Connecting error!\n";
    return false;
  }

  listener.close();

  std::cerr << enemy_socket.getRemoteAddress()
            << " has successfully connected!\n";
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

bool Network::send_move(const BoardCell &from, const BoardCell &to) {
  sf::Packet packet;
  packet << from.x << from.y << to.x << to.y;
  std::cerr << "sending move...\n";
  sf::Socket::Status status = enemy_socket.send(packet);
  while (status == sf::Socket::Partial) {
    status = enemy_socket.send(packet);
  }
  std::cerr << "move has sent!\n";
  return status == sf::Socket::Done;
}

std::queue<controller::Event *> &Network::get_events() { return events; }