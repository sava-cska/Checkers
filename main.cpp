#include "Event.hpp"
#include "Player.hpp"
#include "draw_smf.hpp"
#include "game.hpp"
#include "Network.hpp"

#include <iostream>
#include <string>
#include <cassert>

static void choose_game_mode(controller::IPlayer *&player,
                             controller::IPlayer *&enemy, Network &network, Game_state game_state, std::string &mode) {
  std::cout << "Game mode (single | server | client)" << std::endl;
  std::cin >> mode;
  if (mode == "single") {
    player = new controller::Player(number_of_player::FIRST, game_state);
    enemy = new controller::Player(number_of_player::SECOND, game_state);
  } else if (mode == "server") {
    player = new controller::Player(number_of_player::FIRST, game_state);
    enemy = new controller::NetworkPlayer(number_of_player::SECOND, network);
    network.setup_server();
  } else if (mode == "client") {
    std::string ip;
    std::cout << "Ip address" << std::endl;
    std::cin >> ip;
    player = new controller::Player(number_of_player::SECOND, game_state);
    enemy = new controller::NetworkPlayer(number_of_player::FIRST, network);
    network.connect_to_player(ip);
  }
} // TODO: make special class for it!

int main() { // TODO: make own main for every game mode
  Gra core;
  Network network;

  Game_state game_state;
  controller::IPlayer *player = nullptr;
  controller::IPlayer *enemy = nullptr;

  std::string mode;
  choose_game_mode(player, enemy, network, game_state, mode);

  assert(player != nullptr);
  assert(enemy != nullptr);

  while (core.window.isOpen()) {
    if (mode == "single" && game_state.who_moves() == enemy->turn) {
      core.update(game_state, enemy);
    } else {
      core.update(game_state, player);
    }
    core.compiling_event(game_state);
    network.update();

    while (!core.get_events().empty()) {
      controller::Event *event = core.get_events().front();
      controller::MoveEvent *move =
          dynamic_cast<controller::MoveEvent *>(event);
      controller::process(move, player, enemy, game_state,
                          mode); // overloaded in Event.hpp

      // currently, there is only MoveEvent.
      // TODO: need to process another events!
      core.get_events().pop();
    }

    while (!network.get_events().empty()) {
      controller::Event *event = network.get_events().front();
      controller::MoveEvent *move =
          dynamic_cast<controller::MoveEvent *>(event);
      controller::process(move, enemy, player, game_state,
                          mode); // overloaded in Event.hpp

      // currently, there is only MoveEvent.
      // TODO: need to process another events!
      network.get_events().pop();
    }

    while (player->check_move()) {
      auto move = player->get_move();
      enemy->send_move(move.first, move.second);
      game_state.move(player->turn, move.first, move.second);
      player->pop_move();
    }

    while (enemy->check_move()) {
      auto move = enemy->get_move();
      player->send_move(move.first, move.second);
      game_state.move(enemy->turn, move.first, move.second);
      std::cerr << "MOVE!\n";
      enemy->pop_move();
    }

    core.drawing();
  }

  delete player;
  delete enemy;

  return 0;
}