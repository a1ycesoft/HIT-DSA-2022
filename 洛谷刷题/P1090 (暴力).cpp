#include <iostream>
#include <algorithm>
using namespace std;
int n;

struct node {
	int data;
	int next;
} a[10010];

bool cmp(node x, node y) {
	return x.data < y.data;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i].data;
	}
	if (n == 1) {
		cout << a[0].data;
		return 0;
	}
	sort(a, a + n, cmp);
	for (int i = 0; i < n - 1; i++) {
		a[i].next = i + 1;
	}
	a[n - 1].next = -1;
	int ans = 0;
	int h1 = 0;
	for (int i = 0; i < n - 1; i++) {
		int h2 = a[h1].next;
		int x = a[h1].data + a[h2].data;
		ans += x;
		a[h2].data = x;
		int j = a[h2].next;
		int pre = j;
		while (j != -1) {
			if (a[j].data > x) {
				break;
			}
			pre = j;
			j = a[j].next;
		}
		if (j == a[h2].next) {
			h1 = h2;
		} else {
			h1 = a[h2].next;
			a[h2].next = a[pre].next;
			a[pre].next = h2;
		}
	}
	cout << ans;
	return 0;
}