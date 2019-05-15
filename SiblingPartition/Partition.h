#pragma once
#include "SiblingPartition.h"
#include "TreeNode.h"

class Partition
{
public:
	Partition();
	~Partition();

	int card;
	int rootweight;

	int dw = 0;

	TreeNode begin, end;
	
	Partition* next;//表示下一个划分的位置
	//pair<int, int> next;
};

Partition* FlatTreeDynamicForTreeWidth(TreeNode root,int K);
void showPartition(Partition* p);

vector<Partition*> GreedyHeightDynamicWidth(TreeNode root, int K);
void showPartition(vector<Partition*> P);
int getGHDWPartitionCard(vector<Partition*> P);

int compare(Partition p1, Partition p2);
vector<Partition*> DynamicHeightWidth(TreeNode root, int K);