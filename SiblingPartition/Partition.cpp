#include "Partition.h"
#include <stack>
#include <algorithm>

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
 FDW的实现
 发现论文伪代码的一个问题
 
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
				cout << s1 << "," << P.rootweight << endl;
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
/*展示FDW的结果*/
void showPartition(Partition* p)
{
	cout << "Partition Card:" << p->card << endl;
	cout << "RootWeight:" << p->rootweight << endl;
	while (p!=NULL) {
		cout << "(" << p->begin.id << "," << p->end.id << ")";
		p = p->next;
	}
	cout << endl;
}
/*GHDW算法的实现，Greedy-Height/Dynamic-Width*/
vector<vector<vector<Partition>>> GHDW;
vector<Partition*> GreedyHeightDynamicWidth(TreeNode root, int K)
{
	vector<Partition*> result;
	stack<TreeNode *> Stack;//用栈实现后序遍历
	stack<bool> Stack1;//这个标记是否第二次访问
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
			current->weight = p->rootweight;//更新在划分中根节点的tree weight
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
/*获得GHDW的划分数目*/
int getGHDWPartitionCard(vector<Partition*> P) {
	int card = 0;
	for (Partition* p : P) {
		card += p->card - 1;
	}
	return card+1;
}
/*展示GHDW的结果*/
void showPartition(vector<Partition*> P)
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

int compare(Partition p1, Partition p2) {
	return p1.dw - p2.dw;
}

vector<Partition*> DynamicHeightWidth(TreeNode root, int K) {
	vector<Partition*> result;
	stack<TreeNode*> Stack;//用栈实现后序遍历
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
			int wt = current->weight, n = current->child.size();
			int wtm = K - wt + 1;
			vector<vector<Partition>>D(K + 1, vector<Partition>(n + 1));
			for (int s = wt; s <= K; s++) {
				D[s][0].begin = *current;
				D[s][0].end = *current;
				D[s][0].card = 1;
				D[s][0].rootweight = s;
				D[s][0].next = NULL;
				D[s][0].dw = 0;
			}
			for (int j = 1; j < n; j++) {
				for (int s = wt; s <= K; s++) {
					int s1 = s + result[current->child[j - 1].id]->rootweight;
					Partition P;
					if (s1 <= K) {
						P = D[s1][j - 1];
						P.rootweight += current->child[j - 1].weight;
					}
					else {
						P.card = INT_MAX;
						P.dw = 0;
					}
						
					int w = 0, m = 0, dw = 0;
					while (m < j && m < K && w - dw < K) {
						w += current->child[j - m - 1].weight;
						dw += result[current->child[j - m - 1].id]->dw;
						if (w - dw <= K) {
							int crd = D[s][j - m - 1].card + 1;
							int rw = D[s][j - m - 1].rootweight;
							vector<Partition> C;
							for (int a = j - m; a <= j; a++)
								C.push_back(current->child[a - 1]);
							sort(C.begin(), C.end(), compare);
							int w1 = w;
							int in = 0;
							while (w1>K){
								TreeNode u;
								if (C[in].card == 1)
									u = C[in].begin;
								else
									u = *(C[in].begin.parent);
								w1 -= result[u.id]->dw;
							}
							if (crd < P.card || (crd == P.card && rw < P.rootweight)) {
								P.begin = current->child[j - m - 1];
								P.end = current->child[j - 1];
								P.card = crd;
								P.rootweight = rw;
								P.next = &D[s][j - m - 1];
							}
						}
						m++;
					}
					D[s][j] = P;
				}
			}
			current->weight = D[wt][n].rootweight;
			current->id = result.size();
			result.push_back(&D[wt][n]);
			Stack.pop();
			Stack1.pop();
		}
	}
	return result;
}





