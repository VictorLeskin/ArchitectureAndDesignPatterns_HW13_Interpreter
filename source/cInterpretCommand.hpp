///************************* OUTS HOMEWORK ****************************************
#ifndef CINTERPRETCOMMAND_HPP
#define CINTERPRETCOMMAND_HPP

#include "iCommand.hpp"
#include "cException.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include "cVector.hpp"

#include "cSpaceShip.hpp"


class cOperationData;
class cGame;
class cMessage;
class cTanker;

inline void to_json(nlohmann::json& j, const cVector& v)
{
	j = nlohmann::json
	{
			{ "x", v.x },
			{ "y", v.y }
	};
}

inline void from_json(const nlohmann::json& j, cVector& v)
{
	j.at("x").get_to(v.x);
	j.at("y").get_to(v.y);
}

void to_json(nlohmann::json& j, const cTanker& v);
void from_json(const nlohmann::json& j, cTanker& v);

class cOperationData
{
public:
	virtual void from_json(const char* sz) = 0;
};

template<const char* type, const char* action>
class TAction : public cOperationData
{
public:
	void from_json(const char* sz) override {}
};

template<const char* type, const char* command, typename DATA>
class TOperation : public cOperationData
{
public:
	void from_json(const char* sz) override
	{
		nlohmann::json j = nlohmann::json::parse(sz);
		::from_json(j, t);
	};
	DATA t;
};


struct sInterpretCommandData
{
	cGame* game;
	const cMessage *msg;
};

class cInterpretCommand : public iCommand
{
public:
	cInterpretCommand(cGame* game, const std::string& objId, const std::string& operationId, const std::shared_ptr<cOperationData>& operationData)
		:game(game), objId(objId), operationId(operationId), operationData(operationData)
	{
	}

	virtual void Execute();
	virtual const char* Type() { return typeid(*this).name(); }

	const std::string& ObjId() const { return objId; };
	const std::string& OperationId() const { return operationId; };
	const std::shared_ptr<cOperationData>& OperationData() const { return operationData; }

protected:		
	cGame* game;
	std::string objId, operationId;
	std::shared_ptr<cOperationData> operationData;

};


#endif //#ifndef CINTERPRETCOMMAND_HPP
