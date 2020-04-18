#include "test_game_state.hpp"
#include "game_state.hpp"

void Test_game_state::test_init()
{
	Game_state g;
	CPPUNIT_ASSERT(g.who_last == SECOND);
	CPPUNIT_ASSERT(g.move_to_draw == 0);
	CPPUNIT_ASSERT(g.type_last == 0);
	CPPUNIT_ASSERT(g.last_move == board_cell(-1, -1));
	for (int i = 0; i < g.SIZE; i += 2)
	{
	CPPUNIT_ASSERT(g.board[1][i] == 'b' && g.board[g.SIZE - 1][i] == 'w' 
					&& g.board[g.SIZE - 3][i] == 'w');
	CPPUNIT_ASSERT(g.board[0][i] == '.' && g.board[2][i] == '.' 
					&& g.board[g.SIZE - 2][i] == '.');
	}
	for (int i = 1; i < g.SIZE; i += 2)
	{
	CPPUNIT_ASSERT(g.board[0][i] == 'b' && g.board[2][i] == 'b' 
					&& g.board[g.SIZE - 2][i] == 'w');
	CPPUNIT_ASSERT(g.board[1][i] == '.' && g.board[g.SIZE - 1][i] == '.' 
					&& g.board[g.SIZE - 3][i] == '.');
	}
	for (int i = 3; i < g.SIZE - 3; i++)
		for (int j = 0; j < g.SIZE; j++)
			CPPUNIT_ASSERT(g.board[i][j] == '.');
	return;
}

void Test_game_state::test_ordinary()
{
	Game_state g;
	for (int i = 0; i < g.SIZE; i++)
		for (int j = 0; j < g.SIZE; j++)
			g.board[i][j] = '.';
	g.board[0][5] = 'b';
	g.board[1][2] = 'b';
	g.board[1][4] = 'b';
	g.board[1][7] = 'b';
	g.board[2][3] = 'w';
	g.board[2][6] = 'b';
	g.board[3][2] = 'w';
	g.board[3][5] = 'w';
	g.board[4][2] = 'w';
	g.board[5][5] = 'w';
	g.board[6][4] = 'w';
	g.board[4][3] = 'b';
	CPPUNIT_ASSERT(g.check_ordinary(FIRST, board_cell(2, 3), board_cell(0, 1)));
	CPPUNIT_ASSERT(g.check_ordinary(FIRST, board_cell(3, 2), board_cell(2, 1)));
	CPPUNIT_ASSERT(!g.check_ordinary(FIRST, board_cell(1, 2), board_cell(3, 4)));
	CPPUNIT_ASSERT(!g.check_ordinary(FIRST, board_cell(3, 5), board_cell(3, 7)));
	CPPUNIT_ASSERT(!g.check_ordinary(FIRST, board_cell(5, 5), board_cell(6, 6)));
	CPPUNIT_ASSERT(g.check_ordinary(FIRST, board_cell(4, 2), board_cell(3, 3)));
	CPPUNIT_ASSERT(g.check_ordinary(FIRST, board_cell(3, 2), board_cell(5, 4)));

	CPPUNIT_ASSERT(!g.check_ordinary(SECOND, board_cell(4, 3), board_cell(2, 5)));
	CPPUNIT_ASSERT(g.check_ordinary(SECOND, board_cell(1, 2), board_cell(3, 4)));
	CPPUNIT_ASSERT(!g.check_ordinary(SECOND, board_cell(1, 2), board_cell(2, 2)));
	CPPUNIT_ASSERT(g.check_ordinary(SECOND, board_cell(0, 5), board_cell(1, 6)));
	CPPUNIT_ASSERT(g.check_ordinary(SECOND, board_cell(1, 2), board_cell(2, 1)));
	CPPUNIT_ASSERT(!g.check_ordinary(SECOND, board_cell(1, 2), board_cell(0, 3)));
	CPPUNIT_ASSERT(g.check_ordinary(SECOND, board_cell(4, 3), board_cell(2, 1)));
	return;
}

