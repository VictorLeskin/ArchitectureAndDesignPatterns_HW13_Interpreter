#ifndef TEST_CFACTORY_HPP
#define TEST_CFACTORY_HPP

#include "cIoC.hpp"
#include "cGame.hpp"
#include "cInterpretCommand.hpp"
#include "cSpaceShip.hpp"
#include "cMessage.hpp"

extern const char str_SpaceShip[];
extern const char str_moveTo[];
extern const char str_refuel[];

class Test_cFactory : public cFactory
{
public:
	static cGame* createGame(std::string id) { return new cGame(id); }
	static cSpaceShip* createSpaceShip(std::string id) { return new cSpaceShip(id); }
	static cOperationData* createSerializeObj(const std::string& objId, const std::string& operationId)
	{
		// change to map
		if (objId.starts_with(str_SpaceShip) && operationId == str_moveTo)
			return new TOperation< str_SpaceShip, str_moveTo, cVector>;
		if (objId.starts_with(str_SpaceShip) && operationId == str_refuel)
			return new TOperation<str_SpaceShip, str_refuel, cTanker>;

		return nullptr;
	}

	static iCommand* createInterpretCommand(sInterpretCommandData sd)
	{
		cGame* game = sd.game;
		const cMessage& msg = *sd.msg;

		// get game 
		cMsgHeader h;
		std::istringstream strm(msg.Header());
		nlohmann::json j = nlohmann::json::parse(strm);
		from_json(j, h);

		cOperationData* p = createSerializeObj(h.objId.id, h.operationId.id);
		p->from_json(msg.Parameters().c_str());

		return new cInterpretCommand(game, h.objId.id, h.operationId.id, std::shared_ptr<cOperationData>(p));
	}
};

#endif //#ifndef TEST_CFACTORY_HPP
