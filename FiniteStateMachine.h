#ifndef FINITE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_H

#include <string>
#include <list>
#include "lexem.h"
#include <boost/statechart/state_machine.hpp>
#include "Events.h"
#include <boost/statechart/transition.hpp>
#include <boost/statechart/simple_state.hpp>

namespace States
{
	struct Start;
	struct Ident;
	struct Constant;
	struct String_;
	struct Multiply;
	struct Division;
	struct Dot;
	struct Comma;
	struct Space;
	struct Semicolon;
	struct Comparsion;
	struct Other;
}

namespace Machine{
	class FiniteStateMachine
	{
	public:
		FiniteStateMachine() {};
		~FiniteStateMachine() { lexems.clear(); value.clear(); }

		std::string value;
		std::list<Lexem::Lexem> lexems;

		void Process(std::string& text);

		void FoundIdent()		{ lexems.push_back(Lexem::Lexem(Lexem::LexemType::IDENTIFIER,	this->value));	value = ""; }
		void FoundConstant()	{ lexems.push_back(Lexem::Lexem(Lexem::LexemType::CONSTANT,		this->value));  value = ""; }
		void FoundString_()		{ lexems.push_back(Lexem::Lexem(Lexem::LexemType::STRING,		this->value));  value = ""; }
		void FoundMultiply()	{ lexems.push_back(Lexem::Lexem(Lexem::LexemType::MULTIPLY,		"*"));			value = ""; }
		void FoundDivision()	{ lexems.push_back(Lexem::Lexem(Lexem::LexemType::DIVISION,		"/"));			value = ""; }
		void FoundDot()			{ lexems.push_back(Lexem::Lexem(Lexem::LexemType::DOT,			"."));			value = ""; }
		void FoundComma()		{ lexems.push_back(Lexem::Lexem(Lexem::LexemType::COMMA,		","));			value = ""; }
		void FoundSpace()		{ lexems.push_back(Lexem::Lexem(Lexem::LexemType::SPACE,		" "));			value = ""; }
		void FoundSemicolon()	{ lexems.push_back(Lexem::Lexem(Lexem::LexemType::SEMICOLON,	";"));			value = ""; }
		void FoundComparsion()	{ lexems.push_back(Lexem::Lexem(Lexem::LexemType::COMPARSION,	this->value));	value = ""; }
		void FoundOther()		{ lexems.push_back(Lexem::Lexem(Lexem::LexemType::OTHER,		this->value)); }
	};


	struct Machine : boost::statechart::state_machine<Machine, States::Start>
	{
		Machine(FiniteStateMachine& mainMachine) : MainMachine_(mainMachine) {}

		void FoundIdent(const Events::Space&)				{ MainMachine_.FoundIdent(); }
		void FoundIdent(const Events::Multiplication&)		{ MainMachine_.FoundIdent(); }
		void FoundIdent(const Events::Division&)			{ MainMachine_.FoundIdent(); }
		void FoundIdent(const Events::Dot&)					{ MainMachine_.FoundIdent(); }
		void FoundIdent(const Events::Comma&)				{ MainMachine_.FoundIdent(); }
		void FoundIdent(const Events::Comparsion&)			{ MainMachine_.FoundIdent(); }
		void FoundIdent(const Events::Semicolon&)			{ MainMachine_.FoundIdent(); }

		void FoundConstant(const Events::Space&)			{ MainMachine_.FoundConstant(); }
		void FoundConstant(const Events::Comparsion&)		{ MainMachine_.FoundConstant(); }
		void FoundConstant(const Events::Multiplication&)	{ MainMachine_.FoundConstant(); }
		void FoundConstant(const Events::Division&)			{ MainMachine_.FoundConstant(); }
		void FoundConstant(const Events::Dot&)				{ MainMachine_.FoundConstant(); }
		void FoundConstant(const Events::Comma&)			{ MainMachine_.FoundConstant(); }
		void FoundConstant(const Events::Semicolon&)		{ MainMachine_.FoundConstant(); }

		void FoundString_(const Events::Quote&)				{ MainMachine_.FoundString_(); }

