#include "TestGame.hpp"
#include "Game.hpp"

void TestGame::test_init()
{
	Game g;
	CPPUNIT_ASSERT((int) g.game.size() == 1 && !(g.game[0] != g.current) && !(g.current != GameState()));
	return;
}

void TestGame::test_number()
{
	Game g;
	CPPUNIT_ASSERT(g.number_of_states() == 1);
	g.move(FIRST, BoardCell(5, 0), BoardCell(4, 1));
	CPPUNIT_ASSERT(g.number_of_states() == 2);
	g.move(FIRST, BoardCell(-1, -1), BoardCell(9, 9));
	CPPUNIT_ASSERT(g.number_of_states() == 2);
	return;
}

void TestGame::test_return_state()
{
	Game g;
	GameState cur1 = g.current;
	g.move(FIRST, BoardCell(5, 0), BoardCell(4, 1));
	g.move(SECOND, BoardCell(2, 1), BoardCell(3, 2));
	GameState cur2 = cur1;
	cur2.move(FIRST, BoardCell(5, 0), BoardCell(4, 1));
	GameState cur3 = cur2;
	cur3.move(SECOND, BoardCell(2, 1), BoardCell(3, 2));
	
	g.return_to_state(2);
	CPPUNIT_ASSERT((int) g.game.size() == 3 && !(g.game[0] != cur1) 
				&& !(g.game[1] != cur2) && !(g.game[2] != cur3) && !(g.current != cur3));
	g.return_to_state(0);
	CPPUNIT_ASSERT((int) g.game.size() == 1 && !(g.game[0] != cur1) 
					&& !(g.current != cur1));
	return;
}

void TestGame::test_watch_state()
{
	Game g;
	GameState cur1 = g.current;
	g.move(FIRST, BoardCell(5, 0), BoardCell(4, 1));
	g.move(SECOND, BoardCell(2, 1), BoardCell(3, 2));
	GameState cur2 = cur1;
	cur2.move(FIRST, BoardCell(5, 0), BoardCell(4, 1));
	GameState cur3 = cur2;
	cur3.move(SECOND, BoardCell(2, 1), BoardCell(3, 2));
	
	CPPUNIT_ASSERT(!(g.watch_state(2) != cur3));
	CPPUNIT_ASSERT(!(g.watch_state(1) != cur2));
	CPPUNIT_ASSERT(!(g.watch_state(0) != cur1));
	return;

}

void TestGame::test_return_current_state()
{
	Game g;
	GameState cur1 = g.current;
	g.move(FIRST, BoardCell(5, 0), BoardCell(4, 1));
	GameState cur2 = cur1;
	cur2.move(FIRST, BoardCell(5, 0), BoardCell(4, 1));
	CPPUNIT_ASSERT(!(g.return_current_state() != cur2));

	g.move(SECOND, BoardCell(2, 1), BoardCell(3, 2));
	GameState cur3 = cur2;
	cur3.move(SECOND, BoardCell(2, 1), BoardCell(3, 2));
	CPPUNIT_ASSERT(!(g.return_current_state() != cur3));
	return;
}
