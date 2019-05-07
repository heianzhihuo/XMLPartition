#pragma once
#include "SiblingPartition.h"
class TreeNode
{
public:
	TreeNode();
	TreeNode(int w);
	TreeNode(int id, int weight);
	~TreeNode();
	int getNodeWeight();
	int getTreeWeight();
	void addChildNode(TreeNode* t);
	int getChildNum();
	int getID();

	TreeNode getChild(int j);

	void postVisit();
	void preVisit();

private:
	int id;
	int weight;
	vector<TreeNode> child;
	TreeNode* parent;
	TreeNode* next;
};

typedef TreeNode Tree;