#include <bits/stdc++.h>
using namespace std;
int n, m;

struct node {
	int k, s;
} a[5010];

bool cmp(node x, node y) {
	if (x.s == y.s)
		return x.k < y.k;
	return x.s > y.s;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i].k >> a[i].s;
	}
	sort(a + 1, a + 1 + n, cmp);
	int x = m * 1.5;
	int cu = a[x].s;
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i].s < cu)
			break;
		cnt++;
	}
	cout << cu << " " << cnt << endl;
	for (int i = 1; i <= cnt; i++) {
		cout << a[i].k << " " << a[i].s << endl;
	}
	return 0;
}