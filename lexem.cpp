#include "lexem.h"
#include <string>

namespace Lexem {
	Lexem::Lexem(LexemType type, std::string value) : type(type), value(value) {}

	Lexem::~Lexem() {}

	LexemType Lexem::getType() {
		return type;
	}

	std::string Lexem::getValue() {
		return value;
	}
}
