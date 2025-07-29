///************************* OUTS HOMEWORK ****************************************

#include "cGame.hpp"
#include "cException.hpp"
#include "iCommand.hpp"
#include "cExceptionsHandler.hpp"
#include "cSpaceShip.hpp"
#include "cInterpretCommand.hpp"

#include <thread>

using namespace std::chrono_literals;

cGame::cGame(std::string id) : cObject(id)
{
  thread_run();
}

void cGame::Execute(const cSoftStopCommand& cmd)
{
  iSoftStop = true;
}

void cGame::Execute(const cInterpretCommand& cmd)
{
  cObject* obj = this->gameObjects[cmd.ObjId()];
  obj->Execute(cmd);
}
  

void cGame::Register(cSpaceShip* spaceShip1)
{
  gameObjects[spaceShip1->Id()] = spaceShip1;
}


void cGame::thread_run()
{
  t = std::thread(
    [](cGame& s)
    {
      std::shared_ptr<iCommand> cmd;

      while (!s.iStop)
      {
        if( false == s.iPlay ) 
        {
          std::this_thread::sleep_for(200ms);
          continue;
        }

        try
        {
          if (true == s.deque.pop_front(cmd))
            cmd->Execute();

          if (true == s.deque.empty())
          {
            if (false == s.iSoftStop)
              std::this_thread::sleep_for(200ms);
            else
              s.iStop = true;
          }
        }
        catch (cException e)
        {
          if (nullptr != s.handler )
            s.handler->Handle(*cmd, e);
        }
      }
    },
    std::ref(*this)
  );

}