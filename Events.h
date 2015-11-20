#ifndef EVENTS_H
#define EVENTS_H

#include <boost/statechart/event.hpp>

namespace Events
{
	struct Digit			: boost::statechart::event<Digit> {};
	struct Letter			: boost::statechart::event<Letter> {};
	struct Quote			: boost::statechart::event<Quote> {};
	struct Multiplication	: boost::statechart::event<Multiplication> {};
	struct Division			: boost::statechart::event<Division> {};
	struct Dot				: boost::statechart::event<Dot> {};
	struct Comma			: boost::statechart::event<Comma> {};
	struct Space			: boost::statechart::event<Space> {};
	struct Semicolon		: boost::statechart::event<Semicolon> {};
	struct Comparsion		: boost::statechart::event<Comparsion> {};
	struct Other			: boost::statechart::event<Other> {};
}

#endif