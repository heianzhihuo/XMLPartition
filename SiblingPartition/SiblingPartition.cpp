// SiblingPartition.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "SiblingPartition.h"
#include  "TreeNode.h"
#include "Partition.h"

int main()
{
	TreeNode c = TreeNode(3,1);
	int w1[2] = { 2,2 };
	int id1[2] = {7,8};
	for (int i = 0; i < 2; i++)
		c.addChildNode(new TreeNode(id1[i], w1[i]));
	TreeNode root = TreeNode(1,3);
	root.addChildNode(new TreeNode(2,2));
	root.addChildNode(&c);
	int w2[3] = { 1,1,2 };
	int id2[3] = { 4,5,6 };
	for (int i = 0; i < 3; i++)
		root.addChildNode(new TreeNode(id2[i], w2[i]));

	root.postVisit();
	cout << endl;
	root.preVisit();
	cout << endl;

	//Partition P = Partition(root);

	//cout << P.card << endl;
	//cout << P.rootweight << endl;
	
	vector<vector<Partition>> D = FlatTreeDynamicForTreeWidth(root, 5);
	showPartition(D,root.getNodeWeight());

    cout << "Hello World!\n"; 
}

