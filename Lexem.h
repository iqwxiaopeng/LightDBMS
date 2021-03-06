#ifndef LEXEM_H
#define LEXEM_H

#include <string>

namespace Lexem{

	enum LexemType
	{
		SELECT, IDENTIFIER, FROM, SEMICOLON, COMMA, STAR, WHERE, IN, NOT, AND, OR,
		LIKE, EXISTS, MORE, LESS, EQUAL, CONSTANT, STRING, MULTIPLY, DIVISION, DOT, OTHER, LEFTBRACKET, RIGHTBRACKET
	};

	class Lexem
	{
		LexemType type;
		std::string value;
	public:
		Lexem(LexemType type, std::string value);
		~Lexem();

		LexemType getType();
		std::string getValue();
	};
}
#endif
