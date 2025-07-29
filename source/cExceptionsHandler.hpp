///************************* OUTS HOMEWORK ****************************************
#ifndef CEXCEPTIONSHANDLER_HPP
#define CEXCEPTIONSHANDLER_HPP

#include <tuple>
#include <string>
#include <optional>
#include <map>

class iCommand;
class cException;

class cExceptionsHandler
{
public:
	using exceptionProcessor = void (*)(cExceptionsHandler&, iCommand&, cException&);
	using key = std::tuple<std::string, std::string>; // command, exception

public:
	cExceptionsHandler() {}

	cExceptionsHandler::exceptionProcessor Handle( iCommand& command, cException& e);

	void Register(const char* commandType, const char* exceptionType, exceptionProcessor procesor);
	std::optional< exceptionProcessor > get(const char* commandType, const char* exceptionType) const;

	static void	exampleProcessException(cExceptionsHandler& handler, iCommand& command, cException& e)
	{
	}
	static void	skipException(cExceptionsHandler& handler, iCommand& command, cException& e)
	{
	}

protected:
	std::map<key, exceptionProcessor> exceptionActions;
};

#endif //#ifndef CEXCEPTIONSHANDLER_HPP
