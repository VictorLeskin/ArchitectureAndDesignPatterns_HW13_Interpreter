///************************* OUTS HOMEWORK ****************************************
#ifndef CSTOPCOMMAND_HPP
#define CSTOPCOMMAND_HPP

#include "iCommand.hpp"
#include <typeinfo>

class cGame;

// stop after deque empty
class cSoftStopCommand : public iCommand
{
public:
	cSoftStopCommand(cGame* s) : s(s) {}

	void Execute() override;

	const char* Type() override { return typeid(*this).name(); }

protected:
	cGame* s;
};

// stop after execution of this command
class cHardStopCommand : public iCommand
{
public:
	cHardStopCommand(cGame* s) : s(s) {}

	void Execute() override;

	const char* Type() override { return typeid(*this).name(); }

protected:
	cGame* s;
};

// stop after execution of this command
class cCommandCounter : public iCommand
{
public:
	cCommandCounter(cGame* s) : s(s) {}

	void Execute() override;

	const char* Type() override { return typeid(*this).name(); }

protected:
	cGame* s;
};




#endif //#ifndef CSTOPCOMMAND_HPP
