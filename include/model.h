#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>

enum state {GAME, FIRST_WIN, SECOND_WIN, DRAW};

class Game_state
{
private:
	static const int SIZE = 8;
	static const int DRAW_MOVE = 15;

	char board[SIZE][SIZE];
	int who_last, move_to_draw, type_last;
	std::pair <int, int> last_move;

	bool check_ordinary(int player, std::pair <int, int> from, std::pair <int, int> to) const;
	bool check_queen(int player, std::pair <int, int> from, std::pair <int, int> to) const;
	bool check_move(int player, std::pair <int, int> from, std::pair <int, int> to) const;
	bool inside(std::pair <int, int> cell) const;
	bool kill(int who, std::pair <int, int> pos) const;
	std::pair <int, int> find_kill(int who) const;
public:
	Game_state();
	int who_moves() const;
	void move (int player, std::pair <int, int> from, std::pair <int, int> to);
	std::vector <std::pair <int, int> > get_list_of_correct_moves(int player, std::pair <int, int> from) const;
	state check_win() const;
};

class Game
{
private:
	std::vector <Game_state> game;
public:
	Game();
	int number_of_states() const;
	void return_to_state(int number);
	Game_state watch_state(int number) const;
};

#endif
