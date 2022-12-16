#include <bits/stdc++.h>
using namespace std;

void showChange(string s, stack<char> symbol) {
	string u = "";
	while (!symbol.empty()) {
		u += symbol.top();
		symbol.pop();
	}
	reverse(u.begin(), u.end());
	cout << "������ʽ��" << s << endl  << "����ջ��" << u << endl << "--------------------" << endl;
}

void showCal(stack<int> num) {
	int x[100], i = 0;
	while (!num.empty()) {
		x[i] = num.top();
		i++;
		num.pop();
	}
	cout << "��ջ��";
	for (int j = i - 1; j >= 0 ; j--)
		cout << x[j] << " ";
	cout << endl;
}

string toPostOrder(string s) {
	cout << "��������ʽת��Ϊ������ʽ��" << endl;
	int len = (int)s.size();
	stack<char> symbol;
	string ans = "";
	for (int i = 0; i < len; i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			ans += s[i];
			showChange(ans, symbol);
			if (s[i + 1] < '0' || s[i + 1] > '9') {
				ans += ' ';
			}
		} else if (s[i] == '(') {
			symbol.push(s[i]);
			showChange(ans, symbol);
		} else if (s[i] == ')') {
			while (!symbol.empty()) {
				char t = symbol.top();
				if (t == '(')
					break;
				ans += t;
				ans += ' ';
				symbol.pop();
			}
			symbol.pop();
			showChange(ans, symbol);
		} else if (s[i] == '*' || s[i] == '/') {
			while (!symbol.empty()) {
				char t = symbol.top();
				if (t == '(' || t == '+' || t == '-')
					break;

				ans += t;
				ans += ' ';
				symbol.pop();
			}
			symbol.push(s[i]);
			showChange(ans, symbol);
		} else if (s[i] == '+') {
			while (!symbol.empty()) {
				char t = symbol.top();
				if (t == '(')
					break;

				ans += t;
				ans += ' ';
				symbol.pop();
			}
			symbol.push(s[i]);
			showChange(ans, symbol);
		} else if (s[i] == '-') {
			if (i == 0 || (s[i - 1] < '0' || s[i - 1] > '9')) //�жϸ���
				ans += s[i];
			else {
				while (!symbol.empty()) {
					char t = symbol.top();
					if (t == '(')
						break;

					ans += t;
					ans += ' ';
					symbol.pop();
				}
				symbol.push(s[i]);
				showChange(ans, symbol);
			}

		}
	}
	while (!symbol.empty()) {
		char t = symbol.top();

		ans += t;
		ans += ' ';
		symbol.pop();
	}
	showChange(ans, symbol);
	return ans;
}

int cal(string s) {
	cout << "ͨ��������ʽ���㣺" << endl;
	stack<int> num;
	int len = (int)s.size();
	int i = 0;
	while (i < len) {
		if (s[i] >= '0' && s[i] <= '9') {
			string ss = "";
			while (s[i] != ' ') {
				ss += s[i];
				i++;
			}
			num.push(stoi(ss));
			showCal(num);

		} else if (s[i] == '-' && (s[i + 1] >= '0' && s[i + 1] <= '9') && i != len - 1 ) {
			string ss = "";
			while (s[i] != ' ') {
				ss += s[i];
				i++;
			}
			num.push(stoi(ss));
			showCal(num);

		} else if (s[i] == ' ') {
			i++;
		} else {
			int x1 = num.top();
			num.pop();
			int x2 = num.top();
			num.pop();
			switch (s[i]) {
				case '+':
					cout << "��ȡ����+��\n";
					num.push(x1 + x2);
					break;
				case '-':
					cout << "��ȡ����-��\n";
					num.push(x2 - x1);
					break;
				case '*':
					cout << "��ȡ����*��\n";
					num.push(x1 * x2);
					break;
				case '/':
					cout << "��ȡ����/��\n";
					num.push(x2 / x1);
					break;
			}
			showCal(num);
			i++;
		}
	}
	return num.top();
}

int main() {
	ifstream in("question.txt", ios::in);
	istreambuf_iterator<char> beg(in), end;
	string s(beg, end);
	in.close();
	cout << "������ʽΪ��" << s << endl;
	cout << endl;
	string ss = toPostOrder(s);
	cout << "���պ������ʽ��" << ss << endl;
	cout << endl;
	int ans = cal(ss);
	cout << "��������" << ans << endl;
	system("pause");
	return 0;
}
