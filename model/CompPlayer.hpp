#ifndef _CompPlayer_HPP_
#define _CompPlayer_HPP_

#include "GameState.hpp"
#include "Player.hpp"
#include <ctime>
#include <random>

class CompPlayer : public controller::IPlayer {
private:
  int seconds_;
  int deep_;

  std::pair<int, Move> alpha_beta(GameState G, int alpha, int beta,
                                  clock_t start_time, int seconds, int deep,
                                  std::mt19937 gen) const;
  int score(GameState G) const;
  Move get_next_move(GameState G, int seconds, int deep) const;

  mutable GameState gs;

public:
  CompPlayer(number_of_player, int seconds, int deep);

  virtual ~CompPlayer();

  void set_game_state(const GameState &);

  bool send_move(const BoardCell &, const BoardCell &) override;
  bool check_move() override;
};

#endif
