#include <bits/stdc++.h>
using namespace std;
int n;
string a[30];

int cmp(string s1, string s2) {
	int l1 = (int)s1.size();
	int l2 = (int)s2.size();
	int i = 0;
	while (i < l1 && i < l2) {
		if (s1[i] == s2[i]) {
			i++;
		} else if (s1[i] > s2[i])
			return 1;
		else if (s1[i] < s2[i])
			return -1;
	}
	string s3 = s1 + s2;
	string s4 = s2 + s1;
	if (s3 > s4)
		return 1;
	else if (s3 == s4)
		return 0;
	else
		return -1;
}

void swap(int i, int j) {
	string t = a[i];
	a[i] = a[j];
	a[j] = t;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (cmp(a[j], a[j + 1]) > 0) {
				swap(j, j + 1);
			}
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		cout << a[i];
	}
	return 0;
}