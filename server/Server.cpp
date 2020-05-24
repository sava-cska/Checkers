//
// Created by pospelov on 24.05.2020.
//

#include "Server.hpp"
#include <thread>
#include <chrono>
#include <list>
#include <memory>

Server::Server(int port) : PORT(port) {
}

Server::Exception::Exception(std::string what) : std::logic_error(what) {}

void Server::run() {
  sf::TcpListener listener;
  if (listener.listen(PORT) != sf::Socket::Done) {
    throw Server::Exception("Error in binding port on " + std::to_string(PORT));
  }

  std::cerr << "Running...\n";
  std::cerr << "Waiting for clients.\n";

  std::vector<std::unique_ptr<sf::TcpSocket>> clients;
  sf::SocketSelector selector;
  selector.add(listener);

  bool running = true;
  while (running) {
    if (selector.wait()) {
      if (selector.isReady(listener)) {
        std::unique_ptr<sf::TcpSocket> client(new sf::TcpSocket);
        if (listener.accept(*client) == sf::Socket::Done) {
          selector.add(*client);
          std::cerr << client->getRemoteAddress() << " has just connected!\n";
          clients.emplace_back(std::move(client));
        }
      } else {
        for (int i = 0; i < 2; i++) {
          sf::TcpSocket &client = *clients[i];
          if (selector.isReady(client)) {
            sf::Packet packet;
            if (client.receive(packet) == sf::Socket::Done) {
              std::cerr << client.getRemoteAddress() << " has just sent packet!\n";
              clients[i ^ 1]->send(packet);
            } else if (client.receive(packet) == sf::Socket::Disconnected) {
              std::cerr << "OK, someone has disconnected, game is finished!\n";
              std::cerr << "Waiting for next clients!\n";
              for (auto &client : clients) {
                selector.remove(*client);
              }
              clients.clear();
              break;
            }
          }
        }
      }
    }
  }
}