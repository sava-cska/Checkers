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
  std::vector<int> opponent;

  int waiting = -1;

  bool running = true;
  while (running) {
    if (selector.wait()) {
      if (selector.isReady(listener)) {
        std::unique_ptr<sf::TcpSocket> client(new sf::TcpSocket);
        if (listener.accept(*client) == sf::Socket::Done) {
          selector.add(*client);
          std::cerr << client->getRemoteAddress() << " has just connected!\n";
          clients.emplace_back(std::move(client));
          opponent.push_back(waiting);
          if (waiting == -1) {
            waiting = clients.size() - 1;
          } else {
            opponent[waiting] = clients.size() - 1;
            opponent.back() = waiting;
            waiting = -1;
          }
        }
      } else {
        for (int i = 0; i < (int)clients.size(); i++) {
          if (clients[i] == nullptr) {
            continue;
          }
          sf::TcpSocket &client = *clients[i];
          if (selector.isReady(client)) {
            sf::Packet packet;
            if (client.receive(packet) == sf::Socket::Done) {
              std::cerr << client.getRemoteAddress() << " has just sent packet!\n";
              clients[opponent[i]]->send(packet);
            } else if (client.receive(packet) == sf::Socket::Disconnected) {
              std::cerr << client.getRemoteAddress() << " has disconnected!\n";

              selector.remove(client);

              clients[i].reset();

              if (opponent[i] != -1) {
                std::cerr << clients[opponent[i]]->getRemoteAddress()
                          << " disconnects...\n";
                selector.remove(*clients[opponent[i]]);

                clients[opponent[i]].reset();
              }
            }
            break;
          }
        }
      }
    }
  }
}