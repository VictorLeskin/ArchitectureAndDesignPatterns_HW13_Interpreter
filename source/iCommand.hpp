///************************* OUTS HOMEWORK ****************************************
#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

// interface class of command
class iCommand
{
public:
	virtual ~iCommand() = default;

	virtual void Execute() = 0;
	virtual const char* Type() = 0;
};


#endif //#ifndef ICOMMAND_HPP
