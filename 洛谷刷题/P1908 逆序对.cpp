#include <bits/stdc++.h>
using namespace std;
int n;
long long ans = 0;
int a[500010];

void merge(int i1, int i2, int j1, int j2) {
	//cout << i1 << "--"<<i2<<"--" << j1 <<"--"<<j2<< endl;
	int *b = new int[j2 - i1 + 1];
	int k1 = i1, k2 = j1, k = 0;
	while (k1 <= i2 && k2 <= j2) {
		if (a[k1] <= a[k2]) {
			ans += k2 - j1;
			b[k++] = a[k1++];
		} else {
			b[k++] = a[k2++];
		}
	}
	while (k1 <= i2) {
		ans += k2 - j1;
		b[k++] = a[k1++];
	}
	while (k2 <= j2) {
		b[k++] = a[k2++];
	}
	k = 0;
	for (int i = i1; i <= j2; i++)
		a[i] = b[k++];
	free(b);
}

void mergesort(int i, int j) {
	if (i >= j)
		return;
	//for (int k = i; k <= j; k++)
	//	cout << a[k] << " ";
	//cout << endl;
	int mid = (i + j) / 2;
	mergesort(i, mid);
	mergesort(mid + 1, j);
	merge(i, mid, mid + 1, j);
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	mergesort(1, n);
	//for (int i = 1; i <= n; i++)
	//	cout << a[i] << " ";
	cout << ans;
	return 0;
}