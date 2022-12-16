#include <iostream>
#include <stack>
#include <queue>
#include <stdlib.h>
using namespace std;

//定义节点
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
		if (curr->left) { //左子树非空
			if (flag == true)
				return false; //flag为true说明已遇到过非满节点，当前节点应当为叶子节点，不应该有左子树，非完全二叉树
			q.push(curr->left);
		} else //左子树为空，说明遇到了非满节点，置flag为true
			flag = true;
		if (curr->right) { //右子树非空
			if (flag == true)
				return false; //flag为true说明已遇到过非满节点，当前节点应当为叶子节点，不应该有右子树，非完全二叉树
			q.push(curr->right);
		} else //右子树为空，说明遇到了非满节点，置flag为true
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

//按照前序顺序建立二叉树
void createBiTree(BiTree &T) {
	//输入需要将二叉树补成满二叉树  ABD##E##CH###  或者 AB##C##
	char c;
	cin >> c;
	if ('#' == c) //当遇到#时，令树的根节点为NULL，从而结束该分支的递归
		T = NULL;
	else {
		T = new BiTreeNode;
		T->data = c;
		createBiTree(T->left);
		createBiTree(T->right);
	}
}

//前序遍历输出
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

//中序遍历输出
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

//后续遍历输出
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
	BiTree T; //声明一个指向二叉树根节点的指针
	createBiTree(T);
	cout << "二叉树创建完成！" << endl;
	cout << "前序遍历：" << endl;
	preTraverse(T);
	cout << endl;
	cout << "非递归前序遍历：" << endl;
	NpreTraverse(T);
	cout << endl;
	cout << "中序遍历：" << endl;
	midTraverse(T);
	cout << endl;
	cout << "非递归中序遍历：" << endl;
	NmidTraverse(T);
	cout << endl;
	cout << "后序遍历：" << endl;
	postTraverse(T);
	cout << endl;
	cout << "非递归后序遍历：" << endl;
	NpostTraverse(T);
	cout << endl;
	if (isComplete(T)) {
		cout << "是完全二叉树\n";
	} else {
		cout << "不是完全二叉树\n";
	}
	cout << "宽度为：";
	cout << width(T);
	cout << endl;
	system("pause");
	return 0;
}