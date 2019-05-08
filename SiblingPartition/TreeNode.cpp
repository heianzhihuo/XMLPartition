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
/*获得根节点权值*/
int TreeNode::getNodeWeight()
{
	return weight;
}
void TreeNode::setNodeWeight(int w)
{
	this->weight = w;
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
void TreeNode::addChildNode(TreeNode& t)
{
	if (this->child.size() != 0)
		this->child[child.size() - 1].next = &t;
	this->child.push_back(t);
	t.parent = this;
}
/*获得子节点数*/
int TreeNode::getChildNum()
{
	return child.size();
}
int TreeNode::getID()
{
	return id;
}
TreeNode& TreeNode::getChild(int j)
{
	return child[j-1];
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
