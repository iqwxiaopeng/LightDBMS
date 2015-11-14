#include <string>

#ifndef LEXEM_H
#define LEXEM_H

enum class LexemType { SELECT, IDENTIFIER, FROM, SEMICOLON, COMMA, STAR, WHERE, IN, NOT, AND, OR, LIKE, EXIST, MORE, LESS, EUQAL};

class Lexem
{
private:
	LexemType type;
	std::string value;
public:
	Lexem(LexemType type, std::string value);
	LexemType getType();
	std::string getValue();
	~Lexem() {};
	
};

#endif