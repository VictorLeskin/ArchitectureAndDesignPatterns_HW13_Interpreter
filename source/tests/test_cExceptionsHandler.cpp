///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cExceptionsHandler.hpp"

// gTest grouping class
class test_cExceptionsHandler : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cExceptionsHandler : public cExceptionsHandler
  {
  public:
    // add here members for free access.
    using cExceptionsHandler::cExceptionsHandler; // delegate constructors
  };

};
 
TEST_F(test_cExceptionsHandler, test_ctor )
{
  Test_cExceptionsHandler t;
}

