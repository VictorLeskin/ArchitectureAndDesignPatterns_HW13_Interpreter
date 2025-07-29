///************************* OUTS HOMEWORK ****************************************

#include "cStopCommand.hpp"
#include "cException.hpp"
#include "cGame.hpp"

void cSoftStopCommand::Execute()
{
	s->Execute(*this);
}

void cHardStopCommand::Execute()
{
	s->Execute(*this);
}

void cCommandCounter::Execute()
{
	s->Execute( *this );
}
