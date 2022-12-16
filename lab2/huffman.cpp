#include <iostream>
#include <stack>
#include <fstream>
#include <algorithm>
#include <bitset>
using namespace std;

int num[128]; // 各个字符出现的次数
double weight[128];// 各个字符的权重
int n = 0;  // 总节点数
int m = 0;  // 总字数
int total = 0; // 总字符种类
string code[128]; // 所有出现的字符对应的编码
int before[10000]; // 初始文章的编码
typedef struct {
	double weight;
	int data;
	int count;
	int lchild;
	int rchild;
	int parent;
	string code;
} node;
node treenode[300];

void read_file(string s) { //读入txt中的文章并统计各种字符出现的个数
	char c;
	fstream file;
	file.open(s, ios::in);
	file >> noskipws;
	while (file.peek() != EOF) {
		c = file.get();
		int x = (int)c;
		before[m] = x;
		num[x]++;
		m++;
	}
	file.close();
	for (int i = 0; i < 128; i++) {
		if (num[i]) {
			switch (i) {
				case 10:
					weight[i] = (double)num[i] / m;
					cout << "\\n"  << "\t" << weight[i] << endl;
					break;
				case 32:
					weight[i] = (double)num[i] / m;
					cout << "space" << "\t" << weight[i] << endl;
					break;
				default:
					weight[i] = (double)num[i] / m;
					cout << (char)i  << "\t" << weight[i] << endl;
					break;
			}
		}
	}
}

bool cmp(node t1, node t2) {
	return t1.weight < t2.weight;
}

void init() { //初始化二叉树，将初始的节点插入树中
	for (int i = 0; i < 128; i++) {
		if (weight[i]) {
			treenode[n].weight = weight[i];
			treenode[n].data = i;
			n++;
		}
	}
	for (int i = 0; i < 300; i++) {
		treenode[i].count = i;
		treenode[i].lchild = -1;
		treenode[i].rchild = -1;
		treenode[i].parent = -1;
	}
	total = n;
}

void selectmin(node nodetree[], int &p1, int &p2) { // 找出目前节点权值最小的两个点
	node tmp[300];
	int m = 0;
	for (int i = 0; i < n; i++) {
		if (nodetree[i].parent == -1) {
			tmp[m++] = nodetree[i];
		}
	}
	sort(tmp, tmp + m, cmp);
	p1 = tmp[0].count;
	p2 = tmp[1].count;
}

void createHuffman(node nodetree[]) { // 将目前权值最小的两个点合并并且插入到树中
	int p1, p2;
	int j = n - 1;
	for (int i = 0; i < j; i++) {
		selectmin(nodetree, p1, p2);
		nodetree[p1].parent = n;
		nodetree[p2].parent = n;
		nodetree[n].lchild = p1;
		nodetree[n].rchild = p2;
		nodetree[n].weight = nodetree[p1].weight + nodetree[p2].weight;
		n++;
	}
}

string encode(int x) { //在一个创建好的树中进行编码。按照分岔的顺序，往左赋0，往右赋1，于是每个字符都有了新的编码
	stack<int> s;
	string code = "";
	int cur = x;
	while (treenode[cur].parent != -1) {
		s.push(treenode[cur].parent);
		cur = treenode[cur].parent;
	}
	int top = s.top();
	s.pop();
	while (!s.empty()) {
		int now = s.top();
		s.pop();
		if (now == treenode[top].lchild) {
			code += "0";
		} else if (now == treenode[top].rchild) {
			code += "1";
		}
		top = now;
	}
	if (x == treenode[top].lchild) {
		code += "0";
	} else if (x == treenode[top].rchild) {
		code += "1";
	}
	return code;
}

void eng2huf() { // 将英文asc2码转化为哈夫曼编码
	for (int i = 0; i < total; i++) {
		treenode[i].code = encode(i);
		code[treenode[i].data] = encode(i);
	}
}

void showtree() {
	for (int i = 0; i < total; i++) {
		cout << i << "\t" << treenode[i].weight << "\t" << treenode[i].data << "\t" << treenode[i].parent << "\t" <<
		     treenode[i].lchild << "\t" << treenode[i].rchild << "\t" << endl;
	}
}

void showcode() {  // 展示哈夫曼编码
	for (int i = 0; i < total; i++) {
		switch (treenode[i].data) {
			case 10:
				cout << "\\n\t" << treenode[i].code << endl;
				break;
			case 32:
				cout << "space\t" << treenode[i].code << endl;
				break;
			default:
				cout << (char)treenode[i].data << "\t" << treenode[i].code << endl;
				break;
		}
	}
}

int write_file(string s) { //将字符串编码转化为二进制bitset串并保存为二进制文件
	string after = "";
	for (int i = 0; i < m; i++) {
		after += code[before[i]];
	}
	int bitslen = after.size();
	int len = bitslen;
	if (len % 8 == 0)
		len /= 8;
	else {
		len = len / 8;
		len++;
	}
	bitset<100000> *b = new bitset<100000>(after);
	ofstream out("huffman.dat", ios::out | ios::binary);
	out.write((char *)b, len);
	out.close();
	return bitslen;
}

string back(int len1, int len2) { //读取二进制文件并转化为01string串，然后依据编码规则转化回英文
	string co;
	string ans = "";
	char tmp;
	ifstream file("huffman.dat", ios::in | ios::binary);
	string x = "";
	for (int i = 1; i <= len1; i++) {
		file.read(&tmp, 1);
		for (int j = 0; j < 8; j++) {
			x += (tmp & 1 == 1 ? '1' : '0');
			tmp = tmp >> 1;
		}
	}
	reverse(x.begin(), x.end());
	int lenx = x.size();
	co = x.substr(lenx - len2, len2);
	cout << "读取二进制文件：" << co << endl;
//	co 为01序列串
	int j = 0;
	int len = (int)co.size();
	while (j < len) {
		for (int i = 0; i < total; i++) {
			int l = treenode[i].code.size();
			string ss = co.substr(j, l);
			if (ss == treenode[i].code) {
				j += l;
				ans += (char)treenode[i].data;
				break;
			}
		}
	}
	return ans;
}

int main() {
	read_file("article.txt");
	init();
	createHuffman(treenode);
	cout << endl;
	eng2huf();
	showcode();
	cout << endl;
	int blen = write_file("after.txt");
	int Blen = blen % 8 == 0 ? (blen / 8) : (blen / 8 + 1);
	string ans = back(Blen, blen);
	cout << ans << endl;
	int len = ans.size();
	ofstream out;
	out.open("huffman.txt", ios::out);
	out << ans;
	out.close();
	system("pause");
	return 0;
}