///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cGame.hpp"

// gTest grouping class
class test_cGame : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cGame : public cGame
  {
  public:
    // add here members for free access.
    using cGame::cGame; // delegate constructors
  };

};
 
TEST_F(test_cGame, test_ctor )
{
  //Test_cGame t("name");
}

