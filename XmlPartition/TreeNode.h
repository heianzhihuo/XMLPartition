#pragma once
#include <vector>
#include <iostream>

using namespace std;

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

	int id = -1;
	int weight = -1;
	vector<TreeNode*> child;
	TreeNode* parent = nullptr;
	TreeNode* next = nullptr;

	class Partition* par = nullptr;//表示这个子树的optimal partition
	class Partition* nopt = nullptr;//表示这个子树的nearly optimal partition
	int dw = 0;//ΔW
	bool isNopt = false;//表示在最优解中，这个子树采用了optimal 还是 nearly optimal

	void addChild(TreeNode *c);
};

typedef TreeNode* Tree;