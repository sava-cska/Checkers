#ifndef _TestBoardCell_HPP_
#define _TestBoardCell_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

class TestBoardCell : public CppUnit::TestFixture
{
private:
	void test_init();
	void test_eq();
public:
	CPPUNIT_TEST_SUITE(TestBoardCell);
	CPPUNIT_TEST(test_init);
	CPPUNIT_TEST(test_eq);
	CPPUNIT_TEST_SUITE_END();
};


#endif
