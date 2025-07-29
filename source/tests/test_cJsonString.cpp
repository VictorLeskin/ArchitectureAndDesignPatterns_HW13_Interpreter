///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cJsonString.hpp"

// gTest grouping class
class test_cJsonString : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cJsonString : public cJsonString
  {
  public:
    // add here members for free access.
    using cJsonString::cJsonString; // delegate constructors
  };

};
 
TEST_F(test_cJsonString, test_ctor )
{
  Test_cJsonString t;
}

