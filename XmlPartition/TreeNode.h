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

	class Partition* par = nullptr;//��ʾ���������optimal partition
	class Partition* nopt = nullptr;//��ʾ���������nearly optimal partition
	int dw = 0;//��W
	bool isNopt = false;//��ʾ�����Ž��У��������������optimal ���� nearly optimal

	void addChild(TreeNode *c);
};

typedef TreeNode* Tree;