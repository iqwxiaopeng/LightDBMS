#include <string>
#include <list>

#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

enum class SyntaxTreeType 
	{ 	
		ROOT, SELECT, QUERY, FROM, SFW, WHERE,
		EQUAL, IN, LESS, MORE, SELECTLIST,
		ATTRIBUTE, FROMLIST, RELATION,
		CONDITION, OR, AND, NOT, TUPLE,
		IDENTIFICATOR, PATTERN
	};

class SyntaxTree
{
private:
	SyntaxTreeType type;
	std::string value;
	std::list<SyntaxTree*> childs;
	// std::stack<SyntaxTree*> nodeStack;
	void printTree(SyntaxTree* cur_node, int level);
public:
	SyntaxTree() {};
	std::list<SyntaxTree*>* getChilds();
	SyntaxTreeType getType();
	std::string getValue();
	void setType(SyntaxTreeType type);
	void setValue(std::string value);
	SyntaxTree* addNewChild(SyntaxTreeType type, std::string value);
	SyntaxTree* addNewChild(SyntaxTreeType type) { return addNewChild(type, ""); };
	void printTree();
	~SyntaxTree() {};
	
};

#endif