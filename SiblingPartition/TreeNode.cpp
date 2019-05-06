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
/*��ø��ڵ�Ȩֵ*/
int TreeNode::getRootNodeWeight()
{
	return 0;
}
/*�������Ȩֵ*/
int TreeNode::getTreeWeight()
{
	int w = this->weight;
	for (TreeNode t : this->child)
		w += t.getTreeWeight();
	return w;
}
/*�����ڵ����һ���ӽڵ�*/
void TreeNode::addChildNode(TreeNode * t)
{
	if (this->child.size() != 0)
		this->child[child.size() - 1].next = t;
	this->child.push_back(*t);
	t->parent = this;
}
/*���ĺ������*/
void TreeNode::postVisit()
{
	for (TreeNode c : child)
		c.postVisit();
	cout << weight << " ";
}
/*�����������*/
void TreeNode::preVisit()
{
	cout << weight << " ";
	for (TreeNode c : child)
		c.preVisit();
}
