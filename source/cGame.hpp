///************************* OUTS HOMEWORK ****************************************
#ifndef CGAME_HPP
#define CGAME_HPP

#include "cObject.hpp"
#include "cGameId.hpp"
#include "cThreadSafeDeque.hpp"
#include "cException.hpp"

#include <memory>
#include <map>

class cSpaceShip;
class iCommand;
class cExceptionsHandler;

class cSoftStopCommand;
class cHardStopCommand;
class cCommandCounter;
class cInterpretCommand;


class cGame : public cObject
{
public:
	cGame(std::string id);

	void Execute(const cSoftStopCommand& cmd);
	void Execute(const cHardStopCommand& cmd) { throw cException("not implemented"); }
	void Execute(const cCommandCounter& cmd) { throw cException("not implemented"); }
	void Execute(const cInterpretCommand& cmd);

	void Register(cSpaceShip* spaceShip1);

	void push_back(const std::shared_ptr<iCommand>& p)
	{
		deque.push_back(p);
	}
	
    void join()	{ t.join(); }
	void detach() {	t.detach(); }
	void play() { iPlay = true; }

	const cObject* operator[](const std::string& s) const
	{
		return gameObjects.at(s);
	}

	const TThreadSafeDeque< std::shared_ptr<iCommand> >& Deque() const { return deque; }

protected:

	void thread_run();
	                  
	TThreadSafeDeque< std::shared_ptr<iCommand> > deque;
	std::map<std::string, cObject *> gameObjects;

	std::thread t;
	std::atomic_int iPlay = false, iStop = false, iSoftStop = false;
	cExceptionsHandler* handler = nullptr;

};

#endif //#ifndef CGAME_HPP
