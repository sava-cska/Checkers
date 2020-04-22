//
// Created by pospelov on 21.04.2020.
//

#include "Event.hpp"

using namespace controller;

Event::~Event() {}

MoveEvent::MoveEvent(board_cell from, board_cell to) : from(from), to(to) {}

MoveEvent::~MoveEvent() {}