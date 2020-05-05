#include "Player.hpp"
#include "Network.hpp"
#include "Event.hpp"

using namespace controller;

IPlayer::IPlayer(number_of_player turn) : turn(turn), enemyGaveUp(false), meGaveUp(false) {}

IPlayer::~IPlayer() {}

void IPlayer::add_move(const BoardCell &from, const BoardCell &to) {
  moves.push({from, to});
}

bool IPlayer::check_move() { return !moves.empty(); }

std::pair<BoardCell, BoardCell> IPlayer::get_move() const {
  return moves.front();
}

void IPlayer::pop_move() { moves.pop(); }

void IPlayer::enemy_gave_up() { enemyGaveUp = true; }

Player::Player(number_of_player turn)
    : IPlayer(turn) {}

Player::~Player() {}

bool Player::send_move(const BoardCell &from, const BoardCell &to) {
  return true;
}

NetworkPlayer::NetworkPlayer(number_of_player turn, Network &network)
    : IPlayer(turn), network(network) {}

NetworkPlayer::~NetworkPlayer() {}

bool NetworkPlayer::send_move(const BoardCell &from, const BoardCell &to) {
  return network.send_event(new MoveEvent(from, to));
}

void NetworkPlayer::enemy_gave_up() {
  enemyGaveUp = true;
  network.send_event(new GiveUpEvent());
}