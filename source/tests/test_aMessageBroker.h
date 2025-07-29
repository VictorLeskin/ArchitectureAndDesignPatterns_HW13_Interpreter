#ifndef TEST_AMESSAGEBROKER_H
#define TEST_AMESSAGEBROKER_H

#include <gtest/gtest.h>

#include "aMessageBroker.hpp"
#include "cMessage.hpp"
#include <deque>


// gTest grouping class
class test_aMessageBroker : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_aMessageBroker : public aMessageBroker
  {
  public:
    std::deque<cMessage> msg;

    bool get(cMessage& m) override
    {
      if (false == msg.empty())
      {
        m = msg.front();
        msg.pop_front();
        return true;
      }
      else
        return false;
    }

    void put(cMessage& m)
    {
        msg.push_back(m);
    }
  public:
    // add here members for free access.
    using aMessageBroker::aMessageBroker; // delegate constructors
  };

};
#endif //#ifndef TEST_AMESSAGEBROKER_H
