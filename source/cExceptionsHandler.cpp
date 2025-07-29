///************************* OUTS HOMEWORK ****************************************

#include "cExceptionsHandler.hpp"
#include "iCommand.hpp"
#include "cException.hpp"

cExceptionsHandler::exceptionProcessor cExceptionsHandler::Handle(iCommand& command, cException& e)
{
  auto action = get(command.Type(), e.what());
  if (action.has_value())
    return *action;

  throw(cException("There is not action for this command and type"));
}


void cExceptionsHandler::Register(const char* commandType, const char* exceptionType, exceptionProcessor procesor)
{
  exceptionActions.insert(std::make_pair(std::tuple(commandType, exceptionType), procesor));
}

std::optional<cExceptionsHandler::exceptionProcessor> cExceptionsHandler::get(const char* commandType, const char* exceptionType) const
{
  if (auto f = exceptionActions.find(std::tuple(commandType, exceptionType));
    exceptionActions.end() != f)
    return std::optional<exceptionProcessor>(f->second);
  else
    return std::optional<exceptionProcessor>();
}