void Test_game_state::test_queen()
{
	Game_state g;
	for (int i = 0; i < g.SIZE; i++)
		for (int j = 0; j < g.SIZE; j++)
			g.board[i][j] = '.';
	g.board[1][2] = 'B';
	g.board[1][3] = 'B';
	g.board[1][5] = 'w';
	g.board[1][6] = 'B';
	g.board[2][6] = 'B';
	g.board[3][4] = 'w';
	g.board[3][7] = 'b';
	g.board[4][2] = 'w';
	g.board[4][6] = 'W';
	g.board[6][4] = 'b';
	g.board[6][7] = 'B';
	CPPUNIT_ASSERT(g.check_queen(FIRST, board_cell(4, 6), board_cell(0, 2)));
	CPPUNIT_ASSERT(g.check_queen(FIRST, board_cell(4, 6), board_cell(2, 4)));
	CPPUNIT_ASSERT(g.check_queen(FIRST, board_cell(4, 6), board_cell(5, 7)));
	CPPUNIT_ASSERT(!g.check_queen(FIRST, board_cell(4, 6), board_cell(4, 5)));
	CPPUNIT_ASSERT(!g.check_queen(FIRST, board_cell(6, 7), board_cell(0, 1)));
	CPPUNIT_ASSERT(!g.check_queen(FIRST, board_cell(1, 6), board_cell(4, 3)));

	CPPUNIT_ASSERT(g.check_queen(SECOND, board_cell(1, 6), board_cell(4, 3)));
	CPPUNIT_ASSERT(g.check_queen(SECOND, board_cell(1, 6), board_cell(7, 0)));
	CPPUNIT_ASSERT(!g.check_queen(SECOND, board_cell(2, 6), board_cell(4, 3)));
	CPPUNIT_ASSERT(g.check_queen(SECOND, board_cell(1, 3), board_cell(5, 7)));
	CPPUNIT_ASSERT(g.check_queen(SECOND, board_cell(2, 6), board_cell(5, 3)));
	CPPUNIT_ASSERT(!g.check_queen(SECOND, board_cell(4, 6), board_cell(3, 7)));
	return;
}

