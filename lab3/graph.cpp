#include <bits/stdc++.h>
using namespace std;
int n, m, q;

struct edge {
	int v;
	int w;
};
vector<edge> g[205]; // ���ڽӱ��dijkstra��ͼ
int gg[205][205]; // ���ڽӾ����floyd��ͼ
int pp[205][205]; // ��floyd��·��
bool b[205][205]; // �����ڽӾ����������Ƿ�����

struct node {
	int dis, u;
	// ģ�� С���� ���ȶ��е�ʹ�÷���
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
		cout << x << "->" << y << "����Ϊ:" << d[y] << endl;
		cout << "·����";
		while (!s.empty()) {
			cout << s.top() << "->";
			s.pop();
		}
		cout << y << endl;
	} else {
		cout << x << "->" << y << "����ͨ" << endl;
	}
}

void findpath_1(int x, int y) {
	int z = pp[x][y];
	cout << x ;
	//ǰ���ڵ���Ҫ����ֱ������
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
				cout << i << "->" << j << "���·������Ϊ:" << gg[i][j] << endl;
				findpath_1(i, j);
			} else {
				cout << i << "->" << j << "����ͨ" << endl;
			}
		}
	cout << "���·������" << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << pp[i][j] << " ";
		}
		cout << endl;
	}
	cout << "��̾������" << endl;
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
		cout << y << "->" << x << "����Ϊ:" << d[y] << endl;
		cout << "·����";
		cout << y;
		while (!s.empty()) {
			cout << "->" << s.front() ;
			s.pop();
		}
		cout << endl;
	} else {
		cout << x << "->" << y << "����ͨ" << endl;
	}
}

void dijkstra_1() {
	cout << "Dijkstra �㷨�����Դ�㼰�䵽������������·�����Ⱥ����·��\n";
	int x;
	cout << "������Դ�㣺";
	cin >> x;
	int d[205];
	int p[205];
	for (int i = 1; i <= n; i++)
		p[i] = -1;
	memset(d, 63, sizeof(d)); // �����÷� 0x3f3f3f3f int���Ϊ0x7fffffff 2*0x3f3f3f3f<0x7fffffff
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
	// Դ�㵽������
	for (int i = 1; i <= n; i++) {
		findpath(x, i, p, d);
	}
	cout << "---------------------" << endl;
}

void floyd() {
	cout << "Floyd-Warshall�㷨����������������������̾����������·�����󣬲���������������������·�����Ⱥ����·��\n";
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
	cout << "Dijkstra �ҳ�ͼ��ÿ������ v ��ĳ��ָ������ c ���·��\n";
	int x;
	cout << "������Ŀ��㣺";
	cin >> x;
	int d[205];
	int p[205];
	for (int i = 1; i <= n; i++)
		p[i] = -1;
	memset(d, 63, sizeof(d)); // �����÷� 0x3f3f3f3f int���Ϊ0x7fffffff 2*0x3f3f3f3f<0x7fffffff
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
	cout << "����ĳ�Զ��� u �� v���ҳ� u �� v ��һ�����·��\n";
	int x, y;
	cout << "������u��v��";
	cin >> x >> y;
	int d[205];
	int p[205];
	for (int i = 1; i <= n; i++)
		p[i] = -1;
	memset(d, 63, sizeof(d)); // �����÷� 0x3f3f3f3f int���Ϊ0x7fffffff 2*0x3f3f3f3f<0x7fffffff
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