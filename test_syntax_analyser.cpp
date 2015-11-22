#include <iostream>
#include "Events.h"
#include <iostream>
#include "FiniteStateMachine.h"
#include "Lexem.h"
#include "syntax_analyser.h"
#include <list>
#include <stack>

using namespace std;


int main(int argc, char *argv[])
{
	string testQuery;
	if (argc > 1) {
		testQuery = argv[1];
	} else {
		testQuery = "select name, price from items where a*b=c;";
	}

	cout << "========================================" << endl <<
		"1. Starting Lexical Analyze... " << endl <<
		"========================================" << endl <<
		"Parsing string \'" << testQuery << "\'." << endl;		 
	
	Machine::FiniteStateMachine machine;
        machine.Process(testQuery);

	for(std::list<Lexem::Lexem>::iterator it = machine.lexems.begin(); it != machine.lexems.end(); ++it)
        {
                std::cout << it->getType() << " " << it->getValue() << std::endl;
        }

	cout << "========================================" << endl <<
		"2. Starting Syntax Analyze... " << endl <<
		"========================================" << endl;
	SyntaxAnalyser analyser;
	bool success = analyser.analyse(machine.lexems);
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
	#ifdef WIN32
	system("pause");
	#endif // WIN32
	return 0;
}
