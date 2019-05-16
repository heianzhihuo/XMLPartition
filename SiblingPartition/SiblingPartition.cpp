// SiblingPartition.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <ctime>
#include <stack>
#include <fstream>
#include <iostream>
#include <sstream>
#include "SiblingPartition.h"
#include  "TreeNode.h"
#include "Partition.h"
#include "XmlParser.h"



int main()
{
	/*clock_t start, end;
	TreeNode ttt(1, 10);
	
	start = clock();
	TreeNode sss = ttt;
	end = clock();
	cout << end - start << endl;

	for (int i = 0; i < 100; i++)
		ttt.child.push_back(TreeNode(i, i + 1));

	start = clock();
	TreeNode ssssss = ttt;
	end = clock();
	cout << end - start << endl;

	for (int i = 0; i < 10000; i++)
		ttt.child.push_back(TreeNode(i, i + 1));

	start = clock();
	TreeNode sssss = ttt;
	end = clock();
	cout << end - start << endl;

	for (int i = 0; i < 1000000; i++)
		ttt.child.push_back(TreeNode(i, i + 1));
	
	start = clock();
	TreeNode ssss = ttt;
	end = clock();
	cout << end - start << endl;*/


	TreeNode c = TreeNode(3,1);
	int w1[2] = { 2,2 };
	int id1[2] = {7,8};
	for (int i = 0; i < 2; i++)
		c.child.push_back(*(new TreeNode(id1[i], w1[i])));
	TreeNode root = TreeNode(1,5);
	root.child.push_back(*(new TreeNode(2,1)));
	root.child.push_back(c);
	//int w2[] = { 2,1,2,2,3};
	//int id2[] = { 4,5,6,9,10 };
	int w2[] = { 1};
	int id2[] = { 4};
	for (int i = 0; i < 1; i++)
		root.child.push_back(*(new TreeNode(id2[i], w2[i])));

	root.postVisit();
	cout << endl;
	root.preVisit();
	cout << endl;

	//Partition P = Partition(root);

	//cout << P.card << endl;
	//cout << P.rootweight << endl;
	
	Partition* P = FlatTreeDynamicForTreeWidth(root, 5);
	showPartition(P);
	//showFDWPartition(D,root.weight);

	cout << endl;

	vector<Partition*> result = GreedyHeightDynamicWidth(root, 5);
	showPartition(result);
	//cout << getGHDWPartitionNum(result, root)<<endl;

	//cout << endl;

	vector<Partition*> reslt = DynamicHeightWidth(root, 5);

	cout << endl << "DynamicHeightDynamicWidth" << endl;
	showPartition(reslt);



	XmlParser xmlParser;
	ifstream infile("xtest.xml");
	if (!infile.is_open())
	{
		cout << "文件未成功打开!!!" << endl;
	}
	stringstream buffer;
	buffer << infile.rdbuf();
	string strXml = buffer.str();
	string temp(strXml);
	
	//xmlParser.ParseXml(strXml);
	cout << xmlParser.id << endl;

	//xmlParser.printXmlData(xmlParser.xmlDocument);


	//xmlParser.root.preVisit();

	cout << "XM" << endl;

	//vector<Partition*> rst = GreedyHeightDynamicWidth(xmlParser.root, 8);
	//showGHDWPartition(rresu, xmlParser.root);
	//cout << getGHDWPartitionNum(rresu, xmlParser.root) << endl;

	
	//xmlParser.ParseXmlToTree(temp);
	
}

