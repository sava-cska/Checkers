#include "Event.hpp"
#include "Network.hpp"
#include "Player.hpp"
#include "Graphics.hpp"
#include "Game.hpp"

#include "tclap/CmdLine.h"

#include <cassert>
#include <iostream>
#include <string>

static void parse_command_line(int argc, char ** argv, controller::IPlayer *&player,
                               controller::IPlayer *&enemy, Network &network,
                               std::string &mode) {
  try {
    TCLAP::CmdLine cmd("Simple checkers game", ' ', "0.1");
    TCLAP::ValueArg<std::string> modeArg("m", "mode", "game mode", true,
                                         "single", "single|client|server");
    cmd.add(modeArg);

    TCLAP::ValueArg<std::string> ipArg("i", "ip", "remote ip address", false,
                                       "localhost", "string");
    cmd.add(ipArg);

    TCLAP::ValueArg<std::string> playerTurnArg("t", "turn", "player turn",
                                               false, "first", "first|second");
    cmd.add(playerTurnArg);

    cmd.parse(argc, argv);

    mode = modeArg.getValue();
    std::string ip = ipArg.getValue();
    std::string playerTurn = playerTurnArg.getValue();

    number_of_player myTurn =
        (playerTurn == "first" ? number_of_player::FIRST
                               : number_of_player::SECOND);
    number_of_player enemyTurn =
        (playerTurn == "first" ? number_of_player::SECOND
                               : number_of_player::FIRST);

    if (mode == "single") {
      player = new controller::Player(myTurn);
      enemy = new controller::Player(enemyTurn);
    } else if (mode == "server") {
      player = new controller::Player(myTurn);
      enemy = new controller::NetworkPlayer(enemyTurn, network);
      network.setup_server();
    } else if (mode == "client") {
      player = new controller::Player(myTurn);
      enemy = new controller::NetworkPlayer(enemyTurn, network);
      network.connect_to_player(ip);
    }
  } catch (TCLAP::ArgException &e) {
    std::cerr << "error: " << e.error() << " arg " << e.argId() << std::endl;
  }
} // TODO: make special class for it!

int main(int argc, char **argv) { // TODO: make own main for every game mode
  Network network;

  GameState game_state;
  controller::IPlayer *player = nullptr;
  controller::IPlayer *enemy = nullptr;

  std::string mode;
  parse_command_line(argc, argv, player, enemy, network, mode);

  Gra core;

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