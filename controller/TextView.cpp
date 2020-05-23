//
// Created by pospelov on 20.05.2020.
//

#include "TextView.hpp"

#include "CompPlayer.hpp"
#include "Event.hpp"
#include "Game.hpp"
#include "Graphics.hpp"
#include "Network.hpp"
#include "Player.hpp"

#include "tclap/CmdLine.h"

#include <cassert>
#include <iostream>
#include <string>

static void parse_command_line(int argc, char **argv,
                               controller::IPlayer *&player,
                               controller::IPlayer *&enemy, Network &network,
                               std::string &mode) {
  try {
    TCLAP::CmdLine cmd("Simple checkers game", ' ', "0.1");
    TCLAP::ValueArg<std::string> modeArg("m", "mode", "game mode", true,
                                         "single", "single|client|server|ai|aivsai",
                                         cmd);

    TCLAP::ValueArg<std::string> ipArg("i", "ip", "remote ip address", false,
                                       "localhost", "string", cmd);

    TCLAP::ValueArg<std::string> playerTurnArg(
        "t", "turn", "player turn", false, "first", "first|second", cmd);

    TCLAP::ValueArg<int> secondsArg1("s", "seconds", "seconds for AI", false, 2,
                                     "integer [1, 10]", cmd);
    TCLAP::ValueArg<int> deepArg1("d", "deep", "deep for A/B algo", false, 3,
                                  "integer [1, 10]", cmd);

    TCLAP::ValueArg<int> secondsArg2("S", "Seconds", "seconds for AI-2", false, 2,
                                     "integer [1, 10]", cmd);
    TCLAP::ValueArg<int> deepArg2("D", "Deep", "deep for A/B algo-2", false, 3,
                                  "integer [1, 10]", cmd);


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
    } else if (mode == "ai") {
      player = new controller::Player(myTurn);
      enemy =
          new CompPlayer(enemyTurn, secondsArg1.getValue(), deepArg1.getValue());
    } else if (mode == "server") {
      player = new controller::Player(myTurn);
      enemy = new controller::NetworkPlayer(enemyTurn, network);
      network.setup_server();
    } else if (mode == "client") {
      if (!playerTurnArg.isSet()) {
        myTurn = number_of_player::SECOND;
        enemyTurn = number_of_player::FIRST;
      }
      player = new controller::Player(myTurn);
      enemy = new controller::NetworkPlayer(enemyTurn, network);
      network.connect_to_player(ip);
    } else if (mode == "aivsai") {
      player = new CompPlayer(myTurn, secondsArg1.getValue(), deepArg1.getValue());
      enemy =
          new CompPlayer(enemyTurn, secondsArg2.getValue(), deepArg2.getValue());
    }
  } catch (TCLAP::ArgException &e) {
    std::cerr << "error: " << e.error() << " arg " << e.argId() << std::endl;
  }
} // TODO: make special class for it!

static void print(const GameState &gs) {
  gs.show();
  std::cout << "Number of turn is: " << (gs.who_moves() == number_of_player::FIRST ? "FIRST" : "SECOND") << "\n";
}

static void get_move(controller::IPlayer *player, GameState &gs) {
  int x1, y1, x2, y2;
  std::cin >> x1 >> y1 >> x2 >> y2;
  BoardCell from(x1, y1), to(x2, y2);
  if (gs.check_move(gs.who_moves(), from, to)) {
    player->add_move(from, to);
  }
}

TextView::TextView(int argc, char **argv) {
  Network network;

  Game game_test;
  GameState& game_state = game_test.return_current_state();
  controller::IPlayer *player = nullptr;
  controller::IPlayer *enemy = nullptr;

  std::string mode;
  parse_command_line(argc, argv, player, enemy, network, mode);
  if (mode == "ai") {
    dynamic_cast<CompPlayer *>(enemy)->set_game_state(game_state);
  }

  assert(player != nullptr);
  assert(enemy != nullptr);

  bool printed = 0;

  while (game_state.check_win() == state::GAME) {

    if (!printed) {
      print(game_state);
      printed = 1;
    }

    network.update();
    game_state = game_test.return_current_state();

    if (game_state.who_moves() == player->turn) {
      get_move(player, game_state);
    } else if (mode == "single" && game_state.who_moves() == enemy->turn) {
      get_move(enemy, game_state);
    }

    while (!network.get_events().empty()) {
      controller::Event *event = network.get_events().front().get();
      controller::MoveEvent *move =
          dynamic_cast<controller::MoveEvent *>(event);
      controller::process(move, enemy, player, game_test,
                          mode); // overloaded in Event.hpp

      controller::GiveUpEvent *giveUp =
          dynamic_cast<controller::GiveUpEvent *>(event);
      controller::process(giveUp, enemy, player, game_test, mode);

      // currently, there is only MoveEvent.
      // TODO: need to process another events!
      network.get_events().pop();
    }

    if (player->check_move()) {
      auto move = player->get_move();
      enemy->send_move(move.first, move.second);
      game_state.move(player->turn, move.first, move.second);
      player->pop_move();

      printed = false;
    }

    if (enemy->check_move()) {
      auto move = enemy->get_move();
      player->send_move(move.first, move.second);
      game_state.move(enemy->turn, move.first, move.second);
      std::cerr << "MOVE!\n";
      enemy->pop_move();

      printed = false;
    }

    if ((game_state.check_win() == state::FIRST_WIN && player->turn == FIRST) ||
        (game_state.check_win() == state::SECOND_WIN &&
            player->turn == SECOND) ||
        player->enemyGaveUp) {
      std::cerr << "Player has won!\n";
      break;
    }

    if ((game_state.check_win() == state::FIRST_WIN && enemy->turn == FIRST) ||
        (game_state.check_win() == state::SECOND_WIN &&
            enemy->turn == SECOND) ||
        enemy->enemyGaveUp) {
      std::cerr << "Enemy has won!\n";
      break;
    }

    if (game_state.check_win() == state::DRAW) {
      std::cerr << "Draw!\n";
      break;
    }
  }

  delete player;
  delete enemy;
}