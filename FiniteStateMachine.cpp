#include "FiniteStateMachine.h"
#include <cctype>

FiniteStateMachine::FiniteStateMachine()
	: CurrentState_(Start)
{
	States_.resize(STATES_COUNT);
	for (size_t i = 0; i != STATES_COUNT; ++i)
	{
		States_[i].resize(EVENTS_COUNT);
		TransitionByEventsTable& transitionByEvents = States_[i];
		for (size_t j = 0; j != EVENTS_COUNT; ++j)
		{
			transitionByEvents[j] = Transition(static_cast<States>(i), &FiniteStateMachine::DoNothing);
		}
	}

	AddTransition(Start, Digit_Ev, Constant);
	AddTransition(Start, Letter_Ev, Ident);
	AddTransition(Start, Quote_Ev, String_);
	AddTransition(Start, Multiplication_Ev, Multiply);
	AddTransition(Start, Division_Ev, Division);
	AddTransition(Start, Dot_Ev, Dot);
	AddTransition(Start, Comma_Ev, Comma);
	AddTransition(Start, Space_Ev, Space);
	AddTransition(Start, Semicolon_Ev, Semicolon);
	AddTransition(Start, More_Ev, More);
	AddTransition(Start, Less_Ev, Less);
	AddTransition(Start, Equal_Ev, Equal);
	AddTransition(Start, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Start, LetterS_Ev, S);
	AddTransition(Start, LeftBracket_Ev, Leftbracket);
	AddTransition(Start, RightBracket_Ev, Rightbracket);

	AddTransition(Ident, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Ident, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(Ident, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(Ident, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(Ident, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(Ident, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(Ident, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(Ident, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(Ident, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(Ident, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(Ident, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Ident, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Ident, RightBracket_Ev, Rightbracket, &FiniteStateMachine::FoundIdent);

	AddTransition(Constant, Letter_Ev, Ident);
	AddTransition(Constant, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Constant, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundConstant);
	AddTransition(Constant, Division_Ev, Division, &FiniteStateMachine::FoundConstant);
	AddTransition(Constant, Dot_Ev, Dot, &FiniteStateMachine::FoundConstant);
	AddTransition(Constant, Comma_Ev, Comma, &FiniteStateMachine::FoundConstant);
	AddTransition(Constant, Space_Ev, Space, &FiniteStateMachine::FoundConstant);
	AddTransition(Constant, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundConstant);
	AddTransition(Constant, More_Ev, More, &FiniteStateMachine::FoundConstant);
	AddTransition(Constant, Less_Ev, Less, &FiniteStateMachine::FoundConstant);
	AddTransition(Constant, Equal_Ev, Equal, &FiniteStateMachine::FoundConstant);
	AddTransition(Constant, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Constant, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Constant, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(Leftbracket, Digit_Ev, Constant, &FiniteStateMachine::FoundLeftBracket);
	AddTransition(Leftbracket, Letter_Ev, Ident, &FiniteStateMachine::FoundLeftBracket);
	AddTransition(Leftbracket, Quote_Ev, String_, &FiniteStateMachine::FoundLeftBracket);
	AddTransition(Leftbracket, Multiplication_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Leftbracket, Division_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Leftbracket, Dot_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Leftbracket, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Leftbracket, Space_Ev, Space, &FiniteStateMachine::FoundLeftBracket);
	AddTransition(Leftbracket, Semicolon_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Leftbracket, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Leftbracket, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Leftbracket, Equal_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Leftbracket, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Leftbracket, LetterS_Ev, S, &FiniteStateMachine::FoundLeftBracket);
	AddTransition(Leftbracket, LeftBracket_Ev, Leftbracket, &FiniteStateMachine::FoundLeftBracket);
	AddTransition(Leftbracket, RightBracket_Ev, Rightbracket, &FiniteStateMachine::FoundLeftBracket);

	AddTransition(Rightbracket, Digit_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Rightbracket, Letter_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Rightbracket, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Rightbracket, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundRightBracket);
	AddTransition(Rightbracket, Division_Ev, Division, &FiniteStateMachine::FoundRightBracket);
	AddTransition(Rightbracket, Dot_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Rightbracket, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Rightbracket, Space_Ev, Space, &FiniteStateMachine::FoundRightBracket);
	AddTransition(Rightbracket, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundRightBracket);
	AddTransition(Rightbracket, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Rightbracket, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Rightbracket, Equal_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Rightbracket, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Rightbracket, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Rightbracket, RightBracket_Ev, Rightbracket, &FiniteStateMachine::FoundRightBracket);

	AddTransition(String_, Quote_Ev, Start, &FiniteStateMachine::FoundString_);

	AddTransition(Multiply, Digit_Ev, Constant, &FiniteStateMachine::FoundMultiply);
	AddTransition(Multiply, Letter_Ev, Ident, &FiniteStateMachine::FoundMultiply);
	AddTransition(Multiply, Quote_Ev, String_, &FiniteStateMachine::FoundMultiply);
	AddTransition(Multiply, Multiplication_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Multiply, Division_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Multiply, Dot_Ev, Dot, &FiniteStateMachine::FoundMultiply);
	AddTransition(Multiply, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Multiply, Space_Ev, Space, &FiniteStateMachine::FoundMultiply);
	AddTransition(Multiply, Semicolon_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Multiply, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Multiply, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Multiply, Equal_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Multiply, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Multiply, LeftBracket_Ev, Leftbracket, &FiniteStateMachine::FoundMultiply);
	AddTransition(Multiply, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(Division, Digit_Ev, Constant, &FiniteStateMachine::FoundDivision);
	AddTransition(Division, Letter_Ev, Ident, &FiniteStateMachine::FoundDivision);
	AddTransition(Division, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Division, Multiplication_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Division, Division_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Division, Dot_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Division, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Division, Space_Ev, Space, &FiniteStateMachine::FoundDivision);
	AddTransition(Division, Semicolon_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Division, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Division, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Division, Equal_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Division, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Division, LeftBracket_Ev, Leftbracket, &FiniteStateMachine::FoundDivision);
	AddTransition(Division, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(Dot, Digit_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Dot, Letter_Ev, Ident, &FiniteStateMachine::FoundDot);
	AddTransition(Dot, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Dot, Multiplication_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Dot, Division_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Dot, Dot_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Dot, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Dot, Space_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Dot, Semicolon_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Dot, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Dot, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Dot, Equal_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Dot, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Dot, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Dot, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(Comma, Digit_Ev, Constant, &FiniteStateMachine::FoundComma);
	AddTransition(Comma, Letter_Ev, Ident, &FiniteStateMachine::FoundComma);
	AddTransition(Comma, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Comma, Multiplication_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Comma, Division_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Comma, Dot_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Comma, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Comma, Space_Ev, Space, &FiniteStateMachine::FoundComma);
	AddTransition(Comma, Semicolon_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Comma, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Comma, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Comma, Equal_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Comma, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Comma, LeftBracket_Ev, Leftbracket, &FiniteStateMachine::FoundComma);
	AddTransition(Comma, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(Semicolon, Digit_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Semicolon, Letter_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Semicolon, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Semicolon, Multiplication_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Semicolon, Division_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Semicolon, Dot_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Semicolon, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Semicolon, Space_Ev, Space, &FiniteStateMachine::FoundSemicolon);
	AddTransition(Semicolon, Semicolon_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Semicolon, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Semicolon, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Semicolon, Equal_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Semicolon, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Semicolon, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Semicolon, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(More, Digit_Ev, Constant, &FiniteStateMachine::FoundMore);
	AddTransition(More, Letter_Ev, Ident, &FiniteStateMachine::FoundMore);
	AddTransition(More, Quote_Ev, String_, &FiniteStateMachine::FoundMore);
	AddTransition(More, Multiplication_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(More, Division_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(More, Dot_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(More, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(More, Space_Ev, Space, &FiniteStateMachine::FoundMore);
	AddTransition(More, Semicolon_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(More, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(More, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(More, Equal_Ev, Equal, &FiniteStateMachine::FoundMore);
	AddTransition(More, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(More, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(More, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(Less, Digit_Ev, Constant, &FiniteStateMachine::FoundLess);
	AddTransition(Less, Letter_Ev, Ident, &FiniteStateMachine::FoundLess);
	AddTransition(Less, Quote_Ev, String_, &FiniteStateMachine::FoundLess);
	AddTransition(Less, Multiplication_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Less, Division_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Less, Dot_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Less, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Less, Space_Ev, Space, &FiniteStateMachine::FoundLess);
	AddTransition(Less, Semicolon_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Less, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Less, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Less, Equal_Ev, Equal, &FiniteStateMachine::FoundLess);
	AddTransition(Less, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Less, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Less, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(Equal, Digit_Ev, Constant, &FiniteStateMachine::FoundEqual);
	AddTransition(Equal, Letter_Ev, Ident, &FiniteStateMachine::FoundEqual);
	AddTransition(Equal, Quote_Ev, String_, &FiniteStateMachine::FoundEqual);
	AddTransition(Equal, Multiplication_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Equal, Division_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Equal, Dot_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Equal, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Equal, Space_Ev, Space, &FiniteStateMachine::FoundEqual);
	AddTransition(Equal, Semicolon_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Equal, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Equal, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Equal, Equal_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Equal, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Equal, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Equal, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(Space, Digit_Ev, Constant, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, Letter_Ev, Ident, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, Quote_Ev, String_, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, Division_Ev, Division, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, Dot_Ev, Dot, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, Comma_Ev, Comma, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, Space_Ev, Space, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, More_Ev, More, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, Less_Ev, Less, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, Equal_Ev, Equal, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(Space, LetterA_Ev, A, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, LetterF_Ev, F, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, LetterL_Ev, L, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, LetterN_Ev, N, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, LetterO_Ev, O, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, LetterS_Ev, S, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, LetterW_Ev, W, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, LeftBracket_Ev, Leftbracket, &FiniteStateMachine::FoundSpace);
	AddTransition(Space, RightBracket_Ev, Rightbracket, &FiniteStateMachine::FoundSpace);

	AddTransition(S, Digit_Ev, Ident);
	AddTransition(S, Letter_Ev, Ident);
	AddTransition(S, LetterE_Ev, SE);
	AddTransition(S, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(S, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(S, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(S, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(S, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(S, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(S, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(S, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(S, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(S, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(S, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(S, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(S, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(SE, Digit_Ev, Ident);
	AddTransition(SE, Letter_Ev, Ident);
	AddTransition(SE, LetterL_Ev, SEL);
	AddTransition(SE, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SE, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(SE, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(SE, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(SE, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(SE, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(SE, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(SE, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(SE, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(SE, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(SE, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SE, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SE, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(SEL, Digit_Ev, Ident);
	AddTransition(SEL, Letter_Ev, Ident);
	AddTransition(SEL, LetterE_Ev, SELE);
	AddTransition(SEL, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SEL, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(SEL, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(SEL, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(SEL, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(SEL, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(SEL, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(SEL, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(SEL, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(SEL, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(SEL, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SEL, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SEL, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(SELE, Digit_Ev, Ident);
	AddTransition(SELE, Letter_Ev, Ident);
	AddTransition(SELE, LetterC_Ev, SELEC);
	AddTransition(SELE, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELE, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(SELE, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(SELE, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(SELE, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(SELE, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(SELE, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(SELE, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(SELE, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(SELE, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(SELE, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELE, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELE, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(SELEC, Digit_Ev, Ident);
	AddTransition(SELEC, Letter_Ev, Ident);
	AddTransition(SELEC, LetterT_Ev, SELECT);
	AddTransition(SELEC, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELEC, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(SELEC, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(SELEC, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(SELEC, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(SELEC, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(SELEC, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(SELEC, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(SELEC, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(SELEC, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(SELEC, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELEC, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELEC, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(SELECT, Digit_Ev, Ident);
	AddTransition(SELECT, Letter_Ev, Ident);
	AddTransition(SELECT, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELECT, Multiplication_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELECT, Division_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELECT, Dot_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELECT, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELECT, Space_Ev, Space, &FiniteStateMachine::FoundSelect);
	AddTransition(SELECT, Semicolon_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELECT, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELECT, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELECT, Equal_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELECT, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELECT, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(SELECT, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(F, Digit_Ev, Ident);
	AddTransition(F, Letter_Ev, Ident);
	AddTransition(F, LetterR_Ev, FR);
	AddTransition(F, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(F, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(F, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(F, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(F, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(F, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(F, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(F, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(F, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(F, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(F, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(F, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(F, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(FR, Digit_Ev, Ident);
	AddTransition(FR, Letter_Ev, Ident);
	AddTransition(FR, LetterO_Ev, FRO);
	AddTransition(FR, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FR, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(FR, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(FR, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(FR, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(FR, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(FR, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(FR, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(FR, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(FR, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(FR, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FR, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FR, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(FRO, Digit_Ev, Ident);
	AddTransition(FRO, Letter_Ev, Ident);
	AddTransition(FRO, LetterM_Ev, FROM);
	AddTransition(FRO, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FRO, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(FRO, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(FRO, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(FRO, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(FRO, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(FRO, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(FRO, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(FRO, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(FRO, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(FRO, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FRO, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FRO, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(FROM, Digit_Ev, Ident);
	AddTransition(FROM, Letter_Ev, Ident);
	AddTransition(FROM, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FROM, Multiplication_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FROM, Division_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FROM, Dot_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FROM, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FROM, Space_Ev, Space, &FiniteStateMachine::FoundFrom);
	AddTransition(FROM, Semicolon_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FROM, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FROM, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FROM, Equal_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FROM, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FROM, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(FROM, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(W, Digit_Ev, Ident);
	AddTransition(W, Letter_Ev, Ident);
	AddTransition(W, LetterH_Ev, WH);
	AddTransition(W, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(W, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(W, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(W, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(W, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(W, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(W, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(W, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(W, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(W, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(W, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(W, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(W, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(WH, Digit_Ev, Ident);
	AddTransition(WH, Letter_Ev, Ident);
	AddTransition(WH, LetterE_Ev, WHE);
	AddTransition(WH, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WH, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(WH, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(WH, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(WH, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(WH, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(WH, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(WH, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(WH, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(WH, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(WH, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WH, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WH, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(WHE, Digit_Ev, Ident);
	AddTransition(WHE, Letter_Ev, Ident);
	AddTransition(WHE, LetterR_Ev, WHER);
	AddTransition(WHE, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHE, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(WHE, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(WHE, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(WHE, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(WHE, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(WHE, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(WHE, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(WHE, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(WHE, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(WHE, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHE, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHE, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(WHER, Digit_Ev, Ident);
	AddTransition(WHER, Letter_Ev, Ident);
	AddTransition(WHER, LetterE_Ev, WHERE);
	AddTransition(WHER, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHER, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(WHER, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(WHER, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(WHER, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(WHER, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(WHER, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(WHER, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(WHER, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(WHER, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(WHER, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHER, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHER, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(WHERE, Digit_Ev, Ident);
	AddTransition(WHERE, Letter_Ev, Ident);
	AddTransition(WHERE, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHERE, Multiplication_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHERE, Division_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHERE, Dot_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHERE, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHERE, Space_Ev, Space, &FiniteStateMachine::FoundWhere);
	AddTransition(WHERE, Semicolon_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHERE, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHERE, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHERE, Equal_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHERE, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHERE, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(WHERE, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(L, Digit_Ev, Ident);
	AddTransition(L, Letter_Ev, Ident);
	AddTransition(L, LetterI_Ev, LI);
	AddTransition(L, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(L, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(L, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(L, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(L, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(L, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(L, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(L, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(L, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(L, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(L, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(L, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(L, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(LI, Digit_Ev, Ident);
	AddTransition(LI, Letter_Ev, Ident);
	AddTransition(LI, LetterK_Ev, LIK);
	AddTransition(LI, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LI, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(LI, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(LI, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(LI, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(LI, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(LI, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(LI, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(LI, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(LI, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(LI, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LI, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LI, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(LIK, Digit_Ev, Ident);
	AddTransition(LIK, Letter_Ev, Ident);
	AddTransition(LIK, LetterE_Ev, LIKE);
	AddTransition(LIK, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LIK, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(LIK, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(LIK, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(LIK, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(LIK, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(LIK, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(LIK, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(LIK, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(LIK, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(LIK, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LIK, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LIK, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(LIKE, Digit_Ev, Ident);
	AddTransition(LIKE, Letter_Ev, Ident);
	AddTransition(LIKE, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LIKE, Multiplication_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LIKE, Division_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LIKE, Dot_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LIKE, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LIKE, Space_Ev, Space, &FiniteStateMachine::FoundLike);
	AddTransition(LIKE, Semicolon_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LIKE, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LIKE, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LIKE, Equal_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LIKE, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LIKE, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(LIKE, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(N, Digit_Ev, Ident);
	AddTransition(N, Letter_Ev, Ident);
	AddTransition(N, LetterO_Ev, NO);
	AddTransition(N, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(N, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(N, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(N, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(N, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(N, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(N, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(N, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(N, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(N, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(N, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(N, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(N, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(NO, Digit_Ev, Ident);
	AddTransition(NO, Letter_Ev, Ident);
	AddTransition(NO, LetterT_Ev, NOT);
	AddTransition(NO, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(NO, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(NO, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(NO, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(NO, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(NO, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(NO, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(NO, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(NO, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(NO, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(NO, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(NO, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(NO, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(NOT, Digit_Ev, Ident);
	AddTransition(NOT, Letter_Ev, Ident);
	AddTransition(NOT, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(NOT, Multiplication_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(NOT, Division_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(NOT, Dot_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(NOT, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(NOT, Space_Ev, Space, &FiniteStateMachine::FoundNot);
	AddTransition(NOT, Semicolon_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(NOT, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(NOT, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(NOT, Equal_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(NOT, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(NOT, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(NOT, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(A, Digit_Ev, Ident);
	AddTransition(A, Letter_Ev, Ident);
	AddTransition(A, LetterN_Ev, AN);
	AddTransition(A, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(A, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(A, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(A, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(A, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(A, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(A, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(A, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(A, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(A, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(A, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(A, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(A, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(AN, Digit_Ev, Ident);
	AddTransition(AN, Letter_Ev, Ident);
	AddTransition(AN, LetterD_Ev, AND);
	AddTransition(AN, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(AN, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(AN, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(AN, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(AN, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(AN, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(AN, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(AN, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(AN, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(AN, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(AN, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(AN, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(AN, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(AND, Digit_Ev, Ident);
	AddTransition(AND, Letter_Ev, Ident);
	AddTransition(AND, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(AND, Multiplication_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(AND, Division_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(AND, Dot_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(AND, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(AND, Space_Ev, Space, &FiniteStateMachine::FoundAnd);
	AddTransition(AND, Semicolon_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(AND, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(AND, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(AND, Equal_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(AND, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(AND, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(AND, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(O, Digit_Ev, Ident);
	AddTransition(O, Letter_Ev, Ident);
	AddTransition(O, LetterR_Ev, OR);
	AddTransition(O, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(O, Multiplication_Ev, Multiply, &FiniteStateMachine::FoundIdent);
	AddTransition(O, Division_Ev, Division, &FiniteStateMachine::FoundIdent);
	AddTransition(O, Dot_Ev, Dot, &FiniteStateMachine::FoundIdent);
	AddTransition(O, Comma_Ev, Comma, &FiniteStateMachine::FoundIdent);
	AddTransition(O, Space_Ev, Space, &FiniteStateMachine::FoundIdent);
	AddTransition(O, Semicolon_Ev, Semicolon, &FiniteStateMachine::FoundIdent);
	AddTransition(O, More_Ev, More, &FiniteStateMachine::FoundIdent);
	AddTransition(O, Less_Ev, Less, &FiniteStateMachine::FoundIdent);
	AddTransition(O, Equal_Ev, Equal, &FiniteStateMachine::FoundIdent);
	AddTransition(O, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(O, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(O, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);

	AddTransition(OR, Digit_Ev, Ident);
	AddTransition(OR, Letter_Ev, Ident);
	AddTransition(OR, Quote_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(OR, Multiplication_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(OR, Division_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(OR, Dot_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(OR, Comma_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(OR, Space_Ev, Space, &FiniteStateMachine::FoundOr);
	AddTransition(OR, Semicolon_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(OR, More_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(OR, Less_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(OR, Equal_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(OR, Other_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(OR, LeftBracket_Ev, Other, &FiniteStateMachine::FoundOther);
	AddTransition(OR, RightBracket_Ev, Other, &FiniteStateMachine::FoundOther);
}


void FiniteStateMachine::ProcessEvent(Events event)
{
	const TransitionByEventsTable& transitionByEvents = States_[CurrentState_];
	const Transition& transition = transitionByEvents[event];

	CurrentState_ = transition.TargetState_;
	(this->*(transition.Action_))();
}

void FiniteStateMachine::AddTransition(States fromState, Events event, States toState)
{
	TransitionByEventsTable& transitionByEvents = States_[fromState];
	transitionByEvents[event] = Transition(toState, &FiniteStateMachine::DoNothing);
}

void FiniteStateMachine::AddTransition(States fromState, Events event, States toState, Action action)
{
	TransitionByEventsTable& transitionByEvents = States_[fromState];
	transitionByEvents[event] = Transition(toState, action);
}


void FiniteStateMachine::Process(std::string& text)
{
	char lastOne = '#';
	const size_t length = text.length();
	for (size_t i = 0; i != length; ++i)
	{
		const char current = text[i];

		if (std::isdigit(current))
		{
			ProcessEvent(Digit_Ev);
			this->value += current;
		}
		else if (std::isalpha(current))
		{
			if (i == 0)
			{
				if (current == 's' || current == 'S') ProcessEvent(LetterS_Ev);
				else ProcessEvent(Letter_Ev);
			}
			else
			{
				if (lastOne == ' ')
				{
					if (current == 'a' || current == 'A')
						ProcessEvent(LetterA_Ev);
					else if (current == 'f' || current == 'F')
						ProcessEvent(LetterF_Ev);
					else if (current == 'l' || current == 'L')
						ProcessEvent(LetterL_Ev);
					else if (current == 'n' || current == 'N')
						ProcessEvent(LetterN_Ev);
					else if (current == 'o' || current == 'O')
						ProcessEvent(LetterO_Ev);
					else if (current == 'w' || current == 'W')
						ProcessEvent(LetterW_Ev);
					else if (current == 's' || current == 'S')
						ProcessEvent(LetterS_Ev);
					else ProcessEvent(Letter_Ev);
				}
				else if (lastOne == '(')
				{
					if (current == 's' || current == 'S')
						ProcessEvent(LetterS_Ev);
					else ProcessEvent(Letter_Ev);
				}
				else if (lastOne == 'e' || lastOne == 'E')
				{
					if (current == 'c' || current == 'C')
						ProcessEvent(LetterC_Ev);
					else if (current == 'l' || current == 'L')
						ProcessEvent(LetterL_Ev);
					else if (current == 'r' || current == 'R')
						ProcessEvent(LetterR_Ev);
					else if (current == 'l' || current == 'L')
						ProcessEvent(LetterL_Ev);
					else if (current == 'n' || current == 'N')
						ProcessEvent(LetterN_Ev);
					else if (current == 'o' || current == 'O')
						ProcessEvent(LetterO_Ev);
					else if (current == 'w' || current == 'W')
						ProcessEvent(LetterW_Ev);
					else ProcessEvent(Letter_Ev);
				}
				else if ((lastOne == 'n' || lastOne == 'N') && (current == 'd' || current == 'D'))
					ProcessEvent(LetterD_Ev);
				else if (current == 'e' || current == 'E')
				{
					if (lastOne == 's' || lastOne == 'S' || lastOne == 'l' || lastOne == 'L' || lastOne == 'h' ||
						lastOne == 'H' || lastOne == 'k' || lastOne == 'K' || lastOne == 'r' || lastOne == 'R')
						ProcessEvent(LetterE_Ev);
					else ProcessEvent(Letter_Ev);
				}
				else if (lastOne == 'o' || lastOne == 'O')
				{
					if (current == 'm' || current == 'M')
						ProcessEvent(LetterM_Ev);
					else if (current == 'r' || current == 'R')
						ProcessEvent(LetterR_Ev);
					else if (current == 't' || current == 'T')
						ProcessEvent(LetterT_Ev);
					else ProcessEvent(Letter_Ev);
				}
				else if (lastOne == 'i' || lastOne == 'I')
				{
					if (current == 'k' || current == 'K')
						ProcessEvent(LetterK_Ev);
					else if (current == 'n' || current == 'N')
						ProcessEvent(LetterN_Ev);
					else ProcessEvent(Letter_Ev);
				}
				else if ((lastOne == 'w' || lastOne == 'W') && (current == 'h' || current == 'H'))
					ProcessEvent(LetterH_Ev);
				else if ((lastOne == 'l' || lastOne == 'L') && (current == 'i' || current == 'I'))
					ProcessEvent(LetterI_Ev);
				else if ((lastOne == 'a' || lastOne == 'A') && (current == 'n' || current == 'N'))
					ProcessEvent(LetterN_Ev);
				else if ((lastOne == 'r' || lastOne == 'R') && (current == 'o' || current == 'O'))
					ProcessEvent(LetterO_Ev);
				else if ((lastOne == 'f' || lastOne == 'F') && (current == 'r' || current == 'R'))
					ProcessEvent(LetterR_Ev);
				else if ((lastOne == 'c' || lastOne == 'C') && (current == 't' || current == 'T'))
					ProcessEvent(LetterT_Ev);
				else ProcessEvent(Letter_Ev);
			}
			this->value += current;
		}
		else if (current == '\'')
		{
			ProcessEvent(Quote_Ev);
		}
		else if (current == '*')
		{
			ProcessEvent(Multiplication_Ev);
		}
		else if (current == '\\')
		{
			ProcessEvent(Division_Ev);
		}
		else if (current == '.')
		{
			ProcessEvent(Dot_Ev);
		}
		else if (current == ',')
		{
			ProcessEvent(Comma_Ev);
		}
		else if (current == ';')
		{
			ProcessEvent(Semicolon_Ev);
		}
		else if (current == '>')
		{
			ProcessEvent(More_Ev);
		}
		else if (current == '<')
		{
			ProcessEvent(Less_Ev);
		}
		else if (current == '=')
		{
			ProcessEvent(Equal_Ev);
		}
		else if (current == '(')
		{
			ProcessEvent(LeftBracket_Ev);
		}
		else if (current == ')')
		{
			ProcessEvent(RightBracket_Ev);
		}
		else if (std::isspace(current))
		{
			ProcessEvent(Space_Ev);
		}
		else
		{
			ProcessEvent(Space_Ev);
			this->value = current;
			ProcessEvent(Other_Ev);
		}
		lastOne = current;
	}
	ProcessEvent(Space_Ev);
}