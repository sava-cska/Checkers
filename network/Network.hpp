#ifndef CHECKERS_NETWORK_NETWORK_HPP_
#define CHECKERS_NETWORK_NETWORK_HPP_

#include "Game.hpp"
#include <SFML/Network.hpp>

#include <queue>
#include <string>
#include <utility>
#include <memory>

namespace controller {
class Event;
}

class Network {
public:
  Network(int = 24310);

  void update();
  bool setup_server();
  bool connect_to_player(const sf::IpAddress &);
  bool send_event(const controller::Event &e);

  std::queue<std::shared_ptr<controller::Event>> &get_events();

private:
  const int PORT;
  bool listening_now;
  sf::TcpListener listener;
  sf::TcpSocket enemy_socket;
  std::queue<std::shared_ptr<controller::Event>> events;

private:
};

#endif // CHECKERS_NETWORK_NETWORK_HPP_
