#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long ll;
priority_queue<ll, vector<ll>, greater<ll>> q;
ll x[10000][3];

int main() {
	ll n, m;
	ll cnt = 0;
	cin >> n >> m;
	for (ll i = 0; i < n; i++)
		for (ll j = 0; j < 3; j++)
			cin >> x[i][j];
	for (ll i = 1; i <= m; i++) {
		ll minx = x[0][0] * i * i + x[0][1] * i + x[0][2];
		q.push(minx);
		for (ll k = 1; k < n; k++) {
			ll s = i * i * x[k][0] + i * x[k][1] + x[k][2];
			minx = minx < s ? minx : s;
			q.push(s);
		}
		while (!q.empty()) {
			if (cnt == m) {
				return 0;
			}
			ll x = q.top();
			if (x < minx) {
				cout << x << " ";
				cnt++;
				q.pop();
			} else {
				break;
			}
		}
	}
	while (cnt < m) {
		cout << q.top() << " ";
		q.pop();
		cnt++;
	}
	return 0;
}