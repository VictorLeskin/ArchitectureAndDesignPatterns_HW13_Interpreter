///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cInterpretCommand.hpp"

// gTest grouping class
class test_cInterpretCommand : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cInterpretCommand : public cInterpretCommand
  {
  public:
    // add here members for free access.
    using cInterpretCommand::cInterpretCommand; // delegate constructors

	void Execute() override {}
	const char* Type() override { return "Test_cInterpretCommand"; }
  };

};
 
TEST_F(test_cInterpretCommand, test_ctor )
{
  Test_cInterpretCommand t(nullptr,"","",nullptr);
}