		void FoundMultiply(const Events::Digit&)			{ MainMachine_.FoundMultiply(); }
		void FoundMultiply(const Events::Letter&)			{ MainMachine_.FoundMultiply(); }
		void FoundMultiply(const Events::Quote&)			{ MainMachine_.FoundMultiply(); }
		void FoundMultiply(const Events::Dot&)				{ MainMachine_.FoundMultiply(); }
		void FoundMultiply(const Events::Space&)			{ MainMachine_.FoundMultiply(); }

		void FoundDivision(const Events::Digit&)			{ MainMachine_.FoundDivision(); }
		void FoundDivision(const Events::Letter&)			{ MainMachine_.FoundDivision(); }
		void FoundDivision(const Events::Space&)			{ MainMachine_.FoundDivision(); }

		void FoundDot(const Events::Letter&)				{ MainMachine_.FoundDot(); }

		void FoundComma(const Events::Digit&)				{ MainMachine_.FoundComma(); } 
		void FoundComma(const Events::Letter&)				{ MainMachine_.FoundComma(); }
		void FoundComma(const Events::Space&)				{ MainMachine_.FoundComma(); }

		void FoundSpace(const Events::Digit&)				{ MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Letter&)				{ MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Quote&)				{ MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Multiplication&)		{ MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Division&)			{ MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Dot&)					{ MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Comma&)				{ MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Space&)				{ MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Semicolon&)			{ MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Comparsion&)			{ MainMachine_.FoundSpace(); }

		void FoundSemicolon(const Events::Space&)			{ MainMachine_.FoundSemicolon(); }

		void FoundComparsion(const Events::Digit&)			{ MainMachine_.FoundComparsion(); }
		void FoundComparsion(const Events::Letter&)			{ MainMachine_.FoundComparsion(); }
		void FoundComparsion(const Events::Quote&)			{ MainMachine_.FoundComparsion(); }
		void FoundComparsion(const Events::Space&)			{ MainMachine_.FoundComparsion(); }
		void FoundComparsion(const Events::Comparsion&)		{ MainMachine_.FoundComparsion(); }

		void FoundOther(const Events::Digit&)				{ MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Letter&)				{ MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Quote&)				{ MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Multiplication&)		{ MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Division&)			{ MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Dot&)					{ MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Comma&)				{ MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Space&)				{ MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Semicolon&)			{ MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Comparsion&)			{ MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Other&)				{ MainMachine_.FoundOther(); this->terminate(); }
	private:
		FiniteStateMachine& MainMachine_;
	};
}

