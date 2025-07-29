///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cGameId.hpp"

// gTest grouping class
class test_cGameId : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cGameId : public cGameId
  {
  public:
    // add here members for free access.
    using cGameId::cGameId; // delegate constructors
  };

};
 
TEST_F(test_cGameId, test_ctor )
{
  Test_cGameId t;
}

