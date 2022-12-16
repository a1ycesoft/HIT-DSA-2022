#include <iostream>
#include <queue>
using namespace std;
int n, m, x, y;
int a[405][405];

int fx[8] = {2, 2, 1, -1, -2, -2, -1, 1};

int fy[8] = { -1, 1, 2, 2, 1, -1, -2, -2 };

struct node {
	int x;
	int y;
	int cnt;
};
queue<node> q;

int main() {
	cin >> n >> m >> x >> y;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			a[i][j] = -1;
		}
	a[x][y] = 0;
	node t;
	t.x = x;
	t.y = y;
	t.cnt = 0;
	q.push(t);
	while (!q.empty()) {
		node tmp = q.front();
		q.pop();
		int xx = tmp.x;
		int yy = tmp.y;
		for (int i = 0; i < 8; i++) {
			int xxx = xx + fx[i];
			int yyy = yy + fy[i];
			if (a[xxx][yyy] == -1 && xxx >= 1 && xxx <= n && yyy >= 1 && yyy <= m) {
				a[xxx][yyy] = tmp.cnt + 1;
				node tp;
				tp.x = xxx;
				tp.y = yyy;
				tp.cnt = tmp.cnt + 1;
				q.push(tp);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}