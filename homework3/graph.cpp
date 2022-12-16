#include <bits/stdc++.h>
using namespace std;

typedef struct {
	bool e[100][100];
	int n, t;
} MTGraph;

typedef struct {
	vector<int> e[100];
	int n, t;
} AdjGraph;

typedef struct {
	vector<int> child[100];
} tree;

MTGraph MTGraph_store() {
	MTGraph g;
	int x, y;
	cin >> g.n >> g.t;
	memset(g.e, 0, sizeof(g.e));
	for (int i = 0; i < g.t; i++) {
		cin >> x >> y;
		g.e[x][y] = 1;
	}
	return g;
}

AdjGraph MT_to_Adj(MTGraph g) {
	AdjGraph gg;
	int n = g.n;
	int t = g.t;
	gg.n = n;
	gg.t = t;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			if (g.e[i][j]) {
				gg.e[i].push_back(j);
			}
		}
	return gg;
}

void MT_DFS_point(int x, bool b[], MTGraph g, queue<int> &q, tree &t) {
	if (b[x])
		return;
	q.push(x);
	b[x] = 1;
	for (int i = 1; i < 100; i++) {
		if (g.e[x][i] && !b[i]) {
			t.child[x].push_back(i);
			MT_DFS_point(i, b, g, q, t);

		}
	}

}

void MT_DFS(MTGraph g) {
	int n = g.n;
	bool b[100] = { 0 };
	int num[100] = { 0 };
	int cnt = 1;
	queue<int> q;
	tree t;
	for (int i = 1; i <= n; i++) {
		MT_DFS_point(i, b, g, q, t);
	}
	cout << "深度优先序列：";
	while (!q.empty()) {
		cout << q.front() << " ";
		num[cnt++] = q.front();
		q.pop();
	}
	cout << endl;
	cout << "深度优先编号：" << endl;
	for (int i = 1; i < cnt; i++) {
		cout << num[i] << ":" << i << endl;
	}
	cout << "深度优先森林：" << endl;
	for (int i = 1; i <= n; i++) {
		cout << i << "的后代:";
		int len = t.child[i].size();
		if (len > 0) {

			for (int j = 0; j < len; j++) {
				cout << t.child[i][j] << " ";
			}
			cout << endl;
		} else {
			cout << "无" << endl;
		}
	}
}

void MT_DFS_point_feidigui(int x, bool b[], MTGraph g) {
	if (b[x])
		return;
	stack<int> s;
	s.push(x);
	while (!s.empty()) {
		int t = s.top();
		if (!b[t])
			cout << t << " ";
		b[t] = 1;
		int f = 0;
		for (int i = 1; i < 100; i++) {
			if (g.e[t][i] && !b[i]) {
				f = 1;
				s.push(i);
				break;
			}
		}
		if (f == 0)
			s.pop();
	}
}

void MT_DFS_feidigui(MTGraph g) {
	int n = g.n;
	bool b[100] = { 0 };
	cout << "（非递归）优先深度序列为：";
	for (int i = 1; i <= n; i++) {
		MT_DFS_point_feidigui(i, b, g);
	}
	cout << endl;
}

void MT_BFS_point(int x, bool b[], MTGraph g, queue<int> &qq, tree &tre) {
	if (b[x])
		return;
	queue<int> q;
	q.push(x);
	while (!q.empty()) {
		int t = q.front();
		q.pop();
		qq.push(t);

		for (int i = 1; i < 100; i++) {
			if (g.e[t][i] && !b[i]) {
				tre.child[t].push_back(i);
				q.push(i);
				b[i] = 1;
			}
		}
	}
}

void MT_BFS(MTGraph g) {
	int n = g.n;
	bool b[100] = { 0 };
	int num[100] = { 0 };
	int cnt = 1;
	queue<int> qq;
	tree tre;
	for (int i = 1; i <= n; i++) {
		MT_BFS_point(i, b, g, qq, tre);
	}
	cout << "广度优先序列：" << endl;
	while (!qq.empty()) {
		cout << qq.front() << " ";
		num[cnt++] = qq.front();
		qq.pop();
	}
	cout << endl;
	cout << "广度优先编号：" << endl;
	for (int i = 1; i < cnt; i++) {
		cout << num[i] << ":" << i << endl;
	}
	cout << "广度优先森林：" << endl;
	for (int i = 1; i <= n; i++) {
		cout << i << "的后代:";
		int len = tre.child[i].size();
		if (len > 0) {

			for (int j = 0; j < len; j++) {
				cout << tre.child[i][j] << " ";
			}
			cout << endl;
		} else {
			cout << "无" << endl;
		}
	}
}

AdjGraph AdjGraph_store() {
	AdjGraph g;
	int x, y;
	cin >> g.n >> g.t;
	for (int i = 0; i < g.t; i++) {
		cin >> x >> y;
		g.e[x].push_back(y);
	}
	return g;
}

MTGraph Adj_to_MT(AdjGraph g) {
	MTGraph gg;
	int n = g.n;
	int t = g.t;
	gg.n = n;
	gg.t = t;
	for (int i = 1; i <= n; i++) {
		int len = (int)g.e[i].size();
		for (int j = 0; j < len; j++) {
			gg.e[i][g.e[i][j]] = 1;
		}
	}
	return gg;
}

