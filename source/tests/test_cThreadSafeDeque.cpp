///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cMessagesDeque.hpp"

// gTest grouping class
class test_cThreadSafeDeque : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cThreadSafeDeque : public cMessagesDeque
  {
  public:
    // add here members for free access.
    using cMessagesDeque::cMessagesDeque; // delegate constructors
  };

};
 
TEST_F(test_cThreadSafeDeque, test_ctor )
{
  Test_cThreadSafeDeque t;
}

