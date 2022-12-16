#include <stdio.h>
#include <stdlib.h>
int n;
struct node
{
  int data;
  struct node *next;
};
// 初始化
void init(struct node *h)
{
  printf("请输入N(表1长度为2N,表2长度为N):");
  scanf("%d", &n);
  h->next = (struct node *)malloc(sizeof(struct node));
  struct node *before = h;
  for (int i = 0; i < n; i++)
  {
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->data = i;
    before->next = p;
    before = p;
  }
  for (int i = 0; i < n; i++)
  {
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->data = 10;
    before->next = p;
    before = p;
  }
  before->next = NULL;
}
void init2(struct node *h)
{
  h->next = (struct node *)malloc(sizeof(struct node));
  struct node *before = h;
  for (int i = 0; i < n; i++)
  {
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->data = i + 2;
    before->next = p;
    before = p;
  }
  before->next = NULL;
}
// 输出
void output(struct node *h)
{
  struct node *p = h;
  p = p->next;
  while (p != NULL)
  {
    printf("%d ", p->data);
    p = p->next;
  }
  printf("\n");
}
// location为待插入的位置
void insert(struct node *h, int location, int x)
{
  struct node *p = h;
  while (location--)
  {
    p = p->next;
  }
  struct node *add = (struct node *)malloc(sizeof(struct node));
  add->data = x;
  add->next = p->next;
  p->next = add;
}
// 通过值删除节点
void deletebyvalue(struct node *h, int x)
{
  struct node *p = h;
  p = p->next;
  struct node *before = h;
  while (p != NULL)
  {
    if (p->data == x)
    {
      before->next = p->next;
    }
    before = p;
    p = p->next;
  }
}
// 通过位置删除节点
void deletebylocation(struct node *h, int x)
{
  struct node *p = h;
  while (x--)
  {
    p = p->next;
  }
  p->next = p->next->next;
}
// 删除重复的元素
void deletesame(struct node *h)
{
  struct node *p = h;
  p = p->next;
  while (p->next != NULL)
  {
    if (p->data == p->next->data)
    {
      p->next = p->next->next;
    }
    else
    {
      p = p->next;
    }
  }
}
// 反转
void reverse(struct node *h)
{
  int k = n;
  while (k--)
  {
    int x = h->next->data;
    deletebylocation(h, 0);
    insert(h, k, x);
  }
}
// 移动k位。flag为0表示左移，为1表示右移
void movek(struct node *h, int flag, int k)
{
  if (flag == 0)
  {
    while (k--)
    {
      int x = h->next->data;
      deletebylocation(h, 0);
      insert(h, n - 1, x);
    }
  }
  else
  {
    int u = n - k;
    while (u < 0)
      u += n;
    while (u--)
    {
      int x = h->next->data;
      deletebylocation(h, 0);
      insert(h, n - 1, x);
    }
  }
}
// 合并
struct node *merge(struct node *a, struct node *b)
{
  struct node *head = (struct node *)malloc(sizeof(struct node));
  struct node *before = head;
  struct node *aa = a->next;
  struct node *bb = b->next;
  while (aa != NULL && bb != NULL)
  {
    int l = aa->data, r = bb->data;
    struct node *p = (struct node *)malloc(sizeof(struct node));
    if (l < r)
    {
      p->data = l;
      aa = aa->next;
    }
    else
    {
      p->data = r;
      bb = bb->next;
    }
    before->next = p;
    before = p;
  }
  while (aa != NULL)
  {
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->data = aa->data;
    before->next = p;
    before = p;
    aa = aa->next;
  }
  while (bb != NULL)
  {
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->data = bb->data;
    before->next = p;
    before = p;
    bb = bb->next;
  }
  before->next = NULL;
  return head;
}
int main()
{
  struct node *head = (struct node *)malloc(sizeof(struct node));
  struct node *ss = (struct node *)malloc(sizeof(struct node));
  init(head);
  init2(ss);
  printf("线性表1:");
  output(head);
  printf("线性表2:");
  output(ss);
  struct node *out = merge(head, ss);
  printf("合并表:");
  output(out);
  deletebylocation(head, 0);
  printf("表1去除第一个节点:");
  output(head);
  deletesame(head);
  printf("表1去除重复节点:");
  output(head);
  deletebyvalue(head, 10);
  printf("合并表1去除值为10的节点:");
  output(head);
  movek(ss, 0, 2);
  printf("表2向左移动两位:");
  output(ss);
  movek(ss, 1, 2);
  printf("表2向右移动两位:");
  output(ss);
  reverse(ss);
  printf("反转表2:");
  output(ss);
  system("pause");
  return 0;
}