#ifndef LEXEM_H
#define LEXEM_H

#include <string>

namespace Lexem{

        enum LexemType
        {
                IDENTIFIER, CONSTANT, STRING, MULTIPLY, DIVISION, DOT, COMMA, SPACE, SEMICOLON, COMPARSION, OTHER
        };

        class Lexem
        {
                LexemType type;
                std::string value;
        public:
                Lexem(LexemType type, std::string value) : type(type), value(value) {};
                ~Lexem() {};

                LexemType getType() { return type; }
                std::string getValue() { return value; }
        };
}
#endif
