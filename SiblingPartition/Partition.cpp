#include "Partition.h"
#include <stack>

Partition::Partition()
{
	card = 0;
	rootweight = 0;
	begin = NULL;
	end = NULL;
	next = make_pair(0, 0);
}

Partition::~Partition()
{
}
/*FlatTree Dynamic programing for tree width
 FDW的实现
 发现论文伪代码的一个问题
 
 */
vector<vector<Partition>> FlatTreeDynamicForTreeWidth(TreeNode root,int K)
{
	int wt = root.weight, n = root.child.size();
	int m = K - wt + 1,s,j;
	vector<vector<Partition>> D(K+1,vector<Partition>(n+1));
	for (s = wt; s<=K; s++) {
		D[s][0].begin = root;
		D[s][0].end = root;
		D[s][0].card = 1;
		D[s][0].rootweight = wt;
		D[s][0].next = make_pair(0, 0);
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
						P.next = make_pair(s, j - m - 1);
					}
				}
				m++;
			}
			D[s][j] = P;
		}
	}
	return D;
}
/*展示FDW的结果*/
void showFDWPartition(vector<vector<Partition>> D,int rootweight)
{
	int K = D.size() - 1, n = D[0].size() - 1;
	int s = rootweight, j = n;
	cout << "Card:" << D[s][j].card << endl;
	cout << "RootWeight:" << D[s][j].rootweight << endl;
	while (s > 0 || j > 0) {
		TreeNode b = D[s][j].begin;
		TreeNode e = D[s][j].end;
		cout << "(" << b.id << "," << e.id << ")" << endl;
		pair<int, int> t = D[s][j].next;
		s = t.first;
		j = t.second;
	}
}
/*GHDW算法的实现，Greedy-Height/Dynamic-Width*/
vector<vector<vector<Partition>>> GHDW;
vector<vector<vector<Partition>>> GreedyHeightDynamicWidth(TreeNode root, int K)
{
	vector<vector<vector<Partition>>> result;
	stack<TreeNode *> Stack;
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
			vector<vector<Partition>> p = FlatTreeDynamicForTreeWidth(*current, K);
			result.push_back(p);
			current->weight = p[current->weight][current->child.size()].rootweight;
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
int getGHDWPartitionNum(vector<vector<vector<Partition>>> D, TreeNode root) {
	stack<TreeNode*> Stack;
	stack<bool> Stack1;
	TreeNode* current;
	Stack.push(&root);
	Stack1.push(true);
	int i=0,partition_num = 0;
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
			vector<vector<Partition>> p = D[i];
			partition_num += (p[current->weight][current->child.size()].card) - 1;
			i++;
			Stack.pop();
			Stack1.pop();
		}
	}
	return partition_num+1;
}
/*展示GHDW的结果*/
void showGHDWPartition(vector<vector<vector<Partition>>> D, TreeNode root)
{
	for (auto d : D) {
		for (auto x : d) {
			for (Partition p : x) {
				cout << p.begin.id << "," << p.end.id << "\t" << p.next.first << "," << p.next.second << "\t\t";
			}
			cout << endl;
		}
		cout << endl;
	}
}





