#include "syntax_analyser.h"
#include "syntax_tree.h"
#include "lexem.h"
#include <string>
#include <iostream>
#include <list>
#include <stack>

using namespace std;

// void printTree(SyntaxTree* cur_node, int level) {
// 	for (int i = 0; i < level; ++i)
// 	{
// 		cout << "\t";
// 	}
// 	cout << cur_node->node <<endl;

// 	for (auto it=cur_node->childs.begin(); it != cur_node->childs.end(); ++it) {
// 		printTree(*it, level+1);
// 	}
// }

bool SyntaxAnalyser::analyse(std::list<Lexem> lexemChain) {
	int state = 0;
	int new_state;
	SyntaxTree root;
	root.setType(SyntaxTreeType::ROOT);
	stack<SyntaxTree*> s;
	SyntaxTree* new_node;
	s.push(&root);
	for (auto it=lexemChain.begin(); it != lexemChain.end(); ++it) {
		if (state == ERROR)
			break;
		new_state = automaton[state][(int)it->getType()];
		switch	(state) {
			case 0:
				new_node = s.top()->addNewChild(SyntaxTreeType::QUERY);
				s.push(new_node);

				new_node = s.top()->addNewChild(SyntaxTreeType::SFW);
				s.push(new_node);

				new_node = s.top()->addNewChild(SyntaxTreeType::SELECT);
				break;
			case 1:
				new_node = s.top()->addNewChild(SyntaxTreeType::SELECTLIST);
				s.push(new_node);

				new_node = s.top()->addNewChild(SyntaxTreeType::ATTRIBUTE);
				s.push(new_node);

				new_node = s.top()->addNewChild(SyntaxTreeType::PATTERN, it->getValue());
				s.pop();
				break;
			case 2:
				if (new_state == 4) {
					s.pop();
					new_node = s.top()->addNewChild(SyntaxTreeType::FROM);
					s.push(new_node);
				}
				break;
			case 3:
				new_node = s.top()->addNewChild(SyntaxTreeType::ATTRIBUTE);
				s.push(new_node);

				new_node = s.top()->addNewChild(SyntaxTreeType::PATTERN, it->getValue());
				s.pop();
				break;
			case 4:
				new_node = s.top()->addNewChild(SyntaxTreeType::FROMLIST);
				s.push(new_node);

				new_node = s.top()->addNewChild(SyntaxTreeType::RELATION);
				s.push(new_node);

				new_node = s.top()->addNewChild(SyntaxTreeType::PATTERN, it->getValue());
		}
		state = new_state;
		cout << state << endl;
	}

	root.printTree();
	return state == SUCCESS;
}