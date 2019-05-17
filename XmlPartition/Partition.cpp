#include "Partition.h"
#include <stack>
#include <algorithm>

Partition* FlatTreeDynamicForTreeWidth(TreeNode * root, int K)
{
	int wt = root->weight, n = root->child.size();
	int wk = K - wt + 1;
	vector<vector<Partition*>> D(wk, vector<Partition*>(n + 1));
	for (int s = 0; s < wk; s++) {
		D[s][0] = new Partition;
		D[s][0]->begin = root;
		D[s][0]->end = root;
		D[s][0]->card = 1;
		D[s][0]->rootweight = wt;
		D[s][0]->next = nullptr;
	}
	for (int j = 1; j <= n; j++) {
		for (int s = 0; s < wk; s++) {
			int s1 = s + root->child[j - 1]->weight;
			Partition *P = new Partition;
			if (s1 < wk) {
				*P = *D[s1][j - 1];
				P->rootweight += root->child[j - 1]->weight;//表示将第j个儿子节点分配给根节点
			}
			else P->card = INT_MAX;//表示没有
			int w = 0, m = 0;
			while (m < j && m < K && w < K) {
				w += root->child[j - m - 1]->weight;
				if (w <= K) {
					int crd = D[s][j - m - 1]->card + 1;
					int rw = D[s][j - m - 1]->rootweight;
					if (crd < P->card || (crd == P->card && rw < P->rootweight)) {
						P->begin = root->child[j - m - 1];
						P->end = root->child[j - 1];
						P->card = crd;
						P->rootweight = rw;
						P->next = D[s][j - m - 1];
					}
				}
				m++;
			}
			D[s][j] = P;
		}
	}
	return D[0][n];
}



/*展示FDW的结果,即FlatTree的Partition结果*/
void showPartition(Partition* p)
{
	cout << "Partition Card:" << p->card << endl;
	cout << "RootWeight:" << p->rootweight << endl;
	while (p != NULL) {
		cout << "(" << p->begin->id << "," << p->end->id << ")";
		p = p->next;
	}
	cout << endl;
}

vector<Partition*> GreedyHeightDynamicWidth(TreeNode* root, int K)
{
	vector<Partition*> result;
	stack<TreeNode*> Stack;//用栈实现后序遍历
	stack<bool> visitStack;//标记是否第1次访问
	Stack.push(root);
	visitStack.push(true);
	while (!Stack.empty()) {
		TreeNode *current = Stack.top();
		if (!current->child.empty() && visitStack.top()) {
			visitStack.pop();
			visitStack.push(false);
			for (TreeNode* c : current->child) {
				Stack.push(c);
				visitStack.push(true);
			}
		}
		else {
			int wt = current->weight, n = current->child.size();
			int wk = K - wt + 1;
			vector<vector<Partition*>> D(wk, vector<Partition*>(n + 1));
			for (int s = 0; s < wk; s++) {
				D[s][0] = new Partition;
				D[s][0]->begin = current;
				D[s][0]->end = current;
				D[s][0]->card = 1;
				D[s][0]->rootweight = wt;
				D[s][0]->next = nullptr;
			}
			for (int j = 1; j <= n; j++) {
				for (int s = 0; s < wk; s++) {
					int s1 = s + current->child[j - 1]->par->rootweight;
					Partition *P = new Partition;
					if (s1 < wk) {
						*P = *D[s1][j - 1];
						P->rootweight += current->child[j - 1]->par->rootweight;//表示将第j个儿子节点分配给根节点
					}
					else P->card = INT_MAX;//表示没有
					int w = 0, m = 0;
					while (m < j && m < K && w < K) {
						w += current->child[j - m - 1]->par->rootweight;
						if (w <= K) {
							int crd = D[s][j - m - 1]->card + 1;
							int rw = D[s][j - m - 1]->rootweight;
							if (crd < P->card || (crd == P->card && rw < P->rootweight)) {
								P->begin = current->child[j - m - 1];
								P->end = current->child[j - 1];
								P->card = crd;
								P->rootweight = rw;
								P->next = D[s][j - m - 1];
							}
						}
						m++;
					}
					D[s][j] = P;
				}
			}
			Partition *p = D[0][n];
			current->par = p;
			result.push_back(p);

			Stack.pop();
			visitStack.pop();
		}
	}
	return result;
}

/*展示GHDW的结果*/
void showPartition(vector<Partition*> P)
{
	int card = 0;
	for (Partition* p : P) {
		card += p->card - 1;
		while (p != NULL) {
			cout << "(" << p->begin->id << "," << p->end->id << ")";
			p = p->next;
		}
		cout << endl;
	}
	cout << "Partition Card : " << card + 1 << endl;
}

