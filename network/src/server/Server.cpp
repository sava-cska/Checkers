//
// Created by pospelov on 11.04.2020.
//

#include "Server.hpp"

#include <SFML/Network.hpp>
#include <iostream>

const int PORT_NUMBER = 24130;

int main() {
  std::cout << "Server" << std::endl;
  sf::TcpListener listener;

  if (listener.listen(PORT_NUMBER) != sf::Socket::Done) {
    std::cout << "Server error!" << std::endl;
  }

  sf::TcpSocket client;
  if (listener.accept(client) != sf::Socket::Done) {
    std::cout << "Error in accepting client" << std::endl;
  } else {
    std::cout << "Success!" << std::endl;
    sf::Packet packet;
    client.receive(packet);
    sf::Int32 x;
    packet >> x;
    std::cout << "Client has send: " << x << std::endl;
    packet.clear();
    packet << x * x;
    client.send(packet);
  }

}