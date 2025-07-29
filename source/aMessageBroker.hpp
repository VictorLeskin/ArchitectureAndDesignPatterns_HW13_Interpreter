///************************* OUTS HOMEWORK ****************************************
#ifndef AMESSAGEBROKER_HPP
#define AMESSAGEBROKER_HPP


class cMessage;

class aMessageBroker
{
public:
	virtual bool get(cMessage& m) = 0;
	virtual void put(cMessage& m) = 0;
};

#endif //#ifndef AMESSAGEBROKER_HPP
