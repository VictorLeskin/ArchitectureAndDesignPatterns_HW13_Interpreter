///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cSpaceShip.hpp"

// gTest grouping class
class test_cSpaceShip : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cSpaceShip : public cSpaceShip
  {
  public:
    // add here members for free access.
    using cSpaceShip::cSpaceShip; // delegate constructors
  };

};
 
TEST_F(test_cSpaceShip, test_ctor )
{
  Test_cSpaceShip t("x");
}

