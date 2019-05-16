// XmlPartition.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <ctime>
#include "TreeNode.h"
#include "Partition.h"

using namespace std;
int main()
{
	TreeNode* c = new TreeNode(3, 1);
	c->addChild(new TreeNode(7, 2));
	c->addChild(new TreeNode(8, 2));
	TreeNode* root = new TreeNode(1, 5);
	root->addChild(new TreeNode(2, 1));
	root->addChild(c);
	root->addChild(new TreeNode(4, 1));
	root->addChild(new TreeNode(5, 1));
	root->addChild(new TreeNode(6, 2));
	root->addChild(new TreeNode(9, 2));

	root->postVisit();
	cout << endl;

	root->preVisit();
	cout << endl;

	Partition *P = FlatTreeDynamicForTreeWidth(root, 5);
	showPartition(P);
	cout << endl;


	vector<Partition*> result = GreedyHeightDynamicWidth(root, 5);
	showPartition(result);
	cout << endl;

	DynamicHeightWidth(root, 5);
	int card = showPartition(root);
	cout << "Partition Card:" << card << endl;
	cout << endl;

    cout << "Hello World!\n"; 
}