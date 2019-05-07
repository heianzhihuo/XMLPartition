#include "Partition.h"

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

vector<vector<Partition>> FlatTreeDynamicForTreeWidth(TreeNode root,int K)
{
	int wt = root.getNodeWeight(), n = root.getChildNum();
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
			int s1 = s + root.getChild(j).getNodeWeight();
			Partition P;
			if (s1 <= K)
				P = D[s1][j - 1];
			else
				P.card = INT_MAX;
			int w = 0;
			int m = 0;
			while (m < j && m < K && w < K) {
				w = w + root.getChild(j - m).getNodeWeight();
				if (w <= K) {
					int crd = D[s][j - m - 1].card + 1;
					int rw = D[s][j - m - 1].rootweight;
					if (crd < P.card || (crd == P.card && rw < P.rootweight)) {
						P.begin = root.getChild(j - m);
						P.end = root.getChild(j);
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

void showPartition(vector<vector<Partition>> D,int rootweight)
{
	int K = D.size() - 1, n = D[0].size() - 1;
	int s = rootweight, j = n;
	cout << "Card:" << D[s][j].card << endl;
	while (s > 0 || j > 0) {
		TreeNode b = D[s][j].begin;
		TreeNode e = D[s][j].end;
		cout << "(" << b.getID() << "," << e.getID() << ")" << endl;
		pair<int, int> t = D[s][j].next;
		s = t.first;
		j = t.second;
	}
}



