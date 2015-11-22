#ifndef FINITE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_H

#include <string>
#include <list>
#include "Lexem.h"
#include <boost/statechart/state_machine.hpp>
#include "Events.h"
#include <boost/statechart/transition.hpp>
#include <boost/statechart/simple_state.hpp>
#include "Machine.h"

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
			boost::statechart::transition<Events::More, More>,
			boost::statechart::transition<Events::Less, Less>,
			boost::statechart::transition<Events::Equal, Equal>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterS, S>
		> reactions;
	};

	struct Ident
		: boost::statechart::simple_state<Ident, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		>reactions;
	};

	struct Constant
		: boost::statechart::simple_state<Constant, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundConstant>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundConstant>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundConstant>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundConstant>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundConstant>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundConstant>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundConstant>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundConstant>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundConstant>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		>reactions;
	};

	struct String_
		: boost::statechart::simple_state<String_, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Quote, Start, Machine::Machine, &Machine::Machine::FoundString_>
		>reactions;
	};

	struct Multiply
		: boost::statechart::simple_state<Multiply, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit, Constant, Machine::Machine, &Machine::Machine::FoundMultiply>,
			boost::statechart::transition<Events::Letter, Ident, Machine::Machine, &Machine::Machine::FoundMultiply>,
			boost::statechart::transition<Events::Quote, String_, Machine::Machine, &Machine::Machine::FoundMultiply>,
			boost::statechart::transition<Events::Multiplication, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundMultiply>,
			boost::statechart::transition<Events::Comma, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundMultiply>,
			boost::statechart::transition<Events::Semicolon, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::More, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Less, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Equal, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct Division
		: boost::statechart::simple_state<Division, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit, Constant, Machine::Machine, &Machine::Machine::FoundDivision>,
			boost::statechart::transition<Events::Letter, Ident, Machine::Machine, &Machine::Machine::FoundDivision>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundDivision>,
			boost::statechart::transition<Events::Semicolon, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::More, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Less, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Equal, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct Dot
		: boost::statechart::simple_state<Dot, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Letter, Ident, Machine::Machine, &Machine::Machine::FoundDot>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Semicolon, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::More, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Less, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Equal, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct Comma
		: boost::statechart::simple_state<Comma, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit, Constant, Machine::Machine, &Machine::Machine::FoundComma>,
			boost::statechart::transition<Events::Letter, Ident, Machine::Machine, &Machine::Machine::FoundComma>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundComma>,
			boost::statechart::transition<Events::Semicolon, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::More, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Less, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Equal, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct Space
		: boost::statechart::simple_state<Space, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit, Constant, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Letter, Ident, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Quote, String_, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterA, A, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::LetterF, F, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::LetterL, L, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::LetterN, N, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::LetterO, O, Machine::Machine, &Machine::Machine::FoundSpace>,
			boost::statechart::transition<Events::LetterW, W, Machine::Machine, &Machine::Machine::FoundSpace>
		> reactions;
	};

	struct Semicolon
		: boost::statechart::simple_state<Semicolon, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Letter, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundSemicolon>,
			boost::statechart::transition<Events::Semicolon, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::More, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Less, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Equal, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct More
		: boost::statechart::simple_state<More, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit, Constant, Machine::Machine, &Machine::Machine::FoundMore>,
			boost::statechart::transition<Events::Letter, Ident, Machine::Machine, &Machine::Machine::FoundMore>,
			boost::statechart::transition<Events::Quote, String_, Machine::Machine, &Machine::Machine::FoundMore>,
			boost::statechart::transition<Events::Multiplication, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundMore>,
			boost::statechart::transition<Events::Semicolon, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::More, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Less, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundMore>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct Less
		: boost::statechart::simple_state<Less, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit, Constant, Machine::Machine, &Machine::Machine::FoundLess>,
			boost::statechart::transition<Events::Letter, Ident, Machine::Machine, &Machine::Machine::FoundLess>,
			boost::statechart::transition<Events::Quote, String_, Machine::Machine, &Machine::Machine::FoundLess>,
			boost::statechart::transition<Events::Multiplication, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundLess>,
			boost::statechart::transition<Events::Semicolon, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundLess>,
			boost::statechart::transition<Events::Less, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundLess>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct Equal
		: boost::statechart::simple_state<Equal, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Digit, Constant, Machine::Machine, &Machine::Machine::FoundEqual>,
			boost::statechart::transition<Events::Letter, Ident, Machine::Machine, &Machine::Machine::FoundEqual>,
			boost::statechart::transition<Events::Quote, String_, Machine::Machine, &Machine::Machine::FoundEqual>,
			boost::statechart::transition<Events::Multiplication, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundEqual>,
			boost::statechart::transition<Events::Semicolon, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::More, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Less, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Equal, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct Other
		: boost::statechart::simple_state<Other, Machine::Machine>
	{
		typedef boost::mpl::list<> reactions;
	};

	struct S
		: boost::statechart::simple_state<S, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::LetterE, SE>,
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct SE
		: boost::statechart::simple_state<SE, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::LetterL, SEL>,
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct SEL
		: boost::statechart::simple_state<SEL, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::LetterE, SELE>,
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct SELE
		: boost::statechart::simple_state<SELE, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::LetterC, SELEC>,
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct SELEC
		: boost::statechart::simple_state<SELEC, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::LetterT, SELECT>,
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct SELECT
		: boost::statechart::simple_state<SELECT, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundSelect>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct F
		: boost::statechart::simple_state<F, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterR, FR>
		> reactions;
	};

	struct FR
		: boost::statechart::simple_state<FR, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterO, FRO>
		> reactions;
	};

	struct FRO
		: boost::statechart::simple_state<FRO, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterM, FROM>
		> reactions;
	};

	struct FROM
		: boost::statechart::simple_state<FROM, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundFrom>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct W
		: boost::statechart::simple_state<W, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterH, WH>
		> reactions;
	};

	struct WH
		: boost::statechart::simple_state<WH, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterE, WHE>
		> reactions;
	};

	struct WHE
		: boost::statechart::simple_state<WHE, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterR, WHER>
		> reactions;
	};

	struct WHER
		: boost::statechart::simple_state<WHER, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterE, WHERE>
		> reactions;
	};

	struct WHERE
		: boost::statechart::simple_state<WHERE, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundWhere>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct L
		: boost::statechart::simple_state<L, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterI, LI>
		> reactions;
	};

	struct LI
		: boost::statechart::simple_state<LI, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterK, LIK>
		> reactions;
	};

	struct LIK
		: boost::statechart::simple_state<LIK, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterE, LIKE>
		> reactions;
	};

	struct LIKE
		: boost::statechart::simple_state<LIKE, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundLike>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct N
		: boost::statechart::simple_state<N, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterO, NO>
		> reactions;
	};

	struct NO
		: boost::statechart::simple_state<NO, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterT, NOT>
		> reactions;
	};

	struct NOT
		: boost::statechart::simple_state<NOT, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundNot>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct A
		: boost::statechart::simple_state<A, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterN, AN>
		> reactions;
	};

	struct AN
		: boost::statechart::simple_state<AN, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterD, AND>
		> reactions;
	};

	struct AND
		: boost::statechart::simple_state<AND, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundAnd>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};

	struct O
		: boost::statechart::simple_state<O, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundIdent>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::LetterR, OR>
		> reactions;
	};

	struct OR
		: boost::statechart::simple_state<OR, Machine::Machine>
	{
		typedef boost::mpl::list<
			boost::statechart::transition<Events::Letter, Ident>,
			boost::statechart::transition<Events::Quote, Other, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Multiplication, Multiply, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Division, Division, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Dot, Dot, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Comma, Comma, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Space, Space, Machine::Machine, &Machine::Machine::FoundOr>,
			boost::statechart::transition<Events::Semicolon, Semicolon, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::More, More, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Less, Less, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Equal, Equal, Machine::Machine, &Machine::Machine::FoundOther>,
			boost::statechart::transition<Events::Other, Other, Machine::Machine, &Machine::Machine::FoundOther>
		> reactions;
	};
}

#endif