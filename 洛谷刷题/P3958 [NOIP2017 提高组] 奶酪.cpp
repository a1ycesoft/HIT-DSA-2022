#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
long long t;

int main() {
	cin >> t;
	long long n, h, r;
	while (t--) {
		cin >> n >> h >> r;
		long long x[1010][3];
		vector<long long> g[1010];
		bool b[1010] = {0};
		for (long long i = 1; i <= n; i++) {
			cin >> x[i][0] >> x[i][1] >> x[i][2];
			if (x[i][2] <= r) {
				g[0].push_back(i);
			}
			if (x[i][2] + r >= h) {
				g[i].push_back(n + 1);
			}
		}
		long long r2 = 4 * r * r;
		for (long long i = 1; i <= n; i++) {
			for (long long j = i + 1; j <= n; j++) {
				long long l = (x[j][0] - x[i][0]) * (x[j][0] - x[i][0]) + (x[j][1] - x[i][1]) * (x[j][1] - x[i][1]) +
				              (x[j][2] - x[i][2]) * (x[j][2] - x[i][2]);
				if (l <= r2) {

					g[i].push_back(j);
					g[j].push_back(i);
				}
			}
		}
		queue<long long> q;
		q.push(0);
		b[0] = 1;
		while (!q.empty()) {
			long long t = q.front();
			q.pop();
			long long len = (long long)g[t].size();
			for (long long i = 0; i < len; i++) {
				long long cur = g[t][i];

				if (!b[cur]) {
					b[cur] = 1;
					q.push(cur);
				}
			}
		}
		if (b[n + 1]) {
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}
	}
	return 0;
}