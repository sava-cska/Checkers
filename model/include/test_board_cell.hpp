#ifndef _TEST_BOARD_CELL_HPP_
#define _TEST_BOARD_CELL_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

class Test_board_cell : public CppUnit::TestFixture
{
private:
	void test_init();
	void test_eq();
public:
	CPPUNIT_TEST_SUITE(Test_board_cell);
	CPPUNIT_TEST(test_init);
	CPPUNIT_TEST(test_eq);
	CPPUNIT_TEST_SUITE_END();
};


#endif
