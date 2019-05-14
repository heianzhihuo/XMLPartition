#include "XmlParser.h"

int XmlParser::id = 0;

XmlParser::XmlParser()
{
}

XmlParser::~XmlParser()
{
}

bool XmlParser::ParseXml(string strXml)
{
	ParseOneItem(strXml, &xmlDocument.root, &root);
	return true;
}

int XmlParser::slot(string str) {
	if (str.size() == 0)
		return 1;//����Ϊ0Ҳ����ռ��һ��slot
	return (str.size()-1) * sizeof(char) / 8+1;//����ȡ��
}
int XmlParser::slot(int size) {
	if (size == 0)
		return 1;
	return (size - 1) / 8 + 1;
}

/*����һ����Ŀ*/
int XmlParser::ParseOneItem(string strOneItemXml, CItem* pItem, TreeNode* pNode) {
	if (pItem == nullptr) return 0;
	CItem newItem;
	TreeNode newNode(id,0);
	id++;
	//�����Ŀ����
	string s = strOneItemXml;
	smatch m;
	regex regexItem("<\\w+\\b");//��������Ϊ1�ĵ��ʣ�����Ϊ�ո�
	if (regex_search(s, m, regexItem)) {
		string strItemName = m.str();
		newItem.name = strItemName.erase(0, 1);//��ȥ��ͷ���ַ�<
		newNode.weight += slot(newItem.name);
	}
	//��ã�����
	s = strOneItemXml;
	regex regexHead("<\\w+[^\\n<]*>");
	if (regex_search(s, m, regexHead)) {
		string strHead = m.str();
		smatch attributeMatch;
		regex regexAttribute("\\b\\w+=\"\\w+\"");
		while (regex_search(strHead, attributeMatch, regexAttribute)) {
			CAttribute newAttribute;
			ParseOneAttribute(attributeMatch.str(), &newAttribute);
			newItem.attributes.push_back(newAttribute);
			newNode.weight += slot(newAttribute.name) + slot(newAttribute.value);
		}
	}  
	//����Ŀ����
	s = strOneItemXml;
	int i = s.find_first_of('>');
	int j = s.find_last_of('<');
	if (j > i) {
		//s.erase(j);
		//s.erase(0, i + 1);
		//������Ϊ����Ŀ
		ParseSubItem(s.substr(i+1,j-i-1), &newItem, &newNode);
	}
	*pItem = newItem;
	*pNode = newNode;
	return 1;
}

int XmlParser::ParseOneItemNode(string strOneItemXml, TreeNode* pNode) {
	if (pNode == nullptr) return 0;
	TreeNode newNode(id, 0);
	id++;
	//�����Ŀ����
	string s = strOneItemXml;
	smatch m;
	regex regexItem("<\\w+\\b");//��������Ϊ1�ĵ��ʣ�����Ϊ�ո�
	if (regex_search(s, m, regexItem)) {
		//string strItemName = m.str();
		newNode.weight += slot(m.length()-1);
	}
	

}

int ParseXmlToTree(string strXml, TreeNode* root) {
	if (root == nullptr) return 0;
	int i, j, k, a, b, c, d,n = strXml.size();
	bool flag;
	for (k = 0; k < n;) {
		i = strXml.find_first_of('<',k);
		j = strXml.find_first_of('>',k);
		if (i >= j) {
			cout << "Error!!!" << endl;
			exit(0);
		}
		for (a = k; a < i; a++);

			
	}
	return 1;
}

/*����һ����Ŀ������Ŀ����text���ԣ���������ǩ֮�����Ϊ������Ŀ����text����*/
int XmlParser::ParseSubItem(string strOneItemXml, CItem* pItem,TreeNode *pNode) {
	if (pItem == nullptr) return 0;
	string s = strOneItemXml;
	int i = s.find_first_of('<');
	if (i!=-1) {
		while (i!=-1) {
			int j = s.find_first_of('>');
			string end_tag = s.substr(i,j-i+1).insert(1, "/");
			int k = s.find(end_tag) + end_tag.size();
			CItem newSubItem;
			TreeNode newSubNode;
			ParseOneItem(s.substr(i, k-i+1), &newSubItem, &newSubNode);
			pItem->subitems.push_back(newSubItem);
			pNode->child.push_back(newSubNode);
			s = s.erase(0, k);
			i = s.find_first_of('<');
		}
	}
	else if(s.size()>0){
		CAttribute textAttribute;
		textAttribute.name = "text";
		textAttribute.value = s;
		pItem->attributes.push_back(textAttribute);
		pNode->weight += slot(s);//���ﲻ���������Ƶĳ���
	}
}


/*����һ�����ԣ�����������Ե�slotֵ*/
int XmlParser::ParseOneAttribute(string strAttribute, CAttribute* pAttribute) {
	if (pAttribute == nullptr) return 0;
	CAttribute newAttribute;
	//��ȡ��������
	string s = strAttribute;
	smatch m;
	regex regexAttributeName("\\b\\w+=");//ƥ������һ���ַ�=
	if (regex_search(s, m, regexAttributeName)) {
		string strTempName = m.str();//ƥ����
		strTempName.erase(strTempName.end() - 1, strTempName.end());//ȥ������=
		newAttribute.name = strTempName;
	}
	s = strAttribute;
	regex regexAttributeValue("\"\\w*\"");//ƥ�����ź��ַ�
	if (regex_search(s, m, regexAttributeValue)) {
		string strTempValue = m.str();
		strTempValue.erase(strTempValue.end() - 1, strTempValue.end());//��ȥ����""
		strTempValue.erase(0, 1);//��ȥ��ͷ��"
		newAttribute.value = strTempValue;
	}
	*pAttribute = newAttribute;
	return slot(newAttribute.name)+slot(newAttribute.value);
}

void XmlParser::printOneItem(CItem item, int subLevel)
{
	string strTab;
	for (int i = 0; i < subLevel; i++) strTab += "\t";
	cout << "Level_" << subLevel << endl;
	cout << strTab << item.name << ":" << endl;
	for (auto attribute : item.attributes) {
		cout <<strTab << "attributes:" << attribute.name << ":" << attribute.value << endl;
	}
	subLevel++;
	for (auto subItem : item.subitems)
		printOneItem(subItem, subLevel);
}

void XmlParser::printXmlData(CDocument xmlDocument)
{
	printOneItem(xmlDocument.root, 0);
}


