#include "Event.hpp"
#include "Player.hpp"
#include "draw_smf.hpp"
#include "game.hpp"

#include <iostream>
#include <string>

int main() {
  Gra core;
  //  Network network;

  std::string mode;
  std::cout << "Game mode" << std::endl;
  std::cin >> mode;

  Game_state game_state;
  Controller::IPlayer *player =
      new Controller::Player(number_of_player::FIRST, game_state);
  Controller::IPlayer *enemy = nullptr;

  if (mode == "multi") {
    //    enemy = new Controller::NetworkPlayer(number_of_turn::SECOND,
    //    network);
  } else if (mode == "single") {
    enemy = new Controller::Player(number_of_player::SECOND, game_state);
  }

  sf::RenderWindow window;

  while (core.window.isOpen()) {
    core.update(game_state);
    core.compiling_event(game_state);

    while (!core.get_events().empty()) {
      controller::Event *event = core.get_events().front();
      controller::MoveEvent *move =
          dynamic_cast<controller::MoveEvent *>(event);
      // example of processing.
      // TODO: This code should be encapsulated in MoveEvent.
      if (move != nullptr) {
        if (mode == "single") {
          if (game_state.who_moves() == player->turn) {
            player->add_move(move->from, move->to);
          } else {
            enemy->add_move(move->from, move->to);
          }
        } else {
          if (game_state.who_moves() == player->turn) {
            player->add_move(move->from, move->to);
          }
        }
        core.get_events().pop();
      }

      // currently, there is only MoveEvent.
      // TODO: need to process another events!
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
      enemy->pop_move();
    }

    core.drawing();
  }

  delete player;
  delete enemy;

  return 0;
}