///************************* OUTS HOMEWORK ****************************************

#include "cSpaceShip.hpp"
#include "cInterpretCommand.hpp"
#include "cVector.hpp"



extern const char str_SpaceShip[];
extern const char str_moveTo[];
extern const char str_refuel[];

void cSpaceShip::Execute(const cInterpretCommand& cmd)
{
  if (cmd.OperationId() == "moveTo")
  {
    using derived = TOperation< str_SpaceShip, str_moveTo, cVector>;

    const cOperationData *p = cmd.OperationData().get();
    const derived* p1 = (const derived*)(p);
    moveTo(p1->t);
  }
  else if (cmd.OperationId() == "refuel")
  {
      using derived = TOperation< str_SpaceShip, str_refuel, cTanker>;

      const cOperationData* p = cmd.OperationData().get();
      const derived* p1 = (const derived*)(p);
      refuel(p1->t);
  }

}