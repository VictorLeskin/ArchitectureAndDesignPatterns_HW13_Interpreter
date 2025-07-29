///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "iCommand.hpp"

// gTest grouping class
class test_iCommand : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_iCommand : public iCommand
  {
  public:
    // add here members for free access.
    using iCommand::iCommand; // delegate constructors
  };

};
 
TEST_F(test_iCommand, test_ctor )
{
  //Test_iCommand t;
}

