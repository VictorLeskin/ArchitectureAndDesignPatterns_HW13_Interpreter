///************************* OUTS HOMEWORK ****************************************

#include "cInterpretCommand.hpp"
#include "cMessage.hpp"
#include "cGame.hpp"
#include "cSpaceShip.hpp"

void cInterpretCommand::Execute()
{
  game->Execute(*this);
}

void to_json(nlohmann::json& j, const cTanker& v)
{
	j = nlohmann::json
	{
			{ "fuel", v.fuel }
	};

}

void from_json(const nlohmann::json& j, cTanker& v)
{
	j.at("fuel").get_to(v.fuel);
}
