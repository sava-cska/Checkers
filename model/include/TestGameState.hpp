#ifndef _TestGameState_HPP_
#define _TestGameState_HPP_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

class TestGameState : public CppUnit::TestFixture {
private:
  void test_init();
  void test_ordinary();
  void test_queen();
  void test_check_move();
  void test_inside();
  void test_kill();
  void test_find_kill();
  void test_who_moves();
  void test_move();
  void test_get_list();
  void test_check_win();
  void test_get_cell();
  void test_neq();

public:
  CPPUNIT_TEST_SUITE(TestGameState);
  CPPUNIT_TEST(test_init);
  CPPUNIT_TEST(test_ordinary);
  CPPUNIT_TEST(test_queen);
  CPPUNIT_TEST(test_check_move);
  CPPUNIT_TEST(test_inside);
  CPPUNIT_TEST(test_kill);
  CPPUNIT_TEST(test_find_kill);
  CPPUNIT_TEST(test_who_moves);
  CPPUNIT_TEST(test_move);
  CPPUNIT_TEST(test_get_list);
  CPPUNIT_TEST(test_check_win);
  CPPUNIT_TEST(test_get_cell);
  CPPUNIT_TEST(test_neq);
  CPPUNIT_TEST_SUITE_END();
};

#endif
