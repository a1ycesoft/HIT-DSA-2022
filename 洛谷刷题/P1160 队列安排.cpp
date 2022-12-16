#include <iostream>
using namespace std;

struct node {
	int l;
	int r;
} a[1000010];
int n, m;
int most_left = 1;

void insert(int now, int canzhao, int pos) {
	if (pos == 0) { // 插入参照的左边
		int ll = a[canzhao].l;
		a[canzhao].l = now;
		a[now].r = canzhao;
		a[now].l = ll;
		a[ll].r = now;
		if (canzhao == most_left) {
			most_left = now;
		}
	} else { // 插入参照的右边
		int rr = a[canzhao].r;
		a[canzhao].r = now;
		a[now].l = canzhao;
		a[now].r = rr;
		a[rr].l = now;
	}
}

void deletenode(int now) {
	if (a[now].l != -1 && a[now].r != -1) {
		int ll = a[now].l;
		int rr = a[now].r;
		a[ll].r = rr;
		a[rr].l = ll;
		a[now].l = -1;
		a[now].r = -1;
	}
}

void output() {
	int x = most_left;
	while (x != 0) {
		cout << x << " ";
		x = a[x].r;
	}
}

int main() {
	cin >> n;
	int canzhao, pos;
	for (int i = 0; i < n - 1; i++) {
		cin >> canzhao >> pos;
		insert(i + 2, canzhao, pos);
	}
	cin >> m;
	int del;
	for (int i = 0; i < m; i++) {
		cin >> del;
		deletenode(del);
	}
	output();
	return 0;
}