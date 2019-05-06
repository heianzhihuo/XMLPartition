// SiblingPartition.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "SiblingPartition.h"
#include  "TreeNode.h"
#include "Partition.h"

int main()
{
	TreeNode c = TreeNode(1);
	int s1[2] = { 2,2 };
	for (int x : s1)
		c.addChildNode(new TreeNode(x));
	TreeNode root = TreeNode(3);
	root.addChildNode(new TreeNode(2));
	int s2[3] = { 1,1,2 };
	for (int x : s2)
		root.addChildNode(new TreeNode(x));

	root.postVisit();
	cout << endl;
	root.preVisit();
	cout << endl;

	Partition P = Partition(root);

	cout << P.card << endl;
	cout << P.rootweight << endl;
	


    cout << "Hello World!\n"; 
}

