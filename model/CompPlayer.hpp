#ifndef _CompPlayer_HPP_
#define _CompPlayer_HPP_

#include "GameState.hpp"
#include <ctime>
#include <random>

class CompPlayer
{
private:
	std::pair <int, Move> alpha_beta(GameState G, int alpha, int beta, 
						clock_t start_time, int seconds, int deep, std::mt19937 gen);
	int score(GameState G) const;
public:
	Move get_next_move(GameState G, int seconds, int deep);
};

#endif
