///************************* OUTS HOMEWORK ****************************************
#ifndef CMESSAGE_HPP
#define CMESSAGE_HPP

#include <string>
#include "cVector.hpp"
#include "nlohmann/json.hpp"

#include "cGameId.hpp"

class cOjectId { public: std::string id; };
class cOperationId { public: std::string id; };

class cMsgHeader
{
public:
	cMsgHeader() {}

public:
	virtual ~cMsgHeader() = default;

	cGameId gameId;
	cOjectId objId;
	cOperationId operationId;

};

class cGameOperation
{
public:
	cGameOperation() {}

public:
	virtual ~cGameOperation() = default;

	cGameId gameId;
	cOjectId objId;
	cOperationId operationId;
};


template<typename OPERATION_PARAMETERS>
class TGameOperation : public cGameOperation
{
public:
	TGameOperation()
	{
	}
	OPERATION_PARAMETERS operationParameters;
};

template<typename OPERATION_PARAMETERS>
inline void to_json(nlohmann::json& j, const TGameOperation<OPERATION_PARAMETERS>& operation )
{
	j["gameId"] = operation.gameId.id;
	j["objId"] = operation.objId.id;
	j["operationId"] = operation.operationId.id;
	j["operationParmeters"] = operation.operationParameters;
}

template<typename OPERATION_PARAMETERS>
inline void from_json(const nlohmann::json& j, TGameOperation<OPERATION_PARAMETERS>& operation)
{
	j.at("gameId").get_to(operation.gameId.id);
	j.at("objId").get_to(operation.objId.id);
	j.at("operationId").get_to(operation.operationId.id);
	j.at("operationParmeters").get_to(operation.operationParameters);
}

void to_json(nlohmann::json& j, const cVector & name);
void from_json(const nlohmann::json& j, cVector &name);
inline void to_json(nlohmann::json& j, const cMsgHeader& h)
{
	j["gameId"] = h.gameId.id;
	j["objId"] = h.objId.id;
	j["operationId"] = h.operationId.id;
}

inline void from_json(const nlohmann::json& j, cMsgHeader& h)
{
	j.at("gameId").get_to(h.gameId.id);
	j.at("objId").get_to(h.objId.id);
	j.at("operationId").get_to(h.operationId.id);
}

class cMessage
{
public:
	cMessage() {}
	cMessage(std::string sHeader, std::string sParameters) 
		: sHeader(sHeader), sParameters(sParameters) {}

	template<typename T_GAME_OPERATION>
	static cMessage Create(const T_GAME_OPERATION& operation)
	{
		cMessage msg;

		cMsgHeader header; 
		header.gameId = operation.gameId;
		header.objId = operation.objId;
		header.operationId = operation.operationId;

		nlohmann::json jHeader;
		to_json(jHeader, header);
		msg.sHeader = jHeader.dump();

		nlohmann::json jParameters;
		to_json(jParameters, operation.operationParameters);
		msg.sParameters = jParameters.dump();

		return msg;
	}

	const std::string& Header() const { return sHeader; }
	const std::string& Parameters() const { return sParameters; }

protected:
	std::string sHeader, sParameters;
};

#endif //#ifndef CMESSAGE_HPP
