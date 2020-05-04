#include "Event.hpp"
#include "Player.hpp"

controller::Event::Event(controller::EventType et) : type(et) {}

controller::MoveEvent::MoveEvent(BoardCell from, BoardCell to)
    : Event(controller::EventType::MOVE), from(from), to(to) { }

controller::MoveEvent::MoveEvent(sf::Packet &sf)
    : Event(controller::EventType::MOVE) {
  sf >> from.x >> from.y >> to.x >> to.y;
}

sf::Packet controller::MoveEvent::pack() const {
  sf::Packet packet;
  packet << static_cast<sf::Int32>(type) << from.x << from.y << to.x << to.y;
  return packet;
}

bool controller::process(MoveEvent *move, controller::IPlayer *player,
                         controller::IPlayer *enemy, GameState &game_state,
                         const std::string &mode) {
  if (move == nullptr) {
    return false;
  }

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
  return true;
}

controller::GiveUpEvent::GiveUpEvent() : Event(controller::EventType::GIVE_UP) {}

controller::GiveUpEvent::GiveUpEvent(sf::Packet &packet) {}

sf::Packet controller::GiveUpEvent::pack() const {
  sf::Packet packet;
  packet << static_cast<sf::Int32>(type);
  return packet;
}

bool controller::process(GiveUpEvent *giveUp, controller::IPlayer *player,
             controller::IPlayer *enemy, GameState &game_state,
             const std::string &mode) {
  if (giveUp == nullptr) {
    return false;
  }

  player->meGaveUp = true;
  enemy->enemyGaveUp = true;
  return true;
}

controller::Event* controller::unpack(sf::Packet &packet) {
  sf::Int32 type;
  packet >> type;
  controller::EventType eType = static_cast<controller::EventType>(type);
  Event *e = nullptr;
  switch (eType) {
  case controller::EventType::MOVE:
    e = new controller::MoveEvent(packet);
    break;
  case controller::EventType::GIVE_UP:
    e = new controller::GiveUpEvent(packet);
    break;
  }
  return e;
}