void Test_game_state::test_check_move()
{
	Game_state g;
	for (int i = 0; i < g.SIZE; i++)
		for (int j = 0; j < g.SIZE; j++)
			g.board[i][j] = '.';
	g.board[0][5] = 'b';
	g.board[1][2] = 'b';
	g.board[1][4] = 'b';
	g.board[1][7] = 'b';
	g.board[2][3] = 'w';
	g.board[2][6] = 'b';
	g.board[3][2] = 'w';
	g.board[3][5] = 'w';
	g.board[4][2] = 'w';
	g.board[5][5] = 'w';
	g.board[6][4] = 'w';
	g.board[4][3] = 'b';
	CPPUNIT_ASSERT(!g.check_move(FIRST, board_cell(0, 0), board_cell(1, 1)));
	CPPUNIT_ASSERT(!g.check_move(FIRST, board_cell(2, 3), board_cell(0, 5)));
	CPPUNIT_ASSERT(g.check_move(FIRST, board_cell(2, 3), board_cell(0, 1)));
	CPPUNIT_ASSERT(g.check_move(FIRST, board_cell(3, 2), board_cell(2, 1)));
	CPPUNIT_ASSERT(!g.check_move(FIRST, board_cell(6, 4), board_cell(8, 6)));
	CPPUNIT_ASSERT(!g.check_move(FIRST, board_cell(1, 2), board_cell(3, 4)));
	CPPUNIT_ASSERT(!g.check_move(FIRST, board_cell(3, 5), board_cell(3, 7)));
	CPPUNIT_ASSERT(!g.check_move(FIRST, board_cell(5, 5), board_cell(6, 6)));

	CPPUNIT_ASSERT(!g.check_move(SECOND, board_cell(4, 3), board_cell(2, 5)));
	CPPUNIT_ASSERT(!g.check_move(SECOND, board_cell(1, 7), board_cell(0, 8)));
	CPPUNIT_ASSERT(!g.check_move(SECOND, board_cell(1, 4), board_cell(3, 2)));
	CPPUNIT_ASSERT(g.check_move(SECOND, board_cell(1, 2), board_cell(3, 4)));
	CPPUNIT_ASSERT(!g.check_move(SECOND, board_cell(1, 2), board_cell(2, 2)));
	CPPUNIT_ASSERT(g.check_move(SECOND, board_cell(0, 5), board_cell(1, 6)));
	CPPUNIT_ASSERT(g.check_move(SECOND, board_cell(1, 2), board_cell(2, 1)));
	CPPUNIT_ASSERT(!g.check_move(SECOND, board_cell(1, 2), board_cell(0, 3)));
	CPPUNIT_ASSERT(g.check_move(SECOND, board_cell(4, 3), board_cell(2, 1)));

	for (int i = 0; i < g.SIZE; i++)
		for (int j = 0; j < g.SIZE; j++)
			g.board[i][j] = '.';
	g.board[1][2] = 'B';
	g.board[1][3] = 'B';
	g.board[1][5] = 'w';
	g.board[1][6] = 'B';
	g.board[2][6] = 'B';
	g.board[3][4] = 'w';
	g.board[3][7] = 'b';
	g.board[4][2] = 'w';
	g.board[4][6] = 'W';
	g.board[6][4] = 'b';
	g.board[6][7] = 'B';
	CPPUNIT_ASSERT(g.check_move(FIRST, board_cell(4, 6), board_cell(0, 2)));
	CPPUNIT_ASSERT(g.check_move(FIRST, board_cell(4, 6), board_cell(2, 4)));
	CPPUNIT_ASSERT(g.check_move(FIRST, board_cell(4, 6), board_cell(5, 7)));
	CPPUNIT_ASSERT(!g.check_move(FIRST, board_cell(4, 6), board_cell(4, 5)));
	CPPUNIT_ASSERT(!g.check_move(FIRST, board_cell(4, 6), board_cell(3, 7)));
	CPPUNIT_ASSERT(!g.check_move(FIRST, board_cell(6, 7), board_cell(0, 1)));
	CPPUNIT_ASSERT(!g.check_move(FIRST, board_cell(1, 6), board_cell(4, 3)));
	CPPUNIT_ASSERT(!g.check_move(FIRST, board_cell(4, 6), board_cell(6, 4)));
	
	CPPUNIT_ASSERT(g.check_move(SECOND, board_cell(1, 6), board_cell(4, 3)));
	CPPUNIT_ASSERT(g.check_move(SECOND, board_cell(1, 6), board_cell(7, 0)));
	CPPUNIT_ASSERT(!g.check_move(SECOND, board_cell(2, 6), board_cell(4, 3)));
	CPPUNIT_ASSERT(g.check_move(SECOND, board_cell(1, 3), board_cell(5, 7)));
	CPPUNIT_ASSERT(g.check_move(SECOND, board_cell(2, 6), board_cell(5, 3)));
	CPPUNIT_ASSERT(!g.check_move(SECOND, board_cell(4, 6), board_cell(3, 7)));
	CPPUNIT_ASSERT(!g.check_move(SECOND, board_cell(6, 7), board_cell(1, 2)));
	CPPUNIT_ASSERT(!g.check_move(SECOND, board_cell(1, 2), board_cell(2, 2)));
	return;
}

void Test_game_state::test_inside()
{
	Game_state g;
	CPPUNIT_ASSERT(g.inside(board_cell(0, 0)));
	CPPUNIT_ASSERT(!g.inside(board_cell(-1, 5)));
	CPPUNIT_ASSERT(g.inside(board_cell(7, 7)));
	CPPUNIT_ASSERT(!g.inside(board_cell(8, 0)));
	CPPUNIT_ASSERT(!g.inside(board_cell(8, 8)));
	CPPUNIT_ASSERT(g.inside(board_cell(0, 7)));
	return;
}

