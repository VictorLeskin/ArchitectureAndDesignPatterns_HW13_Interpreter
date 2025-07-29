///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cStopCommand.hpp"

// gTest grouping class
class test_cSoftStopCommand : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cSoftStopCommand : public cSoftStopCommand
  {
  public:
    // add here members for free access.
    using cSoftStopCommand::cSoftStopCommand; // delegate constructors
  };

};
 
TEST_F(test_cSoftStopCommand, test_ctor )
{
  Test_cSoftStopCommand t(nullptr);
}

