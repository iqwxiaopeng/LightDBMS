//structure of the machine http://www.devexp.ru/2011/02/konechnye-avtomaty-v-c/
#ifndef FINITE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_H
#include "Lexem.h"
#include <list>
#include <vector>

class FiniteStateMachine
{
	enum States
	{
		Start, Ident, Constant, String_, Multiply, Division, Dot, Comma, Space, Semicolon, More, Less, Equal, Other,
		A, AN, AND, N, NO, NOT, O, OR, 
		F, FR, FRO, FROM, L, LI, LIK, LIKE, 
		S, SE, SEL, SELE, SELEC, SELECT, 
		W, WH, WHE, WHER, WHERE,
		Leftbracket, Rightbracket
	};

	static const size_t STATES_COUNT = 43;

	enum Events
	{
		Digit_Ev, Letter_Ev,
		LetterA_Ev, LetterC_Ev, LetterD_Ev, LetterE_Ev, LetterF_Ev, LetterH_Ev, LetterI_Ev, LetterK_Ev,
		LetterL_Ev, LetterM_Ev, LetterN_Ev, LetterO_Ev, LetterR_Ev, LetterS_Ev, LetterT_Ev, LetterW_Ev,
		Quote_Ev, Multiplication_Ev, Division_Ev, Dot_Ev, Comma_Ev,
		Space_Ev, Semicolon_Ev, More_Ev, Less_Ev, Equal_Ev, Other_Ev,
		LeftBracket_Ev, RightBracket_Ev
	};

	static const size_t EVENTS_COUNT = 31;

public:
	FiniteStateMachine();
	~FiniteStateMachine() { lexems.clear(); value.clear(); }

	std::string value;
	std::list<Lexem::Lexem> lexems;

	void Process(std::string& text);

private:
	void ProcessEvent(Events event);

	void DoNothing() {}

	typedef void (FiniteStateMachine::*Action)();

	struct Transition
	{
		Transition() {};
		Transition(States targetState, Action action) : TargetState_(targetState), Action_(action) {};

		States TargetState_;
		Action Action_;
	};

	void AddTransition(States fromState, Events event, States toState);
	void AddTransition(States fromState, Events event, States toState, Action action);

	typedef std::vector<Transition> TransitionByEventsTable;
	typedef std::vector<TransitionByEventsTable> StatesTable;

	StatesTable States_;
	States CurrentState_;

	void FoundIdent() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::IDENTIFIER, this->value)); value = ""; }
	void FoundConstant() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::CONSTANT, this->value)); value = ""; }
	void FoundString_() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::STRING, this->value)); value = ""; }
	void FoundMultiply() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::MULTIPLY, "*")); value = ""; }
	void FoundDivision() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::DIVISION, "/")); value = ""; }
	void FoundDot() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::DOT, ".")); value = ""; }
	void FoundComma() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::COMMA, ",")); value = ""; }
	void FoundSpace() { value = ""; }
	void FoundSemicolon() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::SEMICOLON, ";")); value = ""; }
	void FoundMore() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::MORE, ">")); value = ""; }
	void FoundLess() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::LESS, "<")); value = ""; }
	void FoundEqual() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::EQUAL, "=")); value = ""; }
	void FoundOther() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::OTHER, this->value)); }
	void FoundSelect() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::SELECT, "")); value = ""; }
	void FoundFrom() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::FROM, "")); value = ""; }
	void FoundWhere() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::WHERE, "")); value = ""; }
	void FoundAnd() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::AND, "")); value = ""; }
	void FoundOr() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::OR, "")); value = ""; }
	void FoundNot() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::NOT, "")); value = ""; }
	void FoundLike() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::LIKE, "")); value = ""; }
	void FoundLeftBracket() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::LEFTBRACKET, "(")); value = ""; }
	void FoundRightBracket() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::RIGHTBRACKET, ")")); value = ""; }
};
#endif