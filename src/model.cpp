#include "model.h"
#include <cassert>
#define pb push_back
#define mp make_pair
#define x first
#define y second

Game_state::Game_state()
{
	who_last = 2;
	move_to_draw = type_last = 0;
	last_move = std::mp(-1, -1);
	
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			board[i][j] = '.';
	for (int j = 0; j < SIZE; j += 2)
		board[1][j] = 'b', board[6][j] = 'w', board[8][j] = 'w';
	for (int j = 1; j < SIZE; j += 2)
		board[0][j] = 'b', board[2][j] = 'b', board[7][j] = 'w';
	return;
}

bool Game_state::inside(std::pair <int, int> cell) const
{
	return (cell.x >= 0 && cell.x < SIZE && cell.y >= 0 && cell.y < SIZE);
}

bool Game_state::check_ordinary(int player, std::pair <int, int> from, std::pair <int, int> to) const
{
	if ((player == 2 && board[from.x][from.y] == 'w') || (player == 1 && board[from.x][from.y] == 'b'))	
		return false;
	int dx;
	char oth1, oth2;
	if (player == 1) dx = -1, oth1 = 'B', oth2 = 'b';
	else dx = 1, oth1 = 'W', oth2 = 'w';

	if (to == std::mp(from.x + dx, from.y - 1) || to == std::mp(from.x + dx, from.y + 1)) return true;
	for (int dx = -1; dx <= 1; dx += 2)
		for (int dy = -1; dy <= 1; dy += 2)
			if (to == std::mp(from.x + dx * 2, from.y + dy * 2) && (board[from.x + dx][from.y + dy] == oth1 || 
				board[from.x + dx][from.y + dy] == oth2)) return true;
	return false;
}

bool Game_state::check_queen(int player, std::pair <int, int> from, std::pair <int, int> to) const
{
	if ((player == 2 && board[from.x][from.y] == 'W') || (player == 1 && board[from.x][from.y] == 'B'))	
		return false;
	if (to.x + to.y != from.x + from.y && to.x - to.y != from.x - from.y) return false;
	
	int cntb = 0, cntw = 0, dy = (to.x + to.y == from.x + from.y ? -1 : 1);
	while (to != from)
	{
		if (board[to.x][to.y] == 'w' || board[to.x][to.y] == 'W') cntw++;
		if (board[to.x][to.y] == 'b' || board[to.x][to.y] == 'B') cntb++;
		if (to.x < from.x) to.x++, to.y += dy;
		else to.x--, to.y -= dy;
	}
	if (player == 1)
		if (cntw == 0 && cntb <= 1) return true;
		else return false;
	else
		if (cntb == 0 && cntw <= 1) return true;
		else return false;
}

bool Game_state::check_move(int player, std::pair <int, int> from, std::pair <int, int> to) const
{
	if (!inside(from) || !inside(to)) return false;
	if (board[from.x][from.y] == '.') return false;
	if (board[to.x][to.y] != '.') return false;

	if (board[from.x][from.y] == 'w' || board[from.x][from.y] == 'b')
		return check_ordinary(player, from, to);
	
	return check_queen(player, from, to);
}

bool Game_state::kill(int who, std::pair <int, int> pos) const
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			if (!check_move(who, pos, std::mp(i, j))) continue;
			std::pair <int, int> cur = std::mp(i, j);
			bool fl = false;
			int dy = (i + j == pos.x + pos.y ? -1 : 1);
			while (cur.x != pos.x)
			{
				if (board[cur.x][cur.y] != '.') fl = true;
				if (cur.x < pos.x) cur.x++, cur.y += dy;
				else cur.x--, cur.y -= dy;
			}
			if (fl) return true;
		}
	return false;
}

std::pair <int, int> Game_state::find_kill(int who) const
{
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (kill(who, std::mp(i, j))) return std::mp(i, j);
	return std::mp(-1, -1);
}

int Game_state::who_moves() const
{
	if (type_last == 0) return 3 - who_last;
	if (kill(who_last, last_move)) return who_last;
	else return 3 - who_last;
}

void Game_state::move(int player, std::pair <int, int> from, std::pair <int, int> to)
{
	if (who_moves() != player) return;
	if (!check_move(player, from, to)) return;
	if (player == who_last)
		if (from != last_move) return;
	
	int dy = (to.x + to.y == from.x + from.y ? -1 : 1);
	std::pair <int, int> cop = to;
	bool die = false;
	while (cop != from)
	{
		if (board[cop.x][cop.y] != '.') die = true;
		board[cop.x][cop.y] = '.';
		if (cop.x < from.x) cop.x++, cop.y += dy;
		else cop.x--, cop.y -= dy;
	}
	if (die)
	{
		std::swap(board[to.x][to.y], board[from.x][from.y]);
		who_last = player;
		move_to_draw = 0;
		type_last = 1;
		last_move = to;
	}
	else
	{
		std::pair <int, int> pos = find_kill(player);
		if (pos != std::mp(-1, -1)) board[pos.x][pos.y] = '.';
		std::swap(board[to.x][to.y], board[from.x][from.y]);
		who_last = player;
		if (board[from.x][from.y] == 'W' || board[from.x][from.y] == 'B') move_to_draw++;
		type_last = 0;
		last_move = to;
	}
	if (player == 1 && to.x == 0 && board[to.x][to.y] == 'w') board[to.x][to.y] = 'W';
	if (player == 2 && to.x == 7 && board[to.x][to.y] == 'b') board[to.x][to.y] = 'B';
	return;
}

std::vector <std::pair <int, int> > Game_state::get_list_of_correct_moves
							(int player, std::pair <int, int> from) const
{
	std::vector <std::pair <int, int> > pos;
	if (who_moves() != player) return pos;
	if (player == who_last && from != last_move) return pos;

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			if (check_move(player, from, std::mp(i, j))) pos.pb(std::mp(i, j));
	return pos;
}

state Game_state::check_win() const
{
	if (move_to_draw >= DRAW_MOVE) return DRAW;
	int player = who_moves();
	for (int i1 = 0; i1 < SIZE; i1++)
		for (int j1 = 0; j1 < SIZE; j1++)
			for (int i2 = 0; i2 < SIZE; i2++)
				for (int j2 = 0; j2 < SIZE; j2++)
					if (check_move(player, std::mp(i1, j1), std::mp(i2, j2))) return GAME;
	if (player == 1) return SECOND_WIN;
	else return FIRST_WIN;
}

Game::Game()
{
	game.pb(Game_state());
}

int Game::number_of_states() const
{
	return (int) game.size();
}

void Game::return_to_state(int number)
{
	if (number < 0 || number >= (int) game.size()) assert(0);
	while ((int) game.size() != number + 1) game.pop_back();
	return;
}

Game_state Game::watch_state(int number) const
{
	if (number < 0 || number >= (int) game.size()) assert(0);
	return game[number];
}
