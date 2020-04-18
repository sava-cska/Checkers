#ifndef _TEST_GAME_HPP_
#define _TEST_GAME_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

class Test_game : public CppUnit::TestFixture
{
private:
	void test_init();
	void test_number();
	void test_return_state();
	void test_watch_state();
	void test_return_current_state();
public:
	CPPUNIT_TEST_SUITE(Test_game);
	CPPUNIT_TEST(test_init);
	CPPUNIT_TEST(test_number);
	CPPUNIT_TEST(test_return_state);
	CPPUNIT_TEST(test_watch_state);
	CPPUNIT_TEST(test_return_current_state);
	CPPUNIT_TEST_SUITE_END();
};

#endif
