///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "cEndPoint.hpp"
#include "cMessage.hpp"
#include "cGame.hpp"
#include "cIoC.hpp"
#include "cSpaceShip.hpp"
#include "test_cFactory.hpp"

// gTest grouping class
class test_cEndPoint : public ::testing::Test
{
public:
  // additional class to access to member of tested class
  class Test_cEndPoint : public cEndPoint
  {
  public:
    // add here members for free access.
    using cEndPoint::cEndPoint; // delegate constructors
    using cEndPoint::process;
    using cEndPoint::games;
  };
};
 
TEST_F(test_cEndPoint, test_ctor )
{
  Test_cEndPoint t;
}

TEST_F(test_cEndPoint, test_Register)
{
    cGame* game = new cGame("AA");
    Test_cEndPoint t;

    t.Register(game);
    EXPECT_EQ(1, t.games.size());
    EXPECT_EQ(game, t.games["AA"]);
}

TEST_F(test_cEndPoint, test_process)
{
	// create message broker.
	cIoC IoC;
	Test_cEndPoint t;

	Test_cFactory f1;
	const cFactory& f11 = f1;

	// register factory ( only one scope )
	IoC.Resolve<iCommand>("Register", "A", f11)->Execute();

	// register two factory methods for game and spaceship
	IoC.Resolve<iCommand>("Register", "A", "cInterpretCommand", Test_cFactory::createInterpretCommand)->Execute();

	// create games 
	cGame* game1 = new cGame( std::string("Game #1"));
	cSpaceShip* spaceShip2 = new cSpaceShip( std::string("SpaceShip #2"));
	game1->Register(spaceShip2);

	t.Register(game1);
	t.set(IoC);

	// load two command to different games
	// moving direction for the first ship of the first game
	TGameOperation<cVector> moveTo;
	moveTo.gameId.id = "Game #1";
	moveTo.objId.id = "SpaceShip #1";
	moveTo.operationId.id = "moveTo";
	moveTo.operationParameters = cVector(23, 45);

	cMessage m1 = cMessage::Create(moveTo);

	EXPECT_EQ(0, game1->Deque().size());
	t.process(m1);
	EXPECT_EQ(1, game1->Deque().size());

	{
		TGameOperation<cVector> moveTo1;
		moveTo1.gameId.id = "Game #99";
		moveTo1.objId.id = "SpaceShip #1";
		moveTo1.operationId.id = "moveTo1";
		moveTo1.operationParameters = cVector(23, 45);

		cMessage m1 = cMessage::Create(moveTo1);

		EXPECT_EQ(1, game1->Deque().size());
		try
		{
			t.process(m1);
			FAIL();
		}
		catch (const std::exception& expected)
		{
			ASSERT_STREQ("There is not such registered game", expected.what());
		}
	}
}




