///************************* OUTS HOMEWORK ****************************************
#ifndef CENDPOINT_HPP
#define CENDPOINT_HPP

#include <memory>
#include <map>
#include <string>

class cInterpretCommand;
class cMessage;
class cIoC;
class cGame;

#include "nlohmann/json.hpp"

class cEndPoint
{
public:

	void process(const cMessage& m);
	void set(cIoC& IoC) { ioc = &IoC; }

	void Register(cGame* game);

protected:
	std::map< std::string, cGame*> games;
	cIoC* ioc;
};

#endif //#ifndef CENDPOINT_HPP
