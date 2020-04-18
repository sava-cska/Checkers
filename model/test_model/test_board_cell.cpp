#include "test_board_cell.hpp"
#include "board_cell.hpp"

void Test_board_cell::test_init()
{
	board_cell a(3, 5), b(0, -10), c(500, 500);
	CPPUNIT_ASSERT(a.x == 3 && a.y == 5);
	CPPUNIT_ASSERT(b.x == 0 && b.y == -10);
	CPPUNIT_ASSERT(c.x == 500 && c.y == 500);
	return;
}

void Test_board_cell::test_eq()
{
	board_cell a(3, 5), b(-10, 0), c(-10, 0), d(3, 5);
	CPPUNIT_ASSERT(a != b);
	CPPUNIT_ASSERT(a != c);
	CPPUNIT_ASSERT(b == c);
	CPPUNIT_ASSERT(d == a);
	return;
}
