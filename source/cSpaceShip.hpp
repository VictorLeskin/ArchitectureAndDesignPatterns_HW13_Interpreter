///************************* OUTS HOMEWORK ****************************************
#ifndef CSPACESHIP_HPP
#define CSPACESHIP_HPP

#include "cObject.hpp"
#include "cVector.hpp"

class cTanker
{
public:
	int fuel = 0;
};

class cSpaceShip : public cObject
{
public:
	cSpaceShip(std::string id) : cObject(id), p({0,0}), fuel(0) {}

	void Execute(const cInterpretCommand& cmd) override;

	void moveTo(const cVector& newPos) { p = newPos;  }
	void refuel(const cTanker &t) 
	{ 
		int f = std::min(25, t.fuel);
		fuel += f; 
		const_cast<cTanker&>(t).fuel -= f;
	}

	const cVector& Position() const { return p; }
	int Fuel() const { return fuel; }

protected:
	cVector p;
	int fuel = 0;
};


#endif //#ifndef CSPACESHIP_HPP
