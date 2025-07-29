///************************* OUTS HOMEWORK ****************************************
#ifndef CMESSAGESDEQUE_HPP
#define CMESSAGESDEQUE_HPP

#include "cThreadSafeDeque.hpp"
#include "cMessage.hpp"
#include <memory>

class cMessagesDeque : public TThreadSafeDeque< std::shared_ptr<cMessage> >
{
public:
	void push_back(const cMessage& item)
	{
		std::shared_ptr<cMessage> t(new cMessage(item));
		TThreadSafeDeque< std::shared_ptr<cMessage> >::push_back(t);
	}

	bool pop_front(cMessage& item)
	{
		std::shared_ptr<cMessage> t;
		if (true == TThreadSafeDeque< std::shared_ptr<cMessage> >::pop_front(t))
		{
			item = *t;
			return true;
		}

		return false;
	}

	using TThreadSafeDeque< std::shared_ptr<cMessage> >::empty;
	using TThreadSafeDeque< std::shared_ptr<cMessage> >::size;
};

#endif //#ifndef CMESSAGESDEQUE_HPP
