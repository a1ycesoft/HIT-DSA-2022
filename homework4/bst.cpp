#include <bits/stdc++.h>
using namespace std;
#define maxn 2000
int n = 0;

struct node {
	int val;
	int l;
	int r;
	bool f = 0;
} tree[maxn];

void init() {
	n = 0;
	for (int i = 0; i < maxn; i++) {
		tree[i].val = 0;
		tree[i].l = 0;
		tree[i].r = 0;
		tree[i].f = 0;
	}
}

void print(int o) {
	// ������ o Ϊ���ڵ�Ķ���������
	if (!tree[o].f)
		return;  // ��������������
	print(tree[o].l);    // �ݹ����������
	printf("%d ", tree[o].val);  // ������ڵ���Ϣ
	print(tree[o].r);  // �ݹ����������
}

void insert(int &o, int v) {
	if (!tree[o].f) {
		o = ++n;
		tree[o].val = v;
		tree[o].f = 1;
		return;
	}
	if (tree[o].val > v)
		insert(tree[o].l, v);
	if (tree[o].val < v)
		insert(tree[o].r, v);
}

int deletemin(int &o) {
	if (!tree[o].l) {
		int u = o;
		o = tree[o].r;
		tree[u].f = 0;
		return u;
	} else {
		int u = deletemin(tree[o].l);
		return u;
	}
}

void findv(int o, int v, int &cnt) {

	if (!tree[o].f)
		return;
	cnt++;
	if (tree[o].val == v) {
		//  printf("Found:%d\n", o);
		return;
	}
	if (tree[o].val > v)
		findv(tree[o].l, v, cnt);
	if (tree[o].val < v)
		findv(tree[o].r, v, cnt);
}

void del(int &o, int v) {
	if (tree[o].val == v) {

		if (tree[o].l && tree[o].r)
			o = deletemin(tree[o].r);
		// ������������������СֵΪ��
		else
			o = tree[o].l + tree[o].r;
		return;
	}
	if (tree[o].val > v)
		del(tree[o].l, v);
	if (tree[o].val < v)
		del(tree[o].r, v);
}

int binary_search(int *arr, int start, int end, int key, int &cnt) {
	int ret = -1;  // δ���������ݷ���-1�±�
	int mid;
	while (start <= end) {
		cnt++;
		mid = start + ((end - start) >> 1);  // ֱ��ƽ�����ܻ����������������㷨
		if (arr[mid] < key)
			start = mid + 1;
		else if (arr[mid] > key)
			end = mid - 1;
		else {  // ������������Ϊ��������������Ǵ��ھ���С��
			ret = mid;
			break;
		}
	}
	return ret;  // ��һ����
}

int main() {
	int root1 = 0, root2 = 0;
	double avl1 = 0, avl2 = 0;
	for (int i = 1; i < 2048; i += 2)
		insert(root1, i);
	int sum1 = 0, sum2 = 0;
	for (int i = 1; i < 2048; i += 2) {
		int cnt = 0;
		findv(root1, i, cnt);
		sum1 += cnt;
	}
	avl1 = (double)sum1 / 1024;
	for (int i = 0; i <= 2048; i += 2) {
		int cnt = 0;
		findv(root1, i, cnt);
		sum2 += cnt;
	}
	avl2 = (double)sum2 / 1025;
	cout << "BST����һ(���ҳɹ�/ʧ�ܵ�ƽ�����ҳ���)��" << avl1 << " " << avl2 << endl;
	init();
	sum1 = 0;
	sum2 = 0;
	avl1 = 0;
	avl2 = 0;
	int x[1024];
	for (int i = 1; i < 2048; i += 2) {
		x[(i + 1) / 2 - 1] = i;
	}
	srand(time(0));
	for (int i = 1; i < 10000; i++) {
		int xx = rand() % 1024;
		int yy = rand() % 1024;
		if (xx != yy)
			swap(x[xx], x[yy]);
	}
	cout << "���������������У�\n";
	for (int i = 0; i < 1024; i++) {
		cout << x[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 1024; i ++) {
		insert(root2, x[i]);
	}

	for (int i = 1; i < 2048; i += 2) {
		int cnt = 0;
		findv(root1, i, cnt);
		sum1 += cnt;
	}
	avl1 = (double)sum1 / 1024;
	for (int i = 0; i <= 2048; i += 2) {
		int cnt = 0;
		findv(root1, i, cnt);
		sum2 += cnt;
	}
	avl2 = (double)sum2 / 1025;
	cout << "BST������(���ҳɹ�/ʧ�ܵ�ƽ�����ҳ���)��" << avl1 << " " << avl2 << endl;
	cout << "�������BST��\n";
	print(root2);
	cout << endl;
	cout << "BST����ӣ�(�����1000)\n";
	insert(root2, 1000);
	cout << "�������BST��\n";
	print(root2);
	cout << endl;
	cout << "BST��ɾ����(ɾ����521)\n";
	del(root2, 521);
	cout << "�������BST��\n";
	print(root2);
	cout << endl;
	for (int i = 1; i < 2048; i += 2) {
		x[(i + 1) / 2 - 1] = i;
	}
	sum1 = 0;
	sum2 = 0;
	avl1 = 0;
	avl2 = 0;
	for (int i = 1; i < 2048; i += 2) {
		int cnt = 0;
		binary_search(x, 0, 1023, i, cnt);
		sum1 += cnt;
	}
	avl1 = (double)sum1 / 1024;
	for (int i = 0; i <= 2048; i += 2) {
		int cnt = 0;
		binary_search(x, 0, 1023, i, cnt);
		sum2 += cnt;
	}
	avl2 = (double)sum2 / 1025;
	cout << "�۰����(���ҳɹ�/ʧ�ܵ�ƽ�����ҳ���)��" << avl1 << " " << avl2 << endl;
	system("pause");
	return 0;
}