// XmlPartition.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "TreeNode.h"
#include "Partition.h"
#include "XmlParser.h"

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
	string test = "Hello World\n";
	cout << test.find_first_of(" ", 0, 4) << endl;


	XmlParser xmlParser;
	//ifstream infile("uwm.xml");
	//ifstream infile("xtest.xml");
	ifstream infile("SigmodRecord.xml");
	
	if (!infile.is_open())
	{
		cout << "文件未成功打开!!!" << endl;
	}
	stringstream buffer;
	buffer << infile.rdbuf();
	string strXml = buffer.str();
	string temp(strXml);

	TreeNode* r = xmlParser.ParseToTree(temp);
	cout << xmlParser.id << endl;
	clock_t start, end;
	//r->preVisit();
	start = clock();
	vector<Partition*> PP = GreedyHeightDynamicWidth(r, 352);
	end = clock();
	cout << (end - start) / CLOCKS_PER_SEC << "s" << endl;
	
	//showPartition(PP);
	cout << getPartitionCard(PP)<<endl;

	start = clock();
	DynamicHeightWidth(r, 352);
	end = clock();
	cout << (end - start) / CLOCKS_PER_SEC << "s" << endl;
	cout << getPartitionCard(r) << endl;

	/*cout << endl;
	DynamicHeightWidth(r, 8);
	int crd = showPartition(r);
	cout << "Partition Card:" << crd << endl;
*/
	
	//r->preVisit();

}