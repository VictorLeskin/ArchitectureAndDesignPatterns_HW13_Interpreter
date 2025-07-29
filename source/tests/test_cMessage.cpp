///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cMessage.hpp"
#include "cInterpretCommand.hpp"

// gTest grouping class
class test_cMessage : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cMessage : public cMessage
  {
  public:
    // add here members for free access.
    Test_cMessage(const cMessage& m) : cMessage(m) {}
    using cMessage::cMessage; // delegate constructors
  };

  struct Test_cOperationParameters
  {
    Test_cOperationParameters() {}
    Test_cOperationParameters(int type, cVector pos) : type(type), pos(pos) {}

    int type;
    cVector pos;
  };


};

void to_json(nlohmann::json& j, const test_cMessage::Test_cOperationParameters& operationParameters)
{
  j = nlohmann::json
  {
      { "type", operationParameters.type },
      { "pos", operationParameters.pos }
  };
}


void from_json(const nlohmann::json& j, test_cMessage::Test_cOperationParameters& operationParameters)
{
  j.at("type").get_to(operationParameters.type);
  j.at("pos").get_to(operationParameters.pos);
}





//TEST_F(test_cMessage, test_to_msg )
//{
//  TGameOperation<Test_cOperationParameters> k;
//  k.gameId = cGameId{ "gameId" };
//  k.objId = cOjectId{ "ojectId" };
//  k.operationId = cOperationId{ "operationId" };
//  k.operationParameters = Test_cOperationParameters{ 22, cVector(303,404) };
//
//  Test_cMessage t("");
//  cMessage::to_msg( t, k );
//  std::string res = R""""({"gameId":"gameId","objId":"ojectId","operationId":"operationId","operationParmeters":{"pos":{"x":303.0,"y":404.0},"type":22}})"""";
//  EXPECT_EQ(res, t.str());
//}
//
//TEST_F(test_cMessage, test_from_msg)
//{
//  std::string res = R""""({"gameId":"gameId","objId":"ojectId","operationId":"operationId","operationParmeters":{"pos":{"x":303.0,"y":404.0},"type":22}})"""";
//  cMessage t(res);
//
//  TGameOperation<Test_cOperationParameters> k;
//  cMessage::from_msg(t, k);
//
//  EXPECT_EQ(std::string("gameId"), k.gameId.id);
//  EXPECT_EQ(std::string("ojectId"), k.objId.id);
//  EXPECT_EQ(std::string("operationId"), k.operationId.id);
//  EXPECT_EQ(22, k.operationParameters.type);
//  EXPECT_EQ(303, k.operationParameters.pos.x );
//  EXPECT_EQ(404, k.operationParameters.pos.y);
//}

TEST_F(test_cMessage, test_Create )
{
    TGameOperation<Test_cOperationParameters> k;
    k.gameId = cGameId{ "gameId" };
    k.objId = cOjectId{ "ojectId" };
    k.operationId = cOperationId{ "operationId" };
    k.operationParameters = Test_cOperationParameters{ 22, cVector(303,404) };

    auto t = cMessage::Create(k);

    std::string resH = R""""({"gameId":"gameId","objId":"ojectId","operationId":"operationId"})"""";
    std::string resP = R""""({"pos":{"x":303.0,"y":404.0},"type":22})"""";
    EXPECT_EQ(resH, t.Header());
    EXPECT_EQ(resP, t.Parameters());
}
