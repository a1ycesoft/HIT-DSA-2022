#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
priority_queue<int, vector<int>, greater<int> >q;

int main() {
	int n;
	cin >> n;
	int x;
	for (int i = 0; i < n; i++) {
		cin >> x;
		q.push(x);
	}
	if (n == 1) {
		cout << q.top();
		return 0;
	}
	int ans = 0;
	while ((int)q.size() >= 2) {
		int x1 = q.top();
		q.pop();
		int x2 = q.top();
		q.pop();
		ans += x1 + x2;
		q.push(x1 + x2);
	}
	cout << ans;
	return 0;
}