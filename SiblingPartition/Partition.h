#pragma once
#include "SiblingPartition.h"
#include "TreeNode.h"

class Partition
{
public:
	Partition();
	Partition(TreeNode root);
	~Partition();
	void addInterval(TreeNode begin,TreeNode end);

	int card;
	int rootweight;
	vector<pair<TreeNode, TreeNode>> intervals;
	
};

class FlatPartitionTable
{
public:
	FlatPartitionTable();
	~FlatPartitionTable();


private:

};

FlatPartitionTable::FlatPartitionTable()
{
}

FlatPartitionTable::~FlatPartitionTable()
{
}

