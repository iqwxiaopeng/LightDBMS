#include <iostream>
#include "lexem.h"
#include "syntax_analyser.h"
#include <list>
#include <stack>

using namespace std;

int main(int argc, char *argv[])
{
	Lexem l1(LexemType::SELECT, "");
	Lexem l2(LexemType::IDENTIFIER, "name");
	Lexem l2_1(LexemType::COMMA, "");
	Lexem l2_2(LexemType::IDENTIFIER, "price");
	Lexem l3(LexemType::FROM, "");
	Lexem l4(LexemType::IDENTIFIER, "items");
	Lexem l5(LexemType::SEMICOLON, "");

	list<Lexem> lexemChain;
	lexemChain.push_back(l1);
	lexemChain.push_back(l2);
	lexemChain.push_back(l2_1);
	lexemChain.push_back(l2_2);
	lexemChain.push_back(l3);
	lexemChain.push_back(l4);
	lexemChain.push_back(l5);

	SyntaxAnalyser analyser;
	bool success = analyser.analyse(lexemChain);
	if (success)
		cout << "Success!" << endl;
	else
		cout << "Error!" << endl;

	// stack<int> s;
	// s.push(10);
	// s.push(30);
	// while (!s.empty()) {
	// 	cout << s.top() << endl;
	// 	s.pop();
	// }


	// cout << (int)l2.getType() << endl;
	// cout << l2.getValue() << endl;
}