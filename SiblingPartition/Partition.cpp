#include "Partition.h"

Partition::Partition()
{
	card = 0;
	rootweight = 0;
}

Partition::Partition(TreeNode root)
{
	card = 1;
	intervals.push_back(make_pair(root, root));
	rootweight = root.getTreeWeight();
}

Partition::~Partition()
{
	intervals.clear();
}

void Partition::addInterval(TreeNode begin, TreeNode end)
{
	this->intervals.push_back(make_pair(begin,end));
}
