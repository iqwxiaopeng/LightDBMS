#ifndef LEXEM_H
#define LEXEM_H

#include <string>

namespace Lexem{

	enum LexemType
	{
		IDENTIFIER, CONSTANT, STRING, MULTIPLY, DIVISION, DOT, COMMA, SPACE, SEMICOLON, MORE, LESS, EQUAL, OTHER,
		SELECT, FROM, WHERE, NOT, AND, OR, LIKE
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