namespace States
{
	struct Start
		: boost::statechart::simple_state<Start, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit, Constant>,
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, String_>,
			boost::statechart::transition<Events::Multiplication, Multiply>,
			boost::statechart::transition<Events::Division, Division>,
			boost::statechart::transition<Events::Dot, Dot>,
			boost::statechart::transition<Events::Comma, Comma>,
			boost::statechart::transition<Events::Space, Space>,
			boost::statechart::transition<Events::Semicolon, Semicolon>,
			boost::statechart::transition<Events::Comparsion, Comparsion>,
			boost::statechart::transition<Events::Other, Other>
		> reactions;
	};

	struct Ident
		: boost::statechart::simple_state<Ident, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Quote,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication,	Multiply,	Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division,			Division,	Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot,				Dot,		Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma,			Comma,		Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space,			Space,		Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon,		Semicolon,	Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comparsion,		Comparsion, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other,			Other,		Machine::Machine, &Machine::Machine::FoundOther>
		>
			reactions;
	};

	struct Constant
		: boost::statechart::simple_state<Constant, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter,			Ident>,
			boost::statechart::transition<Events::Quote,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication,	Multiply,	Machine::Machine, &Machine::Machine::FoundConstant>,
			boost::statechart::transition<Events::Division,			Division,	Machine::Machine, &Machine::Machine::FoundConstant>,
			boost::statechart::transition<Events::Dot,				Dot,		Machine::Machine, &Machine::Machine::FoundConstant>,
			boost::statechart::transition<Events::Comma,			Comma,		Machine::Machine, &Machine::Machine::FoundConstant>,
			boost::statechart::transition<Events::Space,			Space,		Machine::Machine, &Machine::Machine::FoundConstant>,
			boost::statechart::transition<Events::Semicolon,		Semicolon,	Machine::Machine, &Machine::Machine::FoundConstant>,
			boost::statechart::transition<Events::Comparsion,		Comparsion, Machine::Machine, &Machine::Machine::FoundConstant>,
			boost::statechart::transition<Events::Other,			Other,		Machine::Machine, &Machine::Machine::FoundOther>
		>
			reactions;
	};

	struct String_
		: boost::statechart::simple_state<String_, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Quote,			Start,		Machine::Machine, &Machine::Machine::FoundString_>
		>
			reactions;
	};

	struct Multiply
		: boost::statechart::simple_state<Multiply, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit,			Constant,	Machine::Machine, &Machine::Machine::FoundMultiply>,
			boost::statechart::transition<Events::Letter,			Ident,		Machine::Machine, &Machine::Machine::FoundMultiply>,
			boost::statechart::transition<Events::Quote,			String_,	Machine::Machine, &Machine::Machine::FoundMultiply>,
			boost::statechart::transition<Events::Multiplication,	Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot,				Dot,		Machine::Machine, &Machine::Machine::FoundMultiply>,
			boost::statechart::transition<Events::Comma,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space,			Space,		Machine::Machine, &Machine::Machine::FoundMultiply>,
			boost::statechart::transition<Events::Semicolon,		Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comparsion,		Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other,			Other,		Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct Division
		: boost::statechart::simple_state<Division, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit,			Constant,	Machine::Machine, &Machine::Machine::FoundDivision>,
			boost::statechart::transition<Events::Letter,			Ident,		Machine::Machine, &Machine::Machine::FoundDivision>,
			boost::statechart::transition<Events::Quote,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication,	Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot,				Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space,			Space,		Machine::Machine, &Machine::Machine::FoundDivision>,
			boost::statechart::transition<Events::Semicolon,		Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comparsion,		Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other,			Other,		Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct Dot
		: boost::statechart::simple_state<Dot, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Letter,			Ident,		Machine::Machine, &Machine::Machine::FoundDot>,
			boost::statechart::transition<Events::Quote,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication,	Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot,				Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Semicolon,		Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comparsion,		Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other,			Other,		Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct Comma
		: boost::statechart::simple_state<Comma, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit,			Constant,	Machine::Machine, &Machine::Machine::FoundComma>,
			boost::statechart::transition<Events::Letter,			Ident,		Machine::Machine, &Machine::Machine::FoundComma>,
			boost::statechart::transition<Events::Quote,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication,	Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot,				Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space,			Space,		Machine::Machine, &Machine::Machine::FoundComma>,
			boost::statechart::transition<Events::Semicolon,		Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comparsion,		Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other,			Other,		Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct Space
		: boost::statechart::simple_state<Space, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit,			Constant,	Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Letter,			Ident,		Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Quote,			String_,	Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Multiplication,	Multiply,	Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Division,			Division,	Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Dot,				Dot,		Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Comma,			Comma,		Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Space,			Space,		Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Semicolon,		Semicolon,	Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Comparsion,		Comparsion, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Other,			Other,		Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct Semicolon
		: boost::statechart::simple_state<Semicolon, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Letter,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Quote,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication,	Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot,				Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space,			Space,		Machine::Machine, &Machine::Machine::FoundSemicolon>,
			boost::statechart::transition<Events::Semicolon,		Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comparsion,		Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other,			Other,		Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct Comparsion
		: boost::statechart::simple_state<Comparsion, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit,			Constant,	Machine::Machine, &Machine::Machine::FoundComparsion>,
			boost::statechart::transition<Events::Letter,			Ident,		Machine::Machine, &Machine::Machine::FoundComparsion>,
			boost::statechart::transition<Events::Quote,			String_,	Machine::Machine, &Machine::Machine::FoundComparsion>,
			boost::statechart::transition<Events::Multiplication,	Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot,				Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma,			Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space,			Space,		Machine::Machine, &Machine::Machine::FoundComparsion>,
			boost::statechart::transition<Events::Semicolon,		Other,		Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comparsion,		Comparsion, Machine::Machine, &Machine::Machine::FoundComparsion>,
			boost::statechart::transition<Events::Other,			Other,		Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct Other
		: boost::statechart::simple_state<Other, Machine::Machine>
	{
		typedef boost::mpl::list<> reactions;
	};
}

#endif
