#include "CompPlayer.hpp"
#include <algorithm>

static const int INF = (int) 1e9;

int CompPlayer::score(GameState G) const
{
	int ordw = 0, ordb = 0, queenw = 0, queenb = 0, killw = 0, killb = 0;
	for (int i = 0; i < G.SIZE; i++)
		for (int j = 0; j < G.SIZE; j++)
		{
			if (G.board[i][j] == 'w') ordw++;
			if (G.board[i][j] == 'b') ordb++;
			if (G.board[i][j] == 'W') queenw++;
			if (G.board[i][j] == 'B') queenb++;
			if ((G.board[i][j] == 'w' || G.board[i][j] == 'W')
				&& G.kill(FIRST, BoardCell(i, j))) killw++;
			if ((G.board[i][j] == 'b' || G.board[i][j] == 'B')
				&& G.kill(SECOND, BoardCell(i, j))) killb++;
		}
	return ordw - ordb + queenw * queenw * queenw - queenb * queenb * queenb 
			+ killw * killw - killb * killb;
}

std::pair <int, Move> CompPlayer::alpha_beta(GameState G, int alpha, int beta,
					clock_t start_time, int seconds, int deep, std::mt19937 gen)
{
	state current = G.check_win();
	if (current != GAME)
	{
		if (current == DRAW) return std::make_pair(0, Move());
		if (current == FIRST_WIN) return std::make_pair(INF, Move());
		return std::make_pair(-INF, Move());
	}
	if (deep == 0) return std::make_pair(score(G), Move());
	clock_t current_time = clock();
	if (1.0 * (current_time - start_time) / CLOCKS_PER_SEC > seconds)
		return std::make_pair(score(G), Move());

	number_of_player player = G.who_moves();
	std::vector <Move> kill;
	std::vector <Move> ordinary;
	for (int i = 0; i < G.SIZE; i++)
		for (int j = 0; j < G.SIZE; j++)
		{
			std::vector <BoardCell> correct = G.get_list_of_correct_moves(player, BoardCell(i, j));
			for (int z = 0; z < (int) correct.size(); z++)
			{
				if (G.is_kill(player, BoardCell(i, j), correct[z]))
					kill.push_back(Move(BoardCell(i, j), correct[z]));
				else
					ordinary.push_back(Move(BoardCell(i, j), correct[z]));
			}
		}
	shuffle(kill.begin(), kill.end(), gen);
	shuffle(ordinary.begin(), ordinary.end(), gen);
	Move best_move;
	int current_score = (player == FIRST ? -INF : INF);
	for (int i = 0; i < (int) kill.size(); i++)
	{
		GameState cop = G;
		cop.move(player, kill[i].from, kill[i].to);
		std::pair <int, Move> result = alpha_beta(cop, alpha, beta, 
								start_time, seconds, deep - 1, gen);
		if (player == FIRST)
		{
			if (result.first >= current_score)
			{
				best_move = kill[i];
				current_score = result.first;
			}
			alpha = std::max(alpha, result.first);
			if (alpha > beta) return std::make_pair(alpha, kill[i]);
		}	
		else
		{
			if (result.first <= current_score)
			{
				best_move = kill[i];
				current_score = result.first;
			}
			beta = std::min(beta, result.first);
			if (alpha > beta) return std::make_pair(beta, kill[i]);
		}
	}
	for (int i = 0; i < (int) ordinary.size(); i++)
	{
		GameState cop = G;
		cop.move(player, ordinary[i].from, ordinary[i].to);
		std::pair <int, Move> result = alpha_beta(cop, alpha, beta, 
										start_time, seconds, deep - 1, gen);
		if (player == FIRST)
		{
			if (result.first >= current_score)
			{
				best_move = ordinary[i];
				current_score = result.first;
			}
			alpha = std::max(alpha, result.first);
			if (alpha > beta) return std::make_pair(alpha, ordinary[i]);
		}	
		else
		{
			if (result.first <= current_score)
			{
				best_move = ordinary[i];
				current_score = result.first;
			}
			beta = std::min(beta, result.first);
			if (alpha > beta) return std::make_pair(beta, ordinary[i]);
		}
	}
	return std::make_pair(current_score, best_move);
}

Move CompPlayer::get_next_move(GameState G, int seconds, int deep)
{
	std::mt19937 gen(time(0));
	clock_t start = clock();
	std::pair <int, Move> result = alpha_beta(G, -INF, INF, start, seconds, deep, gen);
	return result.second;
}
