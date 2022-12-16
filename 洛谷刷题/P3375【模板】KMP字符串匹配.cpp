#include <iostream>
#include <algorithm>
using namespace std;
string s1, s2;
int a[2000010];

int main() {
	cin >> s1 >> s2;
	int len1 = (int)s1.size();
	int len2 = (int)s2.size();
	string s = s2 + "#" + s1;
	int len = (int)s.size();
	for (int i = 1; i < len; i++) {
		int j = a[i - 1];
		while (j > 0 && s[j] != s[i])
			j = a[j - 1];
		if (s[j] == s[i])
			j++;
		a[i] = j;
		if (j == len2)
			cout << i - 2 * len2 + 1 << endl;
	}
	for (int i = 0; i < len2; i++) {
		cout << a[i] << " ";
	}
	return 0;
}