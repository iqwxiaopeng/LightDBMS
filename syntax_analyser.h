#include <string>
#include <list>
#include "lexem.h"

#ifndef SYNTAX_ANALYSER_H
#define SYNTAX_ANALYSER_H

#define ERROR -1
#define SUCCESS -2

// struct SyntaxTree {
// 	std::string	node;
// 	std::list<SyntaxTree*> childs;
// };

class SyntaxAnalyser
{
private:
	int automaton[6][5] = {
		{1, ERROR, ERROR, ERROR, ERROR},
		{ERROR, 2, ERROR, ERROR, ERROR},
		{ERROR, ERROR, 4, ERROR, 3},
		{ERROR, 2, ERROR, ERROR, ERROR},
		{ERROR, 5, ERROR, ERROR, ERROR},
		{ERROR, ERROR, ERROR, SUCCESS, ERROR}
	};
	// int automaton[5][5] = {
	// 	{1, ERROR, ERROR, ERROR, ERROR},
	// 	{ERROR, 2, ERROR, ERROR, 2},
	// 	{ERROR, ERROR, 3, ERROR, ERROR},
	// 	{ERROR, 4, ERROR, ERROR, ERROR},
	// 	{ERROR, ERROR, ERROR, SUCCESS, ERROR}
	// };
public:
	SyntaxAnalyser() {};
	bool analyse(std::list<Lexem> lexemChain);
	~SyntaxAnalyser() {};
};

#endif