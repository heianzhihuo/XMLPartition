#pragma once
#include <vector>
#include <iostream>

using namespace std;

/*��ʾ���Ľڵ�����*/
class TreeNode
{
public:
	TreeNode();
	TreeNode(int w);
	TreeNode(int id, int weight);
	~TreeNode();
	void addChild(TreeNode *c);//��ýڵ���ӽڵ�����׷��һ�����ӽڵ�
	int getTreeWeight();

	void postVisit();
	void preVisit();

	int id = -1;//Ĭ��Ϊ-1�����ڱ�ʶ��ͬ�ڵ�
	int weight = -1;//�ڵ�Ȩֵ
	vector<TreeNode*> child;//���ж��ӽڵ�
	TreeNode* parent = nullptr;//���ڵ�
	TreeNode* next = nullptr;//���ֵܽڵ�

	//�洢�ýڵ����ɵ������Ļ���
	class Partition* par = nullptr;//��ʾ���������optimal partition
	class Partition* nopt = nullptr;//��ʾ���������nearly optimal partition
	int dw = 0;//��W
	bool isNopt = false;//��ʾ�����Ž��У��������������optimal ���� nearly optimal

};

typedef TreeNode* Tree;