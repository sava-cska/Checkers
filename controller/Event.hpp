//
// Created by pospelov on 21.04.2020.
//

#ifndef CHECKERS_CONTROLLER_EVENT_HPP_
#define CHECKERS_CONTROLLER_EVENT_HPP_

#include "game.hpp"

namespace controller {
class IPlayer;

class Event {
public:
  virtual ~Event();
};

class MoveEvent : public Event {
public:
  BoardCell from;
  BoardCell to;

public:
  MoveEvent(BoardCell, BoardCell);
  ~MoveEvent() override;
};

bool process(MoveEvent *move, controller::IPlayer *player,
             controller::IPlayer *enemy, GameState &game_state,
             const std::string &mode);

} // namespace controller

#endif // CHECKERS_CONTROLLER_EVENT_HPP_
