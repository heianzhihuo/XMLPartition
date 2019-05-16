#pragma once
#include "TreeNode.h"

class Partition
{
public:
	Partition();
	~Partition();
	int card;
	int rootweight;

	TreeNode*begin = nullptr,*end = nullptr;

	Partition* next = nullptr;//表示下一个划分的位置
};

Partition* FlatTreeDynamicForTreeWidth(TreeNode* root, int K);
void showPartition(Partition* p);

vector<Partition*> GreedyHeightDynamicWidth(TreeNode* root, int K);
void showPartition(vector<Partition*> P);

int getPartitionCard(vector<Partition*> P);
int getPartitionCard(TreeNode *root);
int showPartition(TreeNode *root);

bool compare(TreeNode* p1,TreeNode *p2);
//vector<Partition*> DynamicHeightWidth(TreeNode* root, int K);
void DynamicHeightWidth(TreeNode* root, int K);