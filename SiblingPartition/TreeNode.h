#pragma once
#include "SiblingPartition.h"
class TreeNode
{
public:
	TreeNode();
	TreeNode(int weight);
	~TreeNode();
	int getRootNodeWeight();
	int getTreeWeight();
	void addChildNode(TreeNode* t);

	void postVisit();
	void preVisit();

private:
	int weight;
	vector<TreeNode> child;
	TreeNode* parent;
	TreeNode* next;
};