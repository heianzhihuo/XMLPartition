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

/*�������Ȩֵ*/
int TreeNode::getTreeWeight()
{
	int w = this->weight;
	for (TreeNode* t : child)
		w += t->getTreeWeight();
	return w;
}
/*���ĺ������*/
void TreeNode::postVisit()
{
	for (TreeNode* c : child)
		c->postVisit();
	cout << id << ":" << weight << " ";
}
/*�����������*/
void TreeNode::preVisit()
{
	cout << id << ":" << weight << " ";
	for (TreeNode* c : child)
		c->preVisit();
}

void TreeNode::addChild(TreeNode * c)
{
	if (child.size() != 0)
		child[child.size() - 1]->next = c;
	child.push_back(c);
	c->parent = this;
}
