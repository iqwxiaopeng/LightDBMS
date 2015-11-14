#include "lexem.h"
#include <string>

Lexem::Lexem(LexemType type, std::string value) : type(type), value(value) {};
LexemType Lexem::getType() {
	return type;
}
std::string Lexem::getValue() {
	return value;
}