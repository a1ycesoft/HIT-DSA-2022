#include <bits/stdc++.h>
using namespace std;
int n, m, q;
int ti[205];

// dijkstra，但正解是floyd
struct edge {
	int v;
	int w;
};
vector<edge> g[205];

struct node {
	int dis, u;
	// 模板 小根堆
	bool operator>(const node &a) const {
		return dis > a.dis;
	}
};

int f(int x, int y, int t) {
	if (ti[x] > t || ti[y] > t)
		return -1;
	int d[205];
	memset(d, 63, sizeof(d)); // 经典用法 0x3f3f3f3f int最大为0x7fffffff 2*0x3f3f3f3f<0x7fffffff
	bool vis[205] = { 0 };
	bool b[205] = {0};
	for (int i = 0; i < n; i++) {
		if (ti[i] <= t)
			b[i] = 1;
	}
	priority_queue<node, vector<node>, greater<node>> q;
	d[x] = 0;
	q.push({ 0, x });
	while (!q.empty()) {
		int u = q.top().u;
		q.pop();
		if (vis[u])
			continue;
		vis[u] = 1;
		for (auto ed : g[u]) {
			int v = ed.v, w = ed.w;
			if (d[v] > d[u] + w && b[v]) {
				d[v] = d[u] + w;
				q.push({ d[v], v });
			}
		}
	}
	if (d[y] == 0x3f3f3f3f) {
		return -1;
	} else
		return d[y];
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		scanf("%d", &ti[i]);
	}
	int x, y, z;
	edge tmp;
	for (int i = 0; i < m; i++) {
		cin >> x >> y >> z;
		tmp.v = y;
		tmp.w = z;
		g[x].push_back(tmp);
		tmp.v = x;
		g[y].push_back(tmp);
	}
	cin >> q;
	int t;
	for (int i = 0; i < q; i++) {
		scanf("%d%d%d", &x, &y, &t);
		printf("%d\n", f(x, y, t));
	}
	return 0;
}