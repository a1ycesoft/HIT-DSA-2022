#include <bits/stdc++.h>
using namespace std;
int n, m, q;

struct edge {
	int v;
	int w;
};
vector<edge> g[205]; // 用邻接表存dijkstra的图
int gg[205][205]; // 用邻接矩阵存floyd的图
int pp[205][205]; // 存floyd的路径
bool b[205][205]; // 表明邻接矩阵中两点是否相连

struct node {
	int dis, u;
	// 模板 小根堆 优先队列的使用方法
	bool operator>(const node &a) const {
		return dis > a.dis;
	}
};

void input() {
	FILE *fp = fopen("graph.txt", "r");
	fscanf(fp, "%d%d", &n, &m);
	int x, y, z;
	edge tmp;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			if (i == j)
				gg[i][j] = 0;
			else
				gg[i][j] = 0x3f3f3f3f;
		}
	for (int i = 0; i < m; i++) {
		fscanf(fp, "%d%d%d", &x, &y, &z);
		b[x][y] = 1;
		b[y][x] = 1;
		tmp.v = y;
		tmp.w = z;
		g[x].push_back(tmp);
		tmp.v = x;
		g[y].push_back(tmp);
		gg[x][y] = z;
		gg[y][x] = z;
		pp[x][y] = y;
		pp[y][x] = x;
	}
	fclose(fp);
}

void findpath(int x, int y, int p[], int d[]) {
	if (d[y] != 0x3f3f3f3f) {
		stack<int> s;
		int j = p[y];
		while (j != -1) {
			s.push(j);
			j = p[j];
		}
		cout << x << "->" << y << "距离为:" << d[y] << endl;
		cout << "路径：";
		while (!s.empty()) {
			cout << s.top() << "->";
			s.pop();
		}
		cout << y << endl;
	} else {
		cout << x << "->" << y << "不连通" << endl;
	}
}

void findpath_1(int x, int y) {
	int z = pp[x][y];
	cout << x ;
	//前驱节点需要与他直接相连
	int xx = x;
	while (z != y) {
		while (!b[xx][z]) {
			z = pp[xx][z];
		}
		pp[xx][y] = z;
		cout << "->" << z;
		xx = z;
		z = pp[z][y];
	}
	cout << "->" << y << endl;
}

void printMatrix() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			if (i == j)
				continue;
			if (gg[i][j] != 0x3f3f3f3f) {
				cout << i << "->" << j << "最短路径长度为:" << gg[i][j] << endl;
				findpath_1(i, j);
			} else {
				cout << i << "->" << j << "不连通" << endl;
			}
		}
	cout << "最短路径矩阵：" << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << pp[i][j] << " ";
		}
		cout << endl;
	}
	cout << "最短距离矩阵：" << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << gg[i][j] << " ";
		}
		cout << endl;
	}

}

void findpath_2(int x, int y, int p[], int d[]) {
	if (d[y] != 0x3f3f3f3f) {
		queue<int> s;
		int j = p[y];
		while (j != -1) {
			s.push(j);
			j = p[j];
		}
		cout << y << "->" << x << "距离为:" << d[y] << endl;
		cout << "路径：";
		cout << y;
		while (!s.empty()) {
			cout << "->" << s.front() ;
			s.pop();
		}
		cout << endl;
	} else {
		cout << x << "->" << y << "不连通" << endl;
	}
}

void dijkstra_1() {
	cout << "Dijkstra 算法，输出源点及其到其他顶点的最短路径长度和最短路径\n";
	int x;
	cout << "请输入源点：";
	cin >> x;
	int d[205];
	int p[205];
	for (int i = 1; i <= n; i++)
		p[i] = -1;
	memset(d, 63, sizeof(d)); // 经典用法 0x3f3f3f3f int最大为0x7fffffff 2*0x3f3f3f3f<0x7fffffff
	bool vis[205] = { 0 };
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
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				q.push({ d[v], v });
				p[v] = u;
			}
		}
	}
	// 源点到其他点
	for (int i = 1; i <= n; i++) {
		findpath(x, i, p, d);
	}
	cout << "---------------------" << endl;
}

void floyd() {
	cout << "Floyd-Warshall算法。计算任意两个顶点间的最短距离矩阵和最短路径矩阵，并输出任意两个顶点间的最短路径长度和最短路径\n";
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				if (i == j)
					continue;
				if (gg[i][j] > gg[i][k] + gg[k][j] && gg[i][k] != 0x3f3f3f3f && gg[k][j] != 0x3f3f3f3f) {
					gg[i][j] = gg[i][k] + gg[k][j];
					pp[i][j] = k;
				}

			}

	printMatrix();
	cout << "---------------------" << endl;
}

void dijkstra_3() {
	cout << "Dijkstra 找出图中每个顶点 v 到某个指定顶点 c 最短路径\n";
	int x;
	cout << "请输入目标点：";
	cin >> x;
	int d[205];
	int p[205];
	for (int i = 1; i <= n; i++)
		p[i] = -1;
	memset(d, 63, sizeof(d)); // 经典用法 0x3f3f3f3f int最大为0x7fffffff 2*0x3f3f3f3f<0x7fffffff
	bool vis[205] = { 0 };
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
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				q.push({ d[v], v });
				p[v] = u;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		findpath_2(x, i, p, d);
	}
	cout << "---------------------" << endl;
}

void dijkstra_4() {
	cout << "对于某对顶点 u 和 v，找出 u 到 v 的一条最短路径\n";
	int x, y;
	cout << "请输入u、v：";
	cin >> x >> y;
	int d[205];
	int p[205];
	for (int i = 1; i <= n; i++)
		p[i] = -1;
	memset(d, 63, sizeof(d)); // 经典用法 0x3f3f3f3f int最大为0x7fffffff 2*0x3f3f3f3f<0x7fffffff
	bool vis[205] = { 0 };
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
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				q.push({ d[v], v });
				p[v] = u;
			}
		}
	}
	// u,v
	findpath(x, y, p, d);
}

int main() {
	input();
	floyd();
	dijkstra_1();
	dijkstra_3();
	dijkstra_4();
	system("pause");
	return 0;
}