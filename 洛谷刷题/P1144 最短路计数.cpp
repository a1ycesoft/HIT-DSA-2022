#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
int n, m;
vector<int> g[1000001];
queue<int> q;
bool b[1000001];
int a[1000001];
int ans[1000001];

int main() {
	cin >> n >> m;
	int x, y;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	q.push(1);
	b[1] = 1;
	a[1] = 0;
	ans[1] = 1;
	while (!q.empty()) {
		int t = q.front();
		q.pop();
		int len = (int)g[t].size();
		for (int i = 0; i < len; i++) {
			int k = g[t][i];
			if (!b[k]) {
				a[k] = a[t] + 1;
				b[k] = 1;
				ans[k] = ans[t];
				q.push(k);
			} else {
				if (a[k] == a[t] + 1) {
					ans[k] += ans[t];
					ans[k] %= 100003;
				}
			}
		}
	}
	for (int i = 1; i <= n; i++)
		cout << ans[i] << endl;
	return 0;
}