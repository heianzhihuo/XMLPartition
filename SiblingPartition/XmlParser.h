#pragma once
#include <iostream>
#include <vector>
#include <regex>
#include "TreeNode.h"

using namespace std;
// Ù–‘
struct CAttribute
{
	string name;
	string value;
};
//œÓ,element,
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

	CDocument xmlDocument;
	TreeNode root;
	static int id;
};

