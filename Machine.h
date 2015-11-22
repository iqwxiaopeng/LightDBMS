#include "Events.h"
#include "Lexem.h"
#include <list>
#include <boost/statechart/state_machine.hpp>
#include "FiniteStateMachine.h"

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
	struct More;
	struct Less;
	struct Equal;
	struct Other;

	struct A;
	struct F;
	struct L;
	struct N;
	struct O;
	struct S;
	struct W;

	struct AN;
	struct FR;
	struct LI;
	struct NO;
	struct OR;
	struct SE;
	struct WH;

	struct AND;
	struct FRO;
	struct LIK;
	struct NOT;
	struct SEL;
	struct WHE;

	struct FROM;
	struct LIKE;
	struct SELE;
	struct WHER;

	struct SELEC;
	struct WHERE;

	struct SELECT;
}

namespace Machine {
	class FiniteStateMachine
	{
	public:
		FiniteStateMachine() {};
		~FiniteStateMachine() { lexems.clear(); value.clear(); }

		std::string value;
		std::list<Lexem::Lexem> lexems;

		void Process(std::string& text);

		void FoundIdent() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::IDENTIFIER, this->value));	value = ""; }
		void FoundConstant() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::CONSTANT, this->value));  value = ""; }
		void FoundString_() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::STRING, this->value));  value = ""; }
		void FoundMultiply() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::MULTIPLY, "*"));			value = ""; }
		void FoundDivision() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::DIVISION, "/"));			value = ""; }
		void FoundDot() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::DOT, "."));			value = ""; }
		void FoundComma() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::COMMA, ","));			value = ""; }
		void FoundSpace() { value = ""; }
		void FoundSemicolon() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::SEMICOLON, ";"));			value = ""; }
		void FoundMore() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::MORE, this->value));	value = ""; }
		void FoundLess() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::LESS, this->value));	value = ""; }
		void FoundEqual() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::EQUAL, this->value));	value = ""; }
		void FoundOther() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::OTHER, this->value)); }
		void FoundSelect() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::SELECT, ""));			value = ""; }
		void FoundFrom() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::FROM, ""));			value = ""; }
		void FoundWhere() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::WHERE, ""));			value = ""; }
		void FoundAnd() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::AND, ""));			value = ""; }
		void FoundOr() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::OR, ""));			value = ""; }
		void FoundNot() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::NOT, ""));			value = ""; }
		void FoundLike() { lexems.push_back(Lexem::Lexem(Lexem::LexemType::LIKE, ""));			value = ""; }
	};


	struct Machine : boost::statechart::state_machine<Machine, States::Start>
	{
		Machine(FiniteStateMachine& mainMachine) : MainMachine_(mainMachine) {}

		void FoundIdent(const Events::Space&) { MainMachine_.FoundIdent(); }
		void FoundIdent(const Events::Multiplication&) { MainMachine_.FoundIdent(); }
		void FoundIdent(const Events::Division&) { MainMachine_.FoundIdent(); }
		void FoundIdent(const Events::Dot&) { MainMachine_.FoundIdent(); }
		void FoundIdent(const Events::Comma&) { MainMachine_.FoundIdent(); }
		void FoundIdent(const Events::More&) { MainMachine_.FoundIdent(); }
		void FoundIdent(const Events::Less&) { MainMachine_.FoundIdent(); }
		void FoundIdent(const Events::Equal&) { MainMachine_.FoundIdent(); }
		void FoundIdent(const Events::Semicolon&) { MainMachine_.FoundIdent(); }

		void FoundConstant(const Events::Space&) { MainMachine_.FoundConstant(); }
		void FoundConstant(const Events::More&) { MainMachine_.FoundConstant(); }
		void FoundConstant(const Events::Less&) { MainMachine_.FoundConstant(); }
		void FoundConstant(const Events::Equal&) { MainMachine_.FoundConstant(); }
		void FoundConstant(const Events::Multiplication&) { MainMachine_.FoundConstant(); }
		void FoundConstant(const Events::Division&) { MainMachine_.FoundConstant(); }
		void FoundConstant(const Events::Dot&) { MainMachine_.FoundConstant(); }
		void FoundConstant(const Events::Comma&) { MainMachine_.FoundConstant(); }
		void FoundConstant(const Events::Semicolon&) { MainMachine_.FoundConstant(); }

		void FoundString_(const Events::Quote&) { MainMachine_.FoundString_(); }

		void FoundMultiply(const Events::Digit&) { MainMachine_.FoundMultiply(); }
		void FoundMultiply(const Events::Letter&) { MainMachine_.FoundMultiply(); }
		void FoundMultiply(const Events::Quote&) { MainMachine_.FoundMultiply(); }
		void FoundMultiply(const Events::Dot&) { MainMachine_.FoundMultiply(); }
		void FoundMultiply(const Events::Space&) { MainMachine_.FoundMultiply(); }

		void FoundDivision(const Events::Digit&) { MainMachine_.FoundDivision(); }
		void FoundDivision(const Events::Letter&) { MainMachine_.FoundDivision(); }
		void FoundDivision(const Events::Space&) { MainMachine_.FoundDivision(); }

		void FoundDot(const Events::Letter&) { MainMachine_.FoundDot(); }

		void FoundComma(const Events::Digit&) { MainMachine_.FoundComma(); }
		void FoundComma(const Events::Letter&) { MainMachine_.FoundComma(); }
		void FoundComma(const Events::Space&) { MainMachine_.FoundComma(); }

		void FoundSpace(const Events::Digit&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Letter&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Quote&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Multiplication&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Division&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Dot&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Comma&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Space&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Semicolon&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::More&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Less&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::Equal&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::LetterA&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::LetterF&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::LetterL&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::LetterN&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::LetterO&) { MainMachine_.FoundSpace(); }
		void FoundSpace(const Events::LetterW&) { MainMachine_.FoundSpace(); }

		void FoundSemicolon(const Events::Space&) { MainMachine_.FoundSemicolon(); }

		void FoundMore(const Events::Digit&) { MainMachine_.FoundMore(); }
		void FoundMore(const Events::Letter&) { MainMachine_.FoundMore(); }
		void FoundMore(const Events::Quote&) { MainMachine_.FoundMore(); }
		void FoundMore(const Events::Space&) { MainMachine_.FoundMore(); }
		void FoundMore(const Events::More&) { MainMachine_.FoundMore(); }
		void FoundMore(const Events::Less&) { MainMachine_.FoundMore(); }
		void FoundMore(const Events::Equal&) { MainMachine_.FoundMore(); }

		void FoundLess(const Events::Digit&) { MainMachine_.FoundLess(); }
		void FoundLess(const Events::Letter&) { MainMachine_.FoundLess(); }
		void FoundLess(const Events::Quote&) { MainMachine_.FoundLess(); }
		void FoundLess(const Events::Space&) { MainMachine_.FoundLess(); }
		void FoundLess(const Events::More&) { MainMachine_.FoundLess(); }
		void FoundLess(const Events::Less&) { MainMachine_.FoundLess(); }
		void FoundLess(const Events::Equal&) { MainMachine_.FoundLess(); }

		void FoundEqual(const Events::Digit&) { MainMachine_.FoundEqual(); }
		void FoundEqual(const Events::Letter&) { MainMachine_.FoundEqual(); }
		void FoundEqual(const Events::Quote&) { MainMachine_.FoundEqual(); }
		void FoundEqual(const Events::Space&) { MainMachine_.FoundEqual(); }
		void FoundEqual(const Events::More&) { MainMachine_.FoundEqual(); }
		void FoundEqual(const Events::Less&) { MainMachine_.FoundEqual(); }
		void FoundEqual(const Events::Equal&) { MainMachine_.FoundEqual(); }

		void FoundOther(const Events::Digit&) { MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Letter&) { MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Quote&) { MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Multiplication&) { MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Division&) { MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Dot&) { MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Comma&) { MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Space&) { MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Semicolon&) { MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::More&) { MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Less&) { MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Equal&) { MainMachine_.FoundOther(); this->terminate(); }
		void FoundOther(const Events::Other&) { MainMachine_.FoundOther(); this->terminate(); }

		void FoundSelect(const Events::Space&) { MainMachine_.FoundSelect(); }
		void FoundFrom(const Events::Space&) { MainMachine_.FoundFrom(); }
		void FoundWhere(const Events::Space&) { MainMachine_.FoundWhere(); }
		void FoundAnd(const Events::Space&) { MainMachine_.FoundAnd(); }
		void FoundOr(const Events::Space&) { MainMachine_.FoundOr(); }
		void FoundNot(const Events::Space&) { MainMachine_.FoundNot(); }
		void FoundLike(const Events::Space&) { MainMachine_.FoundLike(); }
	private:
		FiniteStateMachine& MainMachine_;
	};
}
