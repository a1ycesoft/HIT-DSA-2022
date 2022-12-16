#include <iostream>
#include <cstring>
using namespace std;
int n;
int m = 1;
string s;

struct node {
	int l;
	int r;
	char s;
};
struct node a[4000];

int pow(int a, int b) {
	int ans = 1;
	for (int i = 0; i < b; i++) {
		ans *= a;
	}
	return ans;
}

bool isB(string str) {
	int len = (int)str.size();
	for (int i = 0; i < len; i++) {
		if (str[i] != '0')
			return false;
	}
	return true;
}

bool isI(string str) {
	int len = (int)str.size();
	for (int i = 0; i < len; i++) {
		if (str[i] != '1')
			return false;
	}
	return true;
}

void init(int n) {
	for (int i = 1; i < 4000; i++) {
		if (i <= pow(2, n) - 1) {
			a[i].l = 2 * i;
			a[i].r = 2 * i + 1;
		} else {
			a[i].l = -1;
			a[i].r = -1;
		}
	}
}

void houxu(int i) {
	if (i == -1) {
		return;
	}
	houxu(a[i].l);
	houxu(a[i].r);
	cout << a[i].s;
}

int main() {
	cin >> n >> s;
	init(n);
	int len = (int)s.size();
	for (int i = 0; i <= n; i++) {
		int k = pow(2, i);
		for (int j = 0; j < k; j++) {
			string ss = s.substr(j * len / k, len / k);
			if (isB(ss)) {
				a[m++].s = 'B';
			} else if (isI(ss)) {
				a[m++].s = 'I';
			} else {
				a[m++].s = 'F';
			}
		}
	}
	houxu(1);
	return 0;
}