#include <iostream>
#include <cstring>
using namespace std;
string s1, s2;

void f(int x1, int x2, int y1, int y2) {
	if (x1 > x2 || y1 > y2)
		return;
	char ss = s2[x2];
	int cur = s1.find(ss);
	int len1 = cur - y1;
	int len2 = y2 - cur;
	cout << ss;
	f(x1, x1 + len1 - 1, y1, cur - 1);
	f(x1 + len1, x2 - 1, cur + 1, y2);
}

int main() {
	cin >> s1 >> s2;
	int len = (int)s1.size();
	f(0, len - 1, 0, len - 1);
	return 0;
}