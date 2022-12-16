#include <stdio.h>
#include <stdlib.h>
int n;
struct node
{
  int data;
  struct node *next;
};
// ��ʼ��
void init(struct node *h)
{
  printf("������N(��1����Ϊ2N,��2����ΪN):");
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
// ���
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
// locationΪ�������λ��
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
// ͨ��ֵɾ���ڵ�
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
// ͨ��λ��ɾ���ڵ�
void deletebylocation(struct node *h, int x)
{
  struct node *p = h;
  while (x--)
  {
    p = p->next;
  }
  p->next = p->next->next;
}
// ɾ���ظ���Ԫ��
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
// ��ת
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
// �ƶ�kλ��flagΪ0��ʾ���ƣ�Ϊ1��ʾ����
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
// �ϲ�
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
  printf("���Ա�1:");
  output(head);
  printf("���Ա�2:");
  output(ss);
  struct node *out = merge(head, ss);
  printf("�ϲ���:");
  output(out);
  deletebylocation(head, 0);
  printf("��1ȥ����һ���ڵ�:");
  output(head);
  deletesame(head);
  printf("��1ȥ���ظ��ڵ�:");
  output(head);
  deletebyvalue(head, 10);
  printf("�ϲ���1ȥ��ֵΪ10�Ľڵ�:");
  output(head);
  movek(ss, 0, 2);
  printf("��2�����ƶ���λ:");
  output(ss);
  movek(ss, 1, 2);
  printf("��2�����ƶ���λ:");
  output(ss);
  reverse(ss);
  printf("��ת��2:");
  output(ss);
  system("pause");
  return 0;
}