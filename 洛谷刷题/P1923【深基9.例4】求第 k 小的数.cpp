#include <bits/stdc++.h>
using namespace std;
int n, k;
int a[5000010];

int partition(int a[], int low, int high) {
	int pivot = a[low];
	int i = low, j = high;
	while (i < j) {
		while (i < j && a[j] >= pivot) {
			j--;
		}
		a[i] = a[j];
		while (i < j && a[i] <= pivot) {
			i++;
		}
		a[j] = a[i];
	}
	a[i] = pivot;
	return i;
}

void quicksort(int a[], int i, int j) {
	if (i > j) {
		return;
	}
	int pivot = partition(a, i, j);
	//for (int i = 1; i <= n; i++)
	//	cout << a[i] << " ";
	//cout << endl;
	//cout << pivot<< endl;
	if (pivot - 1 < k) {
		quicksort(a, pivot + 1, j);
	} else if (pivot - 1 > k) {
		quicksort(a, i, pivot - 1);
	} else {
		cout << a[pivot];
		return;
	}

}

int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	quicksort(a, 1, n);
	return 0;
}