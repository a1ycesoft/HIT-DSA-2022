#include <iostream>
#include <deque>
#include <algorithm>
#include <stdio.h>
using namespace std;

int n, m;
int a[2000001];
struct node {
	int val;
	int pos;
};
deque<node> q;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	printf("0\n");
	for (int i = 0; i < n - 1; i++) {
		while (!q.empty()) {
			int t = q.back().val;
			if (t > a[i]) {
				q.pop_back();
			} else {
				break;
			}
		}
		node t;
		t.val = a[i];
		t.pos = i;
		q.push_back(t);
		while (q.front().pos + m <= i) {
			q.pop_front();
		}
		printf("%d\n", q.front().val);
	}
	return 0;
}