#include "Game.hpp"
#include "CompPlayer.hpp"
#include <iostream>

int main()
{
	Game game;
	CompPlayer AI;
	while (game.return_current_state().check_win() == GAME)
	{
		if (game.return_current_state().who_moves() == FIRST)
		{
			int x1, y1, x2, y2;
			std::cin >> x1 >> y1 >> x2 >> y2;
			game.move(FIRST, BoardCell(x1, y1), BoardCell(x2, y2));
		}
		else
		{
			Move cur = AI.get_next_move(game.return_current_state(), 10, 2);
			game.move(SECOND, cur.from, cur.to);
		}
		game.return_current_state().show();
	}
	return 0;
}
