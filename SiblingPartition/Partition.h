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
	
	Partition* next;//��ʾ��һ�����ֵ�λ��
	//pair<int, int> next;
};

Partition* FlatTreeDynamicForTreeWidth(TreeNode root,int K);
void showFDWPartition(Partition* p);

vector<Partition*> GreedyHeightDynamicWidth(TreeNode root, int K);
void showGHDWPartition(vector<Partition*> P);
int getGHDWPartitionCard(vector<Partition*> P);