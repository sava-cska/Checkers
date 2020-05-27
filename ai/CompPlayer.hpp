#ifndef _CompPlayer_HPP_
#define _CompPlayer_HPP_

#include "GameState.hpp"
#include "Player.hpp"

class CompPlayer : public controller::IPlayer {
private:
  int seconds_;
  int deep_;

  static void alpha_beta(const GameState &G, int alpha, int beta, 
                         int deep, std::pair <int, Move> &total, bool flow);
  static int score(const GameState &G);
  Move get_next_move(const GameState &G, int seconds, int deep) const;

  mutable GameState gs;

  static const int NUMBER_OF_THREADS = 2;
public:
  CompPlayer(number_of_player, int seconds, int deep);

  virtual ~CompPlayer();

  void set_game_state(const GameState &);

  bool send_move(const BoardCell &, const BoardCell &) override;
  bool check_move() override;
};

#endif
