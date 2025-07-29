///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cMessagesDeque.hpp"

// gTest grouping class
class test_cMessagesDeque : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cMessagesDeque : public cMessagesDeque
  {
  public:
    // add here members for free access.
    using cMessagesDeque::cMessagesDeque; // delegate constructors
  };

};
 
TEST_F(test_cMessagesDeque, test_ctor )
{
  Test_cMessagesDeque t;
}

