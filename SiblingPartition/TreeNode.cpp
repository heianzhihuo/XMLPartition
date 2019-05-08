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
/*��ø��ڵ�Ȩֵ*/
int TreeNode::getNodeWeight()
{
	return weight;
}
void TreeNode::setNodeWeight(int w)
{
	this->weight = w;
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
void TreeNode::addChildNode(TreeNode& t)
{
	if (this->child.size() != 0)
		this->child[child.size() - 1].next = &t;
	this->child.push_back(t);
	t.parent = this;
}
/*����ӽڵ���*/
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
/*���ĺ������*/
void TreeNode::postVisit()
{
	for (TreeNode c : child)
		c.postVisit();
	cout << id << ":" << weight << " ";
}
/*�����������*/
void TreeNode::preVisit()
{
	cout << id << ":" << weight << " ";
	for (TreeNode c : child)
		c.preVisit();
}
