//
// Created by pospelov on 21.04.2020.
//

#include "Event.hpp"
#include "Player.hpp"

controller::Event::~Event() {}

controller::MoveEvent::MoveEvent(BoardCell from, BoardCell to)
    : from(from), to(to) {}

controller::MoveEvent::~MoveEvent() {}

bool controller::process(MoveEvent *move, controller::IPlayer *player,
                         controller::IPlayer *enemy, GameState &game_state,
                         const std::string &mode) {
  std::cerr << "OK!\n";
  if (move != nullptr) {
    std::cerr << "MODE: " << mode << "\n";
    std::cerr << int(game_state.who_moves()) << " " << int(player->turn)
              << "\n";
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
  }
  return true;
}