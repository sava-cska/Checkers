//
// Created by pospelov on 11.04.2020.
//

#include "Client.hpp"

#include <SFML/Network.hpp>
#include <iostream>
#include <string>

const int PORT_NUMBER = 24130;

int main() {
  sf::TcpSocket socket;
  std::string ipAddress;
  std::cout << "Enter ip address" << std::endl;
  std::cin >> ipAddress;

  sf::Socket::Status status = socket.connect(ipAddress, PORT_NUMBER);
  if (status != sf::Socket::Done) {
    std::cout << "Oups...";
  } else {
    std::cout << "Connected!\nEnter number" << std::endl;
    sf::Packet packet;
    sf::Int32 x;
    std::cin >> x;
    packet << x;
    socket.send(packet);
    socket.receive(packet);
    packet >> x;
    std::cout << "Server has answered: " << x << std::endl;
  }
  return 0;
}