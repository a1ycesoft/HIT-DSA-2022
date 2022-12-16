#include <bits/stdc++.h>
using namespace std;
int n;

struct node {
	int x, y;
} g[5010];
double f[5005];

bool vis[5005] = {0};

struct e {
	int v;
	double w;
	bool operator > (const e &a)const {
		return w > a.w;
	}

};

double len(int x, int y) {
	// ºÃ¿Ó°¡
	double u = (double)(g[x].x - g[y].x) * (g[x].x - g[y].x) + (double)(g[x].y - g[y].y) * (g[x].y - g[y].y);
	return sqrt(u);
}
priority_queue<e, vector<e>, greater<e>> q;
double ans = 0;

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> g[i].x >> g[i].y;
	for (int i = 1; i <= n; i++)
		f[i] = 1e12 * 1.0;
	f[1] = 0;
	q.push({ 1, 0 });
	while (!q.empty()) {
		int cur = q.top().v;
		double ww = q.top().w;
		q.pop();
		if (vis[cur])
			continue;
		vis[cur] = 1;
		ans += ww;
		for (int i = 1; i <= n; i++) {
			if (vis[i])
				continue;
			double x = len(cur, i);
			if (f[i] > x) {
				f[i] = x;
				q.push({ i, x });
			}
		}
	}
	printf("%.2lf", ans);
}