//
// Created by pospelov on 11.04.2020.
//

#include "Client.hpp"

#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <thread>

const int PORT_NUMBER = 24130;

int main() {
  sf::TcpSocket socket;
  std::string ipAddress;
  std::cout << "Enter ip address" << std::endl;
  std::cin >> ipAddress;

  sf::Socket::Status status = socket.connect(ipAddress, PORT_NUMBER);
  if (status != sf::Socket::Done) {
    std::cout << "Can't connect." << std::endl;
  } else {
    std::cout << "Successfully connected!" << std::endl;

    std::thread send([&socket] {
      std::string s;
      while (std::cin >> s) {
        sf::Packet packet;
        packet << s;
        socket.send(packet);
      }
    });

    std::thread receive([&socket] {
      while (true) {
        sf::Packet packet;
        socket.receive(packet);
        std::string s;
        packet >> s;
        std::cout << s << std::endl;
      }
    });

    send.join();
    receive.join();
  }
  return 0;
}