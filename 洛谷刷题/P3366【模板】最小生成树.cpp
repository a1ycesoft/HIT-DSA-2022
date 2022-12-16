#include <bits/stdc++.h>
using namespace std;
int n, m;

struct edge {
	int x;
	int y;
	int w;
};
struct edge g[200010];
int a[5010];
int ans = 0;

bool cmp(edge x, edge y) {
	return x.w < y.w;
}

// 并查集写法
int ff(int x) {
	if (x != a[x]) {
		a[x] = ff(a[x]);
	}
	return a[x];
	//return a[x]==x?a[x]:a[x]=ff(a[x]);
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> g[i].x >> g[i].y >> g[i].w;
	}
	sort(g, g + m, cmp);
	for (int i = 1; i <= n; i++) {
		a[i] = i;
	}
	int cnt = 0;
	for (int k = 0; k < m; k++) {
		int x = g[k].x;
		int y = g[k].y;
		if (ff(x) != ff(y)) {
			ans += g[k].w;
			a[ff(y)] = ff(x);
			cnt++;
		}
		if (cnt == n - 1) {
			cout << ans;
			return 0;
		}
	}
	if (n == 1)
		cout << 0;
	if (cnt != n - 1)
		cout << "orz";
	return 0;
}