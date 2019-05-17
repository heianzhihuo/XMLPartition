#include "XmlParser.h"
#include <stack>
#include <string>

TreeNode* XmlParser::ParseToTree(string strXml)
{
	//int id = 0;
	TreeNode *root = nullptr;
	int n = strXml.length();
	stack<pair<int, int>> Stack;
	stack<TreeNode*> treeStack;
	for (int k = 0; k < n;) {
		int i = strXml.find_first_of('<', k);
		int j = strXml.find_first_of('>', k);
		if (i == -1 && j == -1)
			break;
		if (i >= j) {
			cout << k<<","<<i<<","<<j << endl;
			cout << strXml.substr(k, i - k) << endl;
			cout << strXml.substr(k, j - k) << endl;
			cout << "Error Xml(括号不匹配)!!!" << endl;
			exit(1);
		}
		if (strXml[i + 1] == '/') {
			if (Stack.empty()) {
				cout << "Error Xml!!!（标签不匹配）" << endl;
				exit(1);
			}
			TreeNode* current = treeStack.top();
			int a = Stack.top().first, b = Stack.top().second;
			int tag_len = b-a-1;
			if (strXml.compare(a + 1, tag_len, strXml, i + 2, tag_len) != 0) {
				cout << tag_len << endl;
				cout << strXml.substr(a+1, b - a)<<endl;
				cout << strXml.substr(i, j-i+1) << endl;
				cout << "Error Xml!!!（标签不相同）" << endl;
				exit(1);
			}
			int c;
			for (c = k + 1; c < i && strXml[c] == ' '; c++);
			int d;
			for (d = i - 1; d > i && strXml[d] != ' '; d--);
			if (d >= c)
				current->weight += slot(d - c + 1);//增加text属性
			Stack.pop();
			treeStack.pop();
		}
		else {
			TreeNode* tmp = new TreeNode;
			tmp->id = id;
			int a;
			for (a = i + 1; a < j && strXml[a] != ' '; a++);//找到第一个空白字符
			if (a == i + 1) {
				cout << "Error Xml!!!（标签长度错误）" << endl;
				exit(1);
			}
			tmp->weight += slot(a - i - 1);//添加元素标签长度
			Stack.push(make_pair(i, a));
			//下面处理项目属性
			while (a < j) {
				int c, d, e, f;
				for (c = a; c < j && strXml[c] == ' '; c++);
				for (d = c; d < j && strXml[d] != '='; d++);
				for (e = d+1; e < j && strXml[e] == ' '; e++);
				for (f = e + 1; f < j && strXml[f] != '\"'; f++);
				if (strXml[e] != '\"') {
					cout << i << "," << j << endl;
					cout << strXml.substr(i,j-i+1) << endl;
					cout << "Error Xml!!!（属性值错误）" << endl;
					exit(1);
				}
				if (c == d || e >= f+1)
					break;
				tmp->weight += slot(d - d) + slot(f - e - 1);
				a = f + 1;
			}
			if (treeStack.empty()) {
				root = tmp;
				cout << "New Root" << endl;
			}
			else {
				TreeNode* current = treeStack.top();
				current->addChild(tmp);
			}
			treeStack.push(tmp);
			id++;
		}
		k = j + 1;
	}
	return root;
}

TreeNode * XmlParser::ParseToTree2(string strXml)
{
	TreeNode *root = nullptr;
	int n = strXml.length();
	stack<pair<int, int>> Stack;
	stack<TreeNode*> treeStack;
	for (int k = 0; k < n;) {
		int i = strXml.find_first_of('<', k);
		int j = strXml.find_first_of('>', k);
		if (i == -1 && j == -1)
			break;
		if (i >= j) {
			cout << k << "," << i << "," << j << endl;
			cout << strXml.substr(k, i - k) << endl;
			cout << strXml.substr(k, j - k) << endl;
			cout << "Error Xml(括号不匹配)!!!" << endl;
			exit(1);
		}
		if (strXml[i + 1] == '/') {
			if (Stack.empty()) {
				cout << "Error Xml!!!（标签不匹配）" << endl;
				exit(1);
			}
			TreeNode* current = treeStack.top();
			int a = Stack.top().first, b = Stack.top().second;
			int tag_len = b - a - 1;
			if (strXml.compare(a + 1, tag_len, strXml, i + 2, tag_len) != 0) {
				cout << tag_len << endl;
				cout << strXml.substr(a + 1, b - a) << endl;
				cout << strXml.substr(i, j - i + 1) << endl;
				cout << "Error Xml!!!（标签不相同）" << endl;
				exit(1);
			}
			int c;
			for (c = k; c < i && (strXml[c] == ' ' || strXml[c]=='\n'); c++);
			int d;
			for (d = i - 1; d > i && strXml[d] != ' '; d--);
			if (d >= c) {
				//current->weight += slot(d - c + 1);//增加text属性
				TreeNode* temp = new TreeNode(id, slot(d - c + 1));
				//cout << "text:" << id << endl;
				//cout << strXml.substr(c, d - c + 1) << endl;;
				current->addChild(temp);
				id++;
				
			}
				
			Stack.pop();
			treeStack.pop();
		}
		else {
			TreeNode* tmp = new TreeNode;
			tmp->id = id;
			id++;
			int a;
			for (a = i + 1; a < j && strXml[a] != ' '; a++);//找到第一个空白字符
			if (a == i + 1) {
				cout << "Error Xml!!!（标签长度错误）" << endl;
				exit(1);
			}
			tmp->weight += slot(a - i - 1);//添加元素标签长度
			Stack.push(make_pair(i, a));
			//下面处理项目属性
			while (a < j) {
				int c, d, e, f;
				for (c = a; c < j && strXml[c] == ' '; c++);
				for (d = c; d < j && strXml[d] != '='; d++);
				for (e = d + 1; e < j && strXml[e] == ' '; e++);
				for (f = e + 1; f < j && strXml[f] != '\"'; f++);
				if (strXml[e] != '\"') {
					cout << i << "," << j << endl;
					cout << strXml.substr(i, j - i + 1) << endl;
					cout << "Error Xml!!!（属性值错误）" << endl;
					exit(1);
				}
				if (c == d || e >= f + 1)
					break;
				//tmp->weight += slot(d - d) + slot(f - e - 1);
				TreeNode *temp = new TreeNode(id, slot(d - d) + slot(f - e - 1));
				id++;
				tmp->addChild(temp);
				/*cout <<"attri:"<< id << endl;*/
				a = f + 1;
			}
			if (treeStack.empty()) {
				root = tmp;
				cout << "New Root" << endl;
			}
			else {
				TreeNode* current = treeStack.top();
				current->addChild(tmp);
			}
			treeStack.push(tmp);
			
		}
		k = j + 1;
	}
	return root;
}

int XmlParser::ParseAttributes(string strXml)
{

	return 0;
}

int XmlParser::slot(int size)
{
	/*if (size == 0)
		return 1;*/
	return (size-1)/8+1;
}

XmlParser::XmlParser()
{
}

XmlParser::~XmlParser()
{
}