void Test_game_state::test_kill()
{
	Game_state g;
	for (int i = 0; i < g.SIZE; i++)
		for (int j = 0; j < g.SIZE; j++)
			g.board[i][j] = '.';
	g.board[0][5] = 'b';
	g.board[1][2] = 'b';
	g.board[1][4] = 'b';
	g.board[1][7] = 'b';
	g.board[2][3] = 'w';
	g.board[2][6] = 'b';
	g.board[3][2] = 'w';
	g.board[3][5] = 'w';
	g.board[4][2] = 'w';
	g.board[5][5] = 'w';
	g.board[6][4] = 'w';
	g.board[4][3] = 'b';
	CPPUNIT_ASSERT(g.kill(FIRST, board_cell(2, 3)));
	CPPUNIT_ASSERT(!g.kill(FIRST, board_cell(3, 5)));
	CPPUNIT_ASSERT(!g.kill(FIRST, board_cell(6, 4)));
	CPPUNIT_ASSERT(g.kill(FIRST, board_cell(3, 2)));

	CPPUNIT_ASSERT(g.kill(SECOND, board_cell(1, 2)));
	CPPUNIT_ASSERT(!g.kill(SECOND, board_cell(1, 4)));
	CPPUNIT_ASSERT(!g.kill(SECOND, board_cell(1, 7)));
	CPPUNIT_ASSERT(g.kill(SECOND, board_cell(4, 3)));

	for (int i = 0; i < g.SIZE; i++)
		for (int j = 0; j < g.SIZE; j++)
			g.board[i][j] = '.';
	g.board[1][2] = 'B';
	g.board[1][3] = 'B';
	g.board[1][5] = 'w';
	g.board[1][6] = 'B';
	g.board[2][6] = 'B';
	g.board[3][4] = 'w';
	g.board[3][7] = 'b';
	g.board[4][2] = 'w';
	g.board[4][6] = 'W';
	g.board[6][4] = 'b';
	g.board[6][7] = 'B';
	CPPUNIT_ASSERT(g.kill(FIRST, board_cell(4, 6)));
	CPPUNIT_ASSERT(!g.kill(FIRST, board_cell(3, 4)));
	CPPUNIT_ASSERT(!g.kill(FIRST, board_cell(1, 5)));
	CPPUNIT_ASSERT(!g.kill(FIRST, board_cell(6, 7)));

	CPPUNIT_ASSERT(g.kill(SECOND, board_cell(1, 2)));
	CPPUNIT_ASSERT(g.kill(SECOND, board_cell(1, 3)));
	CPPUNIT_ASSERT(!g.kill(SECOND, board_cell(4, 2)));
	CPPUNIT_ASSERT(g.kill(SECOND, board_cell(3, 7)));
	return;
}

void Test_game_state::test_find_kill()
{
	Game_state g;
	CPPUNIT_ASSERT(g.find_kill(FIRST) == board_cell(-1, -1));
	CPPUNIT_ASSERT(g.find_kill(SECOND) == board_cell(-1, -1));
	for (int i = 0; i < g.SIZE; i++)
		for (int j = 0; j < g.SIZE; j++)
			g.board[i][j] = '.';
	g.board[0][5] = 'b';
	g.board[1][2] = 'b';
	g.board[1][4] = 'b';
	g.board[1][7] = 'b';
	g.board[2][3] = 'w';
	g.board[2][6] = 'b';
	g.board[3][2] = 'w';
	g.board[3][5] = 'w';
	g.board[4][2] = 'w';
	g.board[5][5] = 'w';
	g.board[6][4] = 'w';
	g.board[4][3] = 'b';
	board_cell A = g.find_kill(FIRST);
	board_cell B = g.find_kill(SECOND);
	CPPUNIT_ASSERT(A == board_cell(2, 3) || A == board_cell(3, 2));
	CPPUNIT_ASSERT(B == board_cell(1, 2) || B == board_cell(2, 6) || B == board_cell(4, 3));

	for (int i = 0; i < g.SIZE; i++)
		for (int j = 0; j < g.SIZE; j++)
			g.board[i][j] = '.';
	g.board[1][2] = 'B';
	g.board[1][3] = 'B';
	g.board[1][5] = 'w';
	g.board[1][6] = 'B';
	g.board[2][6] = 'B';
	g.board[3][4] = 'w';
	g.board[3][7] = 'b';
	g.board[4][2] = 'w';
	g.board[4][6] = 'W';
	g.board[6][4] = 'b';
	g.board[6][7] = 'B';
	A = g.find_kill(FIRST);
	CPPUNIT_ASSERT(A == board_cell(4, 6));
	return;
}

