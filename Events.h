#ifndef EVENTS_H
#define EVENTS_H

#include <boost/statechart/event.hpp>

namespace Events
{
	struct Digit : boost::statechart::event<Digit> {};
	struct Letter : boost::statechart::event<Letter> {};

	struct LetterA : boost::statechart::event<LetterA> {};
	struct LetterC : boost::statechart::event<LetterC> {};
	struct LetterD : boost::statechart::event<LetterD> {};
	struct LetterE : boost::statechart::event<LetterE> {};
	struct LetterF : boost::statechart::event<LetterF> {};
	struct LetterH : boost::statechart::event<LetterH> {};
	struct LetterI : boost::statechart::event<LetterI> {};
	struct LetterK : boost::statechart::event<LetterK> {};
	struct LetterL : boost::statechart::event<LetterL> {};
	struct LetterM : boost::statechart::event<LetterM> {};
	struct LetterN : boost::statechart::event<LetterN> {};
	struct LetterO : boost::statechart::event<LetterO> {};
	struct LetterR : boost::statechart::event<LetterR> {};
	struct LetterS : boost::statechart::event<LetterS> {};
	struct LetterT : boost::statechart::event<LetterT> {};
	struct LetterW : boost::statechart::event<LetterW> {};

	struct Quote : boost::statechart::event<Quote> {};
	struct Multiplication : boost::statechart::event<Multiplication> {};
	struct Division : boost::statechart::event<Division> {};
	struct Dot : boost::statechart::event<Dot> {};
	struct Comma : boost::statechart::event<Comma> {};
	struct Space : boost::statechart::event<Space> {};
	struct Semicolon : boost::statechart::event<Semicolon> {};
	struct More : boost::statechart::event<More> {};
	struct Less : boost::statechart::event<Less> {};
	struct Equal : boost::statechart::event<Equal> {};
	struct Other : boost::statechart::event<Other> {};
}

#endif