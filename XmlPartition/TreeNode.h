#pragma once
#include <vector>
#include <iostream>

using namespace std;

/*表示树的节点类型*/
class TreeNode
{
public:
	TreeNode();
	TreeNode(int w);
	TreeNode(int id, int weight);
	~TreeNode();
	void addChild(TreeNode *c);//向该节点儿子节点链表追加一个儿子节点
	int getTreeWeight();

	void postVisit();
	void preVisit();

	int id = -1;//默认为-1，用于标识不同节点
	int weight = -1;//节点权值
	vector<TreeNode*> child;//所有儿子节点
	TreeNode* parent = nullptr;//父节点
	TreeNode* next = nullptr;//右兄弟节点

	//存储该节点生成的子树的划分
	class Partition* par = nullptr;//表示这个子树的optimal partition
	class Partition* nopt = nullptr;//表示这个子树的nearly optimal partition
	int dw = 0;//ΔW
	bool isNopt = false;//表示在最优解中，这个子树采用了optimal 还是 nearly optimal

};

typedef TreeNode* Tree;