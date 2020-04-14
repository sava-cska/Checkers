//
// Created by pospelov on 11.04.2020.
//

#include "Server.hpp"

#include <SFML/Network.hpp>
#include <iostream>
#include <list>

static const int PORT_NUMBER = 24130;

int main() {
  std::cout << "Server" << std::endl;
  sf::TcpListener listener;

  if (listener.listen(PORT_NUMBER) != sf::Socket::Done) {
    std::cout << "Server error!" << std::endl;
  }

  sf::SocketSelector selector;
  selector.add(listener);
  std::list<sf::TcpSocket *> clients;

  while (true) {
    if (selector.wait()) {
      if (selector.isReady(listener)) {
        sf::TcpSocket *client = new sf::TcpSocket;
        if (listener.accept(*client) != sf::Socket::Done) {
          delete client;
        } else {
          clients.push_back(client);
          selector.add(*client);
        }
      } else {
        for (sf::TcpSocket *client : clients) {
          if (selector.isReady(*client)) {
            sf::Packet packet;
            if (client->receive(packet) == sf::Socket::Done) {
              for (sf::TcpSocket *other_client : clients) {
                other_client->send(packet);
              }
            }
          }
        }
      }
    }
  }

  return 0;
}