void Test_game_state::test_who_moves()
{
	Game_state g;
	CPPUNIT_ASSERT(g.who_moves() == FIRST);
	for (int i = 0; i < g.SIZE; i++)
		for (int j = 0; j < g.SIZE; j++)
			g.board[i][j] = '.';
	g.board[0][5] = 'b';
	g.board[1][2] = 'b';
	g.board[1][4] = 'b';
	g.board[1][7] = 'b';
	g.board[2][3] = 'w';
	g.board[2][6] = 'b';
	g.board[3][2] = 'w';
	g.board[3][5] = 'w';
	g.board[4][2] = 'w';
	g.board[5][5] = 'w';
	g.board[6][4] = 'w';
	g.board[4][3] = 'b';
	g.last_move = board_cell(2, 3);
	g.who_last = FIRST;
	g.type_last = 1;
	CPPUNIT_ASSERT(g.who_moves() == FIRST);
	g.last_move = board_cell(3, 5);
	CPPUNIT_ASSERT(g.who_moves() == SECOND);
	g.type_last = 0;
	g.last_move = board_cell(2, 3);
	CPPUNIT_ASSERT(g.who_moves() == SECOND);
	g.who_last = SECOND;
	g.last_move = board_cell(4, 3);
	g.type_last = 0;
	CPPUNIT_ASSERT(g.who_moves() == FIRST);

	for (int i = 0; i < g.SIZE; i++)
		for (int j = 0; j < g.SIZE; j++)
			g.board[i][j] = '.';
	g.board[1][2] = 'B';
	g.board[1][3] = 'B';
	g.board[1][5] = 'w';
	g.board[1][6] = 'B';
	g.board[2][6] = 'B';
	g.board[3][4] = 'w';
	g.board[3][7] = 'b';
	g.board[4][2] = 'w';
	g.board[4][6] = 'W';
	g.board[6][4] = 'b';
	g.board[6][7] = 'B';
	g.last_move = board_cell(4, 6);
	g.who_last = FIRST;
	g.type_last = 0;
	CPPUNIT_ASSERT(g.who_moves() == SECOND);
	g.type_last = 1;
	CPPUNIT_ASSERT(g.who_moves() == FIRST);
	g.who_last = SECOND;
	g.last_move = board_cell(4, 2);
	g.type_last = 1;
	CPPUNIT_ASSERT(g.who_moves() == FIRST);
	return;
}

void Test_game_state::test_move()
{
	Game_state g;
	for (int i = 0; i < g.SIZE; i++)
		for (int j = 0; j < g.SIZE; j++)
			g.board[i][j] = '.';
	g.board[1][2] = 'B';
	g.board[1][5] = 'w';
	g.board[1][6] = 'B';
	g.board[2][6] = 'B';
	g.board[3][4] = 'w';
	g.board[3][7] = 'b';
	g.board[4][2] = 'w';
	g.board[4][6] = 'W';
	g.board[6][7] = 'W';
	Game_state cop = g;
	g.move(FIRST, board_cell(3, 4), board_cell(4, 3));
	CPPUNIT_ASSERT(!(cop != g));
	cop = g;
	g.move(SECOND, board_cell(6, 7), board_cell(2, 3));
	CPPUNIT_ASSERT(!(cop != g));
	
	g.who_last = FIRST;
	g.type_last = 0;
	g.last_move = board_cell(6, 7);
	cop = g;
	g.move(SECOND, board_cell(1, 2), board_cell(4, 5));
	for (int i = 0; i < g.SIZE; i++)
		for (int j = 0; j < g.SIZE; j++)
			if (board_cell(i, j) != board_cell(1, 2) && board_cell(i, j) != board_cell(3, 4) && board_cell(i, j) != board_cell(4, 5)) CPPUNIT_ASSERT(g.board[i][j] == cop.board[i][j]);
	CPPUNIT_ASSERT(g.board[1][2] == '.');
	CPPUNIT_ASSERT(g.board[3][4] == '.');
	CPPUNIT_ASSERT(g.board[4][5] == 'B');

	cop = g;
	g.move(FIRST, board_cell(4, 6), board_cell(5, 5));
	for (int i = 0; i < g.SIZE; i++)
		for (int j = 0; j < g.SIZE; j++)
			if (board_cell(i, j) != board_cell(4, 6) && board_cell(i, j) != board_cell(6, 7) && board_cell(i, j) != board_cell(5, 5)) CPPUNIT_ASSERT(g.board[i][j] == cop.board[i][j]);
	CPPUNIT_ASSERT(g.board[6][7] == '.');
	CPPUNIT_ASSERT(g.board[4][6] == '.');
	CPPUNIT_ASSERT(g.board[5][5] == 'W');
	return;
}