int getPartitionCard(TreeNode *root) {
	int card = 0;
	for (auto c : root->child)
		card += getPartitionCard(c);
	Partition *p = root->par;
	card += p->card;
	if (p->nearlyopt != nullptr)
		card -= p->nearlyopt->size();
	return card - 1;
}

int getPartitionCard(vector<Partition*> P)
{
	int card = 0;
	for (Partition* p : P) {
		card += p->card - 1;
	}
	return card+1;
}

int showPartition(TreeNode * root)
{
	//int card = 0;
	Partition *p;
	if (root->useNopt && root->nopt != nullptr) p = root->nopt;
	else p = root->par;
	cout << endl;
	while (p != nullptr) {
		cout << "(" << p->begin->id << "," << p->end->id << ")";
		if (p->nearlyopt != nullptr)
			for (auto c : *p->nearlyopt)
				c->useNopt = true;
		p = p->next;
	}
	for (auto c : root->child)
		showPartition(c);

	//Partition *p = root->par;
	//if (root->parent == nullptr || root->nopt!=nullptr) p = root->nopt;
	return 0;
}

bool compare(TreeNode * p1, TreeNode * p2)
{
	return p2->dw < p1->dw;
}

void DynamicHeightWidth(TreeNode* root, int K)
{
	//vector<Partition*> result;
	stack<TreeNode*> Stack;//用栈实现后序遍历
	stack<bool> visitStack;//标记是否第1次访问
	Stack.push(root);
	visitStack.push(true);
	while (!Stack.empty()){
		TreeNode *current = Stack.top();
		if (!current->child.empty() && visitStack.top()) {
			visitStack.pop();
			visitStack.push(false);
			for (auto c : current->child) {
				Stack.push(c);
				visitStack.push(true);
			}
		}
		else {
			int wt = current->weight, n = current->child.size();
			int wk = K - wt + 1;
			vector<vector<Partition*>> D(wk, vector<Partition*>(n + 1));
			for (int s = 0; s < wk; s++) {
				D[s][0] = new Partition;
				D[s][0]->begin = current;
				D[s][0]->end = current;
				D[s][0]->card = 1;
				D[s][0]->rootweight = wt;
				D[s][0]->next = nullptr;
			}
			//接下来是对每个这个节点的各个子节点进行划分
			for (int j = 1; j <= n; j++) {
				for (int s = 0; s < wk; s++) {
					int s1 = s + current->child[j - 1]->par->rootweight;
					Partition *P = new Partition;
					if (s1 < wk) {
						//表示将第j个儿子节点分配给根节点
						*P = *D[s1][j - 1];
						P->rootweight += current->child[j - 1]->par->rootweight;
					}
					else P->card = INT_MAX;//表示没有
					int w = 0, dw = 0, m = 0;
					while (m < j && m < K && w-dw < K) {
						w += current->child[j - m - 1]->par->rootweight;//最优解的
						dw += current->child[j - m - 1]->dw;
						if (w - dw <= K) {
							int crd = D[s][j - m - 1]->card + 1;
							int rw = D[s][j - m - 1]->rootweight;
							vector<TreeNode*> C;
							for (int _ = j - m; _ <= j; _++)
								C.push_back(current->child[_ - 1]);
							sort(C.begin(), C.end(), compare);//降序排列
							int w1 = w;
							vector<TreeNode*>* N = new vector<TreeNode*>;
							for (TreeNode* u : C) {
								if (w1 <= K)
									break;
								w1 -= u->dw;//表示子节点u采用nearly optimal
								N->push_back(u);
								crd++;
							}
							if (crd < P->card || (crd == P->card && rw < P->rootweight)) {
								P->begin = current->child[j - m - 1];
								P->end = current->child[j - 1];
								P->card = crd;
								P->rootweight = rw;
								P->next = D[s][j - m - 1];
								P->nearlyopt = N;
							}
						}
						m++;
					}
					D[s][j] = P;
				}
			}
			Partition *p = D[0][n];
			current->par = p;
			int s = K - p->rootweight + 1;
			if (0 <= s && s < wk && n>0) {
				//计算ΔW和Q(current)
				current->nopt = D[s][n];
				current->dw = current->par->rootweight - current->nopt->rootweight;
				//p->dw = p->rootweight - D[s][n]->rootweight;
			}
			//result.push_back(p);
			Stack.pop();
			visitStack.pop();
		}
	}
	//showPartition(result);
	//return result;
}

Partition::Partition()
{
}

Partition::~Partition()
{
}
