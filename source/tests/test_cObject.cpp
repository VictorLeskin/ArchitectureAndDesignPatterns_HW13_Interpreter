///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cObject.hpp"

// gTest grouping class
class test_cObject : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cObject : public cObject
  {
  public:
    // add here members for free access.
    using cObject::cObject; // delegate constructors
  };

};
 
TEST_F(test_cObject, test_ctor )
{
  Test_cObject t("name");
}