void Test_game_state::test_get_list()
{
	Game_state g;
	for (int i = 0; i < g.SIZE; i++)
		for (int j = 0; j < g.SIZE; j++)
			g.board[i][j] = '.';
	g.board[1][2] = 'B';
	g.board[1][3] = 'B';
	g.board[1][5] = 'w';
	g.board[1][6] = 'B';
	g.board[2][6] = 'B';
	g.board[3][4] = 'w';
	g.board[3][7] = 'b';
	g.board[4][2] = 'w';
	g.board[4][6] = 'W';
	g.board[6][4] = 'b';
	g.board[6][7] = 'W';
	std::vector <board_cell> A {board_cell(4, 5), board_cell(5, 6), board_cell(7, 6)};
	std::vector <board_cell> B {board_cell(5, 5)};
	std::vector <board_cell> C {board_cell(7, 3), board_cell(7, 5)};
	std::vector <board_cell> D {board_cell(0, 2), board_cell(2, 4), board_cell(3, 5), 
					board_cell(5, 5), board_cell(5, 7), board_cell(7, 3)};

	CPPUNIT_ASSERT(g.get_list_of_correct_moves(FIRST, board_cell(6, 7)) == A);
	CPPUNIT_ASSERT(g.get_list_of_correct_moves(FIRST, board_cell(4, 6)) == D);
	g.who_last = FIRST;
	CPPUNIT_ASSERT(g.get_list_of_correct_moves(SECOND, board_cell(3, 7)) == B);
	CPPUNIT_ASSERT(g.get_list_of_correct_moves(SECOND, board_cell(6, 4)) == C);
	return;
}

void Test_game_state::test_check_win()
{
	Game_state g;
	CPPUNIT_ASSERT(g.check_win() == GAME);
	g.move_to_draw = 20;
	CPPUNIT_ASSERT(g.check_win() == DRAW);
	g.move_to_draw = 0;

	for (int i = 0; i < g.SIZE; i++)
		for (int j = 0; j < g.SIZE; j++)
			g.board[i][j] = '.';
	for (int i = 0; i < g.SIZE; i++)
		g.board[0][i] = 'b', g.board[1][i] = 'w';
	g.who_last = SECOND;
	CPPUNIT_ASSERT(g.check_win() == SECOND_WIN);
	g.who_last = FIRST;
	CPPUNIT_ASSERT(g.check_win() == GAME);
	return;
}

void Test_game_state::test_get_cell()
{
	Game_state g;
	for (int i = 0; i < g.SIZE; i += 2)
	{
		CPPUNIT_ASSERT(g.get_cell(board_cell(0, i)) == '.');
		CPPUNIT_ASSERT(g.get_cell(board_cell(1, i)) == 'b');
		CPPUNIT_ASSERT(g.get_cell(board_cell(2, i)) == '.');
		CPPUNIT_ASSERT(g.get_cell(board_cell(g.SIZE - 3, i)) == 'w');
		CPPUNIT_ASSERT(g.get_cell(board_cell(g.SIZE - 2, i)) == '.');
		CPPUNIT_ASSERT(g.get_cell(board_cell(g.SIZE - 1, i)) == 'w');
	}
	for (int i = 1; i < g.SIZE; i += 2)
	{
		CPPUNIT_ASSERT(g.get_cell(board_cell(0, i)) == 'b');
		CPPUNIT_ASSERT(g.get_cell(board_cell(1, i)) == '.');
		CPPUNIT_ASSERT(g.get_cell(board_cell(2, i)) == 'b');
		CPPUNIT_ASSERT(g.get_cell(board_cell(g.SIZE - 3, i)) == '.');
		CPPUNIT_ASSERT(g.get_cell(board_cell(g.SIZE - 2, i)) == 'w');
		CPPUNIT_ASSERT(g.get_cell(board_cell(g.SIZE - 1, i)) == '.');
	}
	return;
}

void Test_game_state::test_neq()
{
	Game_state g1, g2, g3;
	g3.move_to_draw++;
	CPPUNIT_ASSERT(!(g1 != g2));
	CPPUNIT_ASSERT(g1 != g3);
	return;
}