void Adj_DFS_point(int x, bool b[], AdjGraph g, queue<int> &q, tree &t) {
	if (b[x])
		return;
	q.push(x);
	b[x] = 1;
	int len = (int)g.e[x].size();
	for (int i = 0; i < len; i++) {
		int tt = g.e[x][i];
		if (!b[tt]) {
			t.child[x].push_back(tt);
			Adj_DFS_point(tt, b, g, q, t);
		}
	}
}

void Adj_DFS(AdjGraph g) {
	int n = g.n;
	bool b[100] = { 0 };
	int num[100] = { 0 };
	int cnt = 1;
	queue<int> q;
	tree t;
	for (int i = 1; i <= n; i++) {
		Adj_DFS_point(i, b, g, q, t);
	}
	cout << "深度优先序列：";
	while (!q.empty()) {
		cout << q.front() << " ";
		num[cnt++] = q.front();
		q.pop();
	}
	cout << endl;
	cout << "深度优先编号：" << endl;
	for (int i = 1; i < cnt; i++) {
		cout << num[i] << ":" << i << endl;
	}
	cout << "深度优先森林：" << endl;
	for (int i = 1; i <= n; i++) {
		cout << i << "的后代:";
		int len = t.child[i].size();
		if (len > 0) {

			for (int j = 0; j < len; j++) {
				cout << t.child[i][j] << " ";
			}
			cout << endl;
		} else {
			cout << "无" << endl;
		}
	}
}

void Adj_DFS_point_feidigui(int x, bool b[], AdjGraph g) {
	if (b[x])
		return;
	stack<int> s;
	s.push(x);
	while (!s.empty()) {
		int t = s.top();
		if (!b[t])
			cout << t << " ";
		b[t] = 1;
		int f = 0;
		int len = (int)g.e[t].size();
		for (int i = 0; i < len; i++) {
			int ii = g.e[t][i];
			if (!b[ii]) {
				f = 1;
				s.push(ii);
				break;
			}
		}
		if (f == 0)
			s.pop();
	}
}

void Adj_DFS_feidigui(AdjGraph g) {
	int n = g.n;
	bool b[100] = { 0 };
	cout << "（非递归）优先深度序列为：";
	for (int i = 1; i <= n; i++) {
		Adj_DFS_point_feidigui(i, b, g);
	}
	cout << endl;
}

void Adj_BFS_point(int x, bool b[], AdjGraph g, queue<int> &qq, tree &tre) {
	if (b[x])
		return;
	queue<int> q;
	q.push(x);
	while (!q.empty()) {
		int t = q.front();
		q.pop();
		qq.push(t);

		int len = (int)g.e[t].size();
		for (int i = 0; i < len; i++) {
			int tt = g.e[t][i];
			if (!b[tt]) {
				tre.child[t].push_back(tt);
				q.push(tt);
				b[tt] = 1;
			}
		}
	}
}

void Adj_BFS(AdjGraph g) {
	int n = g.n;
	bool b[100] = {0};
	int num[100] = { 0 };
	int cnt = 1;
	queue<int> qq;
	tree tre;
	for (int i = 1; i <= n; i++) {
		Adj_BFS_point(i, b, g, qq, tre);
	}
	cout << "广度优先序列：" << endl;
	while (!qq.empty()) {
		cout << qq.front() << " ";
		num[cnt++] = qq.front();
		qq.pop();
	}
	cout << endl;
	cout << "广度优先编号：" << endl;
	for (int i = 1; i < cnt; i++) {
		cout << num[i] << ":" << i << endl;
	}
	cout << "广度优先森林：" << endl;
	for (int i = 1; i <= n; i++) {
		cout << i << "的后代:";
		int len = tre.child[i].size();
		if (len > 0) {

			for (int j = 0; j < len; j++) {
				cout << tre.child[i][j] << " ";
			}
			cout << endl;
		} else {
			cout << "无" << endl;
		}
	}
}

void Adj_BFS_degree(int x, bool b[], AdjGraph g, int a1[], int a2[]) {
	if (b[x])
		return;
	queue<int> q;
	q.push(x);
	while (!q.empty()) {
		int t = q.front();
		q.pop();
		b[t] = 1;
		int len = (int)g.e[t].size();
		a1[t] = len;
		for (int i = 0; i < len; i++) {
			int tt = g.e[t][i];
			a2[tt] ++;
			if (!b[tt]) {
				q.push(tt);
			}
		}
	}
}

void Adj_degree(AdjGraph g) {
	int n = g.n;
	int a1[100] = { 0 };
	int a2[100] = { 0 };
	bool b[100] = { 0 };
	for (int i = 1; i <= n; i++) {
		Adj_BFS_degree(i, b, g, a1, a2);
	}
	for (int i = 1; i <= n; i++) {
		cout << i << endl;
		cout << "出度:" << a1[i] << endl;
		cout << "入度:" << a2[i] << endl;
		cout << "度:" << a1[i] + a2[i] << endl;
	}
}

int main() {
	MTGraph g = MTGraph_store();
	MT_DFS_feidigui(g);
	MT_DFS(g);
	MT_BFS(g);
	cout << "-----转换-----\n";
	AdjGraph gg = MT_to_Adj(g);
	Adj_DFS_feidigui(gg);
	Adj_DFS(gg);
	Adj_BFS(gg);
	Adj_degree(gg);
	return 0;
}