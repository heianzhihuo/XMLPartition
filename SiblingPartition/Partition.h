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
	TreeNode begin, end;
	
	pair<int, int> next;
};

vector<vector<Partition>> FlatTreeDynamicForTreeWidth(TreeNode root,int K);

void showPartition(vector<vector<Partition>> D,int rootweight);