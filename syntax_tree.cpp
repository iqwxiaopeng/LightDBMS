#include "syntax_tree.h"
#include <string>
#include <list>
#include <iostream>

std::string syntaxTreeTypeNames[21] = {
	"ROOT", "SELECT", "QUERY", "FROM", "SFW", "WHERE",
	"EQUAL", "IN", "LESS", "MORE", "SELECTLIST",
	"ATTRIBUTE", "FROMLIST", "RELATION",
	"CONDITION", "OR", "AND", "NOT", "TUPLE",
	"IDENTIFICATOR", "PATTERN"
};

SyntaxTreeType SyntaxTree::getType() {
	return type;
}
std::string SyntaxTree::getValue() {
	return value;
}

void SyntaxTree::setType(SyntaxTreeType type) {
	this->type = type;
}

void SyntaxTree::setValue(std::string value) {
	this->value = value;
}

std::list<SyntaxTree*>* SyntaxTree::getChilds() {
	return &childs;
}

SyntaxTree* SyntaxTree::addNewChild(SyntaxTreeType type, std::string value) {
	SyntaxTree* new_node = new SyntaxTree();
	new_node->setType(type);
	new_node->setValue(value);
	this->childs.push_back(new_node);
	return new_node;
}

void SyntaxTree::printTree(SyntaxTree* cur_node, int level) {
	for (int i = 0; i < level; ++i)
	{
		std::cout << "\t";
	}
	std::cout << syntaxTreeTypeNames[(int)cur_node->getType()];
	if (cur_node->getValue() != "")
		std::cout << " <" << cur_node->getValue() << ">";
	std::cout << std::endl;

	for (auto it=cur_node->getChilds()->begin(); it != cur_node->getChilds()->end(); ++it) {
		printTree(*it, level+1);
	}
}

void SyntaxTree::printTree() {
	printTree(this, 0);
}