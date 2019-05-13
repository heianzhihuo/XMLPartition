#pragma once
#include "SiblingPartition.h"
class TreeNode
{
public:
	TreeNode();
	TreeNode(int w);
	TreeNode(int id, int weight);
	~TreeNode();

	int getTreeWeight();

	void postVisit();
	void preVisit();

	int id;
	int weight;
	vector<TreeNode> child;
	TreeNode* parent;
	TreeNode* next;
};

typedef TreeNode Tree;