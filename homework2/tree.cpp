#include <iostream>
#include <stack>
#include <queue>
#include <stdlib.h>
using namespace std;

//����ڵ�
typedef struct node {
	struct node *left;
	struct node *right;
	char data;
} BiTreeNode, * BiTree;

BiTree Lchild(BiTree T) {
	return T->left;
}

BiTree Rchild(BiTree T) {
	return T->right;
}

bool isEmpty(BiTree T) {
	if (T == NULL)
		return true;
	return false;
}

bool isComplete(BiTree T) {
	queue<BiTree> q;
	BiTree t = T;
	q.push(t);
	bool flag = false;
	while (!q.empty()) {
		BiTree curr = q.front();
		q.pop();
		if (curr->left) { //�������ǿ�
			if (flag == true)
				return false; //flagΪtrue˵���������������ڵ㣬��ǰ�ڵ�Ӧ��ΪҶ�ӽڵ㣬��Ӧ����������������ȫ������
			q.push(curr->left);
		} else //������Ϊ�գ�˵�������˷����ڵ㣬��flagΪtrue
			flag = true;
		if (curr->right) { //�������ǿ�
			if (flag == true)
				return false; //flagΪtrue˵���������������ڵ㣬��ǰ�ڵ�Ӧ��ΪҶ�ӽڵ㣬��Ӧ����������������ȫ������
			q.push(curr->right);
		} else //������Ϊ�գ�˵�������˷����ڵ㣬��flagΪtrue
			flag = true;

	}
	return true;
}

int width(BiTree T) {
	if (T == NULL)
		return 0;
	queue<BiTree> q;
	BiTree t = T;
	q.push(t);
	int ans = 0;
	while (!q.empty()) {
		int wid = (int)q.size();
		for (int i = 0; i < wid; i++) {

			BiTree cur = q.front();
			q.pop();
			if (cur->left) {
				q.push(cur->left);
			}
			if (cur->right) {
				q.push(cur->right);
			}
		}
		ans = wid > ans ? wid : ans;
	}
	return ans;
}

//����ǰ��˳����������
void createBiTree(BiTree &T) {
	//������Ҫ��������������������  ABD##E##CH###  ���� AB##C##
	char c;
	cin >> c;
	if ('#' == c) //������#ʱ�������ĸ��ڵ�ΪNULL���Ӷ������÷�֧�ĵݹ�
		T = NULL;
	else {
		T = new BiTreeNode;
		T->data = c;
		createBiTree(T->left);
		createBiTree(T->right);
	}
}

//ǰ��������
void preTraverse(BiTree T) {
	if (T) {
		cout << T->data << " ";
		preTraverse(T->left);
		preTraverse(T->right);
	}
}

void NpreTraverse(BiTree T) {
	stack<BiTree> s;
	BiTree t;
	t = T;
	while (!s.empty() || !isEmpty(t)) {
		if (!isEmpty(t)) {
			cout << t->data << " ";
			s.push(t);
			t = Lchild(t);
		} else {
			t = s.top();
			s.pop();
			t = Rchild(t);
		}
	}
}

//����������
void midTraverse(BiTree T) {
	if (T) {
		midTraverse(T->left);
		cout << T->data << " ";
		midTraverse(T->right);
	}
}

void NmidTraverse(BiTree T) {
	stack<BiTree> s;
	BiTree t;
	t = T;
	while (!s.empty() || !isEmpty(t)) {
		if (!isEmpty(t)) {
			s.push(t);
			t = Lchild(t);
		} else {
			t = s.top();
			s.pop();
			cout << t->data << " ";
			t = Rchild(t);
		}
	}
}

//�����������
void postTraverse(BiTree T) {
	if (T) {
		postTraverse(T->left);
		postTraverse(T->right);
		cout << T->data << " ";
	}
}

void NpostTraverse(BiTree T) {
	stack<BiTree> s;
	stack<BiTree> output;
	BiTree t;
	t = T;
	s.push(t);
	while (!s.empty()) {
		BiTree cur = s.top();
		s.pop();
		output.push(cur);
		if (cur->left) {
			s.push(cur->left);
		}
		if (cur->right) {
			s.push(cur->right);
		}
	}
	while (!output.empty()) {
		cout << output.top()->data << " ";
		output.pop();
	}
}

int main() {
	BiTree T; //����һ��ָ����������ڵ��ָ��
	createBiTree(T);
	cout << "������������ɣ�" << endl;
	cout << "ǰ�������" << endl;
	preTraverse(T);
	cout << endl;
	cout << "�ǵݹ�ǰ�������" << endl;
	NpreTraverse(T);
	cout << endl;
	cout << "���������" << endl;
	midTraverse(T);
	cout << endl;
	cout << "�ǵݹ����������" << endl;
	NmidTraverse(T);
	cout << endl;
	cout << "���������" << endl;
	postTraverse(T);
	cout << endl;
	cout << "�ǵݹ���������" << endl;
	NpostTraverse(T);
	cout << endl;
	if (isComplete(T)) {
		cout << "����ȫ������\n";
	} else {
		cout << "������ȫ������\n";
	}
	cout << "���Ϊ��";
	cout << width(T);
	cout << endl;
	system("pause");
	return 0;
}