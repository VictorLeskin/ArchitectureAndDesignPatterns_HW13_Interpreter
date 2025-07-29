///************************* OUTS HOMEWORK ****************************************

#include <gtest/gtest.h>

#include "ArchitectureAndDesignPatterns_HW13_Interpreter.hpp"
#include "cMessage.hpp"
#include "cEndPoint.hpp"
#include "cIoC.hpp"
#include "cMessagesDeque.hpp"
#include "cGame.hpp"
#include "cInterpretCommand.hpp"
#include "cSpaceShip.hpp"
#include "cStopCommand.hpp"

#include <iostream>
#include <nlohmann/json.hpp>
#include <tuple>
#include <memory>
#include <thread>

#include "test_aMessageBroker.h"
#include "test_cFactory.hpp"

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


TEST_F(test_ArchitectureAndDesignPatterns_HW13_Interpreter, test_sendMessage)
{
	using operation_parameters = std::tuple< int, cVector >;
	operation_parameters p{ 321,cVector(456,78) };
	TGameOperation<operation_parameters> op;

	op.gameId.id = "Game #1";
	op.objId.id = "Spaceship #1";
	op.operationId.id = "moveTo";
	op.operationParameters = p;

	cMessage msg = cMessage::Create(op);
	cMessagesDeque deq;

	deq.push_back(msg);

	EXPECT_EQ(1, deq.size());

	cMessage msg1;
	EXPECT_TRUE(deq.pop_front(msg1));
	EXPECT_EQ(0, deq.size());
}

TEST_F(test_ArchitectureAndDesignPatterns_HW13_Interpreter, test_EndpointCommonBehaviour)
{
	// create message broker.
	test_aMessageBroker::Test_aMessageBroker broker;
	cIoC IoC;
	cEndPoint endPoint;

	Test_cFactory f1, f2;
	const cFactory& f11 = f1;
	const cFactory& f12 = f2;

	// registering 

	// register factory ( only two scope one scope for each player )
	IoC.Resolve<iCommand>("Register", "A", f11)->Execute();
	IoC.Resolve<iCommand>("Register", "B", f12)->Execute();

	// register two factory methods for game and spaceship
	IoC.Resolve<iCommand>("Register", "A", "cGame", Test_cFactory::createGame)->Execute();
	IoC.Resolve<iCommand>("Register", "A", "cSpaceShip", Test_cFactory::createSpaceShip)->Execute();
	IoC.Resolve<iCommand>("Register", "A", "cInterpretCommand", Test_cFactory::createInterpretCommand)->Execute();

	IoC.Resolve<iCommand>("Register", "B", "cGame", Test_cFactory::createGame)->Execute();
	IoC.Resolve<iCommand>("Register", "B", "cSpaceShip", Test_cFactory::createSpaceShip)->Execute();
	IoC.Resolve<iCommand>("Register", "B", "cInterpretCommand", Test_cFactory::createInterpretCommand)->Execute();

	// create games 
	cGame* game1 = IoC.Resolve<cGame>("A", "cGame", std::string("Game #1"));
	cGame* game2 = IoC.Resolve<cGame>("B", "cGame", std::string("Game #2"));

	cSpaceShip* spaceShip1 = IoC.Resolve<cSpaceShip>("A", "cSpaceShip", std::string("SpaceShip #1"));
	cSpaceShip* spaceShip2 = IoC.Resolve<cSpaceShip>("A", "cSpaceShip", std::string("SpaceShip #2"));
	cSpaceShip* spaceShip3 = IoC.Resolve<cSpaceShip>("B", "cSpaceShip", std::string("SpaceShip #3"));
	cSpaceShip* spaceShip4 = IoC.Resolve<cSpaceShip>("B", "cSpaceShip", std::string("SpaceShip #4"));

	game1->Register(spaceShip1);
	game1->Register(spaceShip2);
	game2->Register(spaceShip3);
	game2->Register(spaceShip4);

	endPoint.Register(game1);
	endPoint.Register(game2);
	endPoint.set(IoC);

	// load two command to different games
	// moving direction for the first ship of the first game
	TGameOperation<cVector> moveTo;
	moveTo.gameId.id = "Game #1";
	moveTo.objId.id = "SpaceShip #1";
	moveTo.operationId.id = "moveTo";
	moveTo.operationParameters = cVector(23, 45);

	cMessage m1 = cMessage::Create(moveTo);
	broker.put(m1);

	// load bombs to the second ship of the second game
	TGameOperation<cTanker> refuel;
	refuel.gameId.id = "Game #2";
	refuel.objId.id = "SpaceShip #4";
	refuel.operationId.id = "refuel";
	cTanker tanker; tanker.fuel = 37;
	refuel.operationParameters = tanker;

	cMessage m2 = cMessage::Create(refuel);
	broker.put(m2);

	cMessage m;
	while (true == broker.get(m))
		endPoint.process(m);

	game1->detach();
	game2->detach();

	game1->play();
	game2->play();

	using namespace std::chrono_literals;
	std::this_thread::sleep_for(5s);

	std::shared_ptr<iCommand> softStopCmd1(new cSoftStopCommand(game1));
	std::shared_ptr<iCommand> softStopCmd2(new cSoftStopCommand(game2));

	game1->push_back(softStopCmd1);
	game2->push_back(softStopCmd2);

	const cObject* k = (*game1)["SpaceShip #1"];
	cVector posSpaceShip1 = ((const cSpaceShip*)k)->Position();
	EXPECT_EQ(23.0, posSpaceShip1.x);
	EXPECT_EQ(45.0, posSpaceShip1.y);

	const cObject* k2 = (*game2)["SpaceShip #4"];
	auto fuel = ((const cSpaceShip*)k2)->Fuel();
	EXPECT_EQ(25, fuel);
}
