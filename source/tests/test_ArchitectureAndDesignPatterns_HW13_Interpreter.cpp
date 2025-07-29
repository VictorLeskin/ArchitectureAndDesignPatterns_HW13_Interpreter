///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "ArchitectureAndDesignPatterns_HW13_Interpreter.hpp"


extern const char str_SpaceShip[] = "SpaceShip";
extern const char str_Game[] = "Game";
extern const char str_moveTo[] = "moveTo";
extern const char str_refuel[] = "refuel";


// gTest grouping class
class test_ArchitectureAndDesignPatterns_HW13_Interpreter : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_ArchitectureAndDesignPatterns_HW13_Interpreter : public ArchitectureAndDesignPatterns_HW13_Interpreter
  {
  public:
    // add here members for free access.
    using ArchitectureAndDesignPatterns_HW13_Interpreter::ArchitectureAndDesignPatterns_HW13_Interpreter; // delegate constructors
  };

};
 
TEST_F(test_ArchitectureAndDesignPatterns_HW13_Interpreter, test_ctor )
{
  Test_ArchitectureAndDesignPatterns_HW13_Interpreter t;
}

