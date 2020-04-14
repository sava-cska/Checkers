#include "model.h"
#include <iostream>
#include <string>

int main()
{
	Game game;
	Game_state g;
	std::string in, out;
	std::cin >> in >> out;
	game.load_from_file(in);
	g.move(1, std::make_pair(5, 0), std::make_pair(4, 1));
	game.add_state(g);
	game.save_to_file(out);
	return 0;
}
