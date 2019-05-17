#pragma once
#include <iostream>
#include <vector>
#include "TreeNode.h"

//属性
struct CAttribute
{
	string name;
	string value;
};
//元素，项目,element,
struct CItem
{
	string name;//element tag
	vector<CItem> subitems;//sub element
	vector<CAttribute> attributes;//element attri
};
struct CDocument
{
	CItem root;
};

class XmlParser {
public:
	XmlParser();
	~XmlParser();

	bool ParseXml(string strXml);


	int ParseOneItem(string strOneItemXml, CItem* pItem, TreeNode* pNode);
	int ParseSubItem(string strOneItemXml, CItem* pItem, TreeNode* pNode);
	int ParseOneAttribute(string strAttribute, CAttribute* pAttribute);


	void printOneItem(CItem item, int subLevel);
	void printXmlData(CDocument xmlDocument);

	int ParseOneItemNode(string strOneItemXml, TreeNode* pNode);
	int ParseSubItemNode(string strOneItemXml, TreeNode* pNode);
	int ParseOneAttribute(string strAttribute);

	TreeNode* ParseToTree(string strXml);

	TreeNode* ParseToTree2(string strXml);

	int ParseAttributes(string strXml);

	int ParseToTree(string strXml, TreeNode* root);



	int slot(int size);

	CDocument xmlDocument;
	TreeNode root;
	int id = 0;
};