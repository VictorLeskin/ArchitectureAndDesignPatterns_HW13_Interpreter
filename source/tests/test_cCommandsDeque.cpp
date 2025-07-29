///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cCommandsDeque.hpp"

// gTest grouping class
class test_cCommandsDeque : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cCommandsDeque : public cCommandsDeque
  {
  public:
    // add here members for free access.
    using cCommandsDeque::cCommandsDeque; // delegate constructors
  };

};
 
TEST_F(test_cCommandsDeque, test_ctor )
{
  Test_cCommandsDeque t;
}

