//
// Created by pospelov on 21.04.2020.
//

#ifndef CHECKERS_CONTROLLER_EVENT_HPP_
#define CHECKERS_CONTROLLER_EVENT_HPP_

#include "game.hpp"
#include "Player.hpp"

namespace controller {

class Event {
public:
  virtual ~Event();
};

class MoveEvent : public Event {
public:
  board_cell from;
  board_cell to;
public:
  MoveEvent(board_cell, board_cell);
  ~MoveEvent() override;
};

}

#endif // CHECKERS_CONTROLLER_EVENT_HPP_
