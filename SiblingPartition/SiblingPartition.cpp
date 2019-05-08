// SiblingPartition.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "SiblingPartition.h"
#include  "TreeNode.h"
#include "Partition.h"
#include <ctime>
#include <stack>

int main()
{
	TreeNode c = TreeNode(3,1);
	int w1[2] = { 2,2 };
	int id1[2] = {7,8};
	for (int i = 0; i < 2; i++)
		c.addChildNode(*(new TreeNode(id1[i], w1[i])));
	TreeNode root = TreeNode(1,3);
	root.addChildNode(*(new TreeNode(2,2)));
	root.addChildNode(c);
	int w2[] = { 2,1,2,2,3};
	int id2[] = { 4,5,6,7,8 };
	for (int i = 0; i < 5; i++)
		root.addChildNode(*(new TreeNode(id2[i], w2[i])));

	root.postVisit();
	cout << endl;
	root.preVisit();
	cout << endl;

	//Partition P = Partition(root);

	//cout << P.card << endl;
	//cout << P.rootweight << endl;
	
	vector<vector<Partition>> D = FlatTreeDynamicForTreeWidth(root, 5);
	showFDWPartition(D,root.getNodeWeight());

	vector<vector<vector<Partition>>> result = GreedyHeightDynamicWidth(root, 5);

	cout << endl;

	TreeNode* r = &root;
	cout << r->getChild(1).getNodeWeight() << endl;
	root.getChild(1).setNodeWeight(10);
	cout << root.getChild(1).getNodeWeight() << endl;

	TreeNode *child = &root.getChild(1);
	vector<TreeNode*> stack;
	stack.push_back(&root.getChild(1));

	child->setNodeWeight(11);
	cout << child->getNodeWeight() << endl;
	cout << root.getChild(1).getNodeWeight() << endl;

	stack[0]->setNodeWeight(13);
	cout << child->getNodeWeight() << endl;
	cout << root.getChild(1).getNodeWeight() << endl;

	cout << "Hello World!\n";
	
}

