#include "TreeNode.h"

TreeNode::TreeNode()
{
	weight = 0;
	this->next = NULL;
	this->parent = NULL;
}

TreeNode::TreeNode(int weight)
{
	this->weight = weight;
	this->next = NULL;
	this->parent = NULL;
}

TreeNode::~TreeNode()
{
	this->child.clear();
}
/*获得根节点权值*/
int TreeNode::getRootNodeWeight()
{
	return 0;
}
/*获得树的权值*/
int TreeNode::getTreeWeight()
{
	int w = this->weight;
	for (TreeNode t : this->child)
		w += t.getTreeWeight();
	return w;
}
/*给根节点添加一个子节点*/
void TreeNode::addChildNode(TreeNode * t)
{
	if (this->child.size() != 0)
		this->child[child.size() - 1].next = t;
	this->child.push_back(*t);
	t->parent = this;
}
/*树的后序遍历*/
void TreeNode::postVisit()
{
	for (TreeNode c : child)
		c.postVisit();
	cout << weight << " ";
}
/*树的先序遍历*/
void TreeNode::preVisit()
{
	cout << weight << " ";
	for (TreeNode c : child)
		c.preVisit();
}
