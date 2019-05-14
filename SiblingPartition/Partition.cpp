#include "Partition.h"
#include <stack>

Partition::Partition()
{
	card = 0;
	rootweight = 0;
	begin = NULL;
	end = NULL;
	//next = make_pair(0, 0);
	next = NULL;
}

Partition::~Partition()
{
}
/*FlatTree Dynamic programing for tree width
 FDW��ʵ��
 ��������α�����һ������
 
 */
Partition* FlatTreeDynamicForTreeWidth(TreeNode root,int K)
{
	int wt = root.weight, n = root.child.size();
	int m = K - wt + 1,s,j;
	vector<vector<Partition>> D(K+1,vector<Partition>(n+1));
	for (s = wt; s<=K; s++) {
		D[s][0].begin = root;
		D[s][0].end = root;
		D[s][0].card = 1;
		D[s][0].rootweight = wt;
		//D[s][0].next = make_pair(0, 0);
		D[s][0].next = NULL;
	}
	for (j = 1; j <= n; j++) {
		for (s = wt; s <= K; s++) {
			int s1 = s + root.child[j - 1].weight;
			Partition P;
			if (s1 <= K) {
				P = D[s1][j - 1];
				P.rootweight+= root.child[j - 1].weight;
			}	
			else
				P.card = INT_MAX;
			int w = 0;
			int m = 0;
			while (m < j && m < K && w < K) {
				w = w + root.child[j - m-1].weight;
				if (w <= K) {
					int crd = D[s][j - m - 1].card + 1;
					int rw = D[s][j - m - 1].rootweight;
					if (crd < P.card || (crd == P.card && rw < P.rootweight)) {
						P.begin = root.child[j - m-1];
						P.end = root.child[j-1];
						P.card = crd;
						P.rootweight = rw;
						P.next = &D[s][j - m - 1];
						//P.next = make_pair(s, j - m - 1);
					}
				}
				m++;
			}
			D[s][j] = P;
		}
	}
	Partition* res = new Partition;
	*res = D[wt][n];
	D.clear();
	return res;
	//return D;
}
/*չʾFDW�Ľ��*/
void showFDWPartition(Partition* p)
{
	cout << "Partition Card:" << p->card << endl;
	cout << "RootWeight:" << p->rootweight << endl;
	while (p!=NULL) {
		cout << "(" << p->begin.id << "," << p->end.id << ")";
		p = p->next;
	}
	cout << endl;
}
/*GHDW�㷨��ʵ�֣�Greedy-Height/Dynamic-Width*/
vector<vector<vector<Partition>>> GHDW;
vector<Partition*> GreedyHeightDynamicWidth(TreeNode root, int K)
{
	vector<Partition*> result;
	stack<TreeNode *> Stack;//��ջʵ�ֺ������
	stack<bool> Stack1;//�������Ƿ�ڶ��η���
	TreeNode* current;
	Stack.push(&root);
	Stack1.push(true);
	while (!Stack.empty())
	{
		current = Stack.top();
		if (current->child.size() != 0 && Stack1.top()) {
			Stack1.pop();
			Stack1.push(false);
			for (int i = 0; i < current->child.size(); i++) {
				Stack.push(&current->child[i]);
				Stack1.push(true);
			}
		}
		else {
			Partition* p = FlatTreeDynamicForTreeWidth(*current, K);
			current->weight = p->rootweight;//�����ڻ����и��ڵ��tree weight
			result.push_back(p);
			Stack.pop();
			Stack1.pop();
		}
	}
	return result;
}
TreeNode GreedyHeigtDW(TreeNode root, int K) {
	
	return TreeNode(1, 2);
}
/*���GHDW�Ļ�����Ŀ*/
int getGHDWPartitionCard(vector<Partition*> P) {
	int card = 0;
	for (Partition* p : P) {
		card += p->card - 1;
	}
	return card+1;
}
/*չʾGHDW�Ľ��*/
void showGHDWPartition(vector<Partition*> P)
{
	int card = 0;
	for (Partition* p : P) {
		card += p->card - 1;
		while (p != NULL) {
			cout << "(" << p->begin.id << "," << p->end.id << ")";
			p = p->next;
		}
		cout << endl;
	}
	cout << "Partition Card : "<< card + 1 << endl;
}

vector<Partition*> DynamicHeightWidth(TreeNode root, int K) {
	vector<Partition*> result;
	stack<TreeNode*> Stack;//��ջʵ�ֺ������
	stack<bool> Stack1;
	TreeNode* current;
	Stack.push(&root);
	Stack1.push(true);
	while (!Stack.empty())
	{
		current = Stack.top();
		if (current->child.size() != 0 && Stack1.top()) {
			Stack1.pop();
			Stack1.push(false);
			for (int i = 0; i < current->child.size(); i++) {
				Stack.push(&current->child[i]);
				Stack1.push(true);
			}
		}
		else {

			Partition* p = FlatTreeDynamicForTreeWidth(*current, K);
			
			current->weight = p->rootweight;
			result.push_back(p);
			Stack.pop();
			Stack1.pop();
		}
	}
	return result;
}





