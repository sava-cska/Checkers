#ifndef CHECKERS_CONTROLLER_EVENT_HPP_
#define CHECKERS_CONTROLLER_EVENT_HPP_

#include "Game.hpp"

#include <SFML/Network.hpp>

namespace controller {
class IPlayer;

enum EventType { EVENT, MOVE, GIVE_UP };

class Event {
protected:
  const EventType type;

public:
  Event(EventType = EventType::EVENT);
  virtual ~Event() = default;

  virtual sf::Packet pack() const = 0;
};

class MoveEvent : public Event {
public:
  BoardCell from;
  BoardCell to;

public:
  MoveEvent(BoardCell, BoardCell);
  MoveEvent(sf::Packet &packet);
  ~MoveEvent() override = default;

  sf::Packet pack() const override;
};

bool process(MoveEvent *move, controller::IPlayer *player,
             controller::IPlayer *enemy, Game &game,
             const std::string &mode);

class GiveUpEvent : public Event {
public:
  GiveUpEvent();
  GiveUpEvent(sf::Packet &packet);
  ~GiveUpEvent() override = default;

  sf::Packet pack() const override;
};

bool process(GiveUpEvent *giveUp, controller::IPlayer *player,
             controller::IPlayer *enemy, Game &game,
             const std::string &mode);

Event *unpack(sf::Packet &packet);

} // namespace controller

#endif // CHECKERS_CONTROLLER_EVENT_HPP_
