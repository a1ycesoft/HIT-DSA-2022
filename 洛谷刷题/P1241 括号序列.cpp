#include <iostream>
#include <string.h>
using namespace std;
string s;
bool match[110];

void findleft(int n) {
	int i;
	for (i = n - 1; i >= 0; i--) {
		if (s[i] == '(' || s[i] == '[' && match[i] == false) {
			break;
		}
	}
	if (i < 0)
		return;
	if ((s[n] == ')' && s[i] == '(') || (s[n] == ']' && s[i] == '[')) {
		match[i] = true;
		match[n] = true;
	}
}

int main() {
	cin >> s;
	int len = s.size();
	for (int i = 0; i < len; i++) {
		if (s[i] == ')' || s[i] == ']') {
			findleft(i);
		}
	}
	string ss = "";
	for (int i = 0; i < len; i++) {
		if (match[i] == false) {
			if (s[i] == '(' || s[i] == ')') {
				ss += "()";
			} else {
				ss += "[]";
			}
		} else {
			ss += s[i];
		}
	}
	cout << ss;
	return 0;
}