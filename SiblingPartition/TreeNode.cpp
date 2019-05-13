#include "TreeNode.h"

TreeNode::TreeNode()
{
	this->id = -1;
	this->weight = 0;
	this->next = NULL;
	this->parent = NULL;
}

TreeNode::TreeNode(int w)
{
	this->id = -1;
	this->weight = w;
	this->next = NULL;
	this->parent = NULL;
}

TreeNode::TreeNode(int id, int weight)
{
	this->id = id;
	this->weight = weight;
	this->next = NULL;
	this->parent = NULL;
}

TreeNode::~TreeNode()
{
	this->child.clear();
}

/*获得树的权值*/
int TreeNode::getTreeWeight()
{
	int w = this->weight;
	for (TreeNode t : this->child)
		w += t.getTreeWeight();
	return w;
}
/*树的后序遍历*/
void TreeNode::postVisit()
{
	for (TreeNode c : child)
		c.postVisit();
	cout << id << ":" << weight << " ";
}
/*树的先序遍历*/
void TreeNode::preVisit()
{
	cout << id << ":" << weight << " ";
	for (TreeNode c : child)
		c.preVisit();
}
