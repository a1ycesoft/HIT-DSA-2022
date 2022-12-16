#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n;
#define max 100
struct node
{
  int elements[max];
  int last;
};
// 初始化
void init(struct node *h)
{
  printf("输入N(表1长度为2N,表2长度为N):");
  scanf("%d", &n);
  for (int i = 0; i < n * 2; i++)
  {
    h->elements[i] = 3;
  }
  h->last = 2 * n - 1;
}
void init2(struct node *h)
{
  for (int i = 0; i < n; i++)
  {
    h->elements[i] = i;
  }
  h->last = n - 1;
}
// 输出
void output(struct node *h)
{
  for (int i = 0; i <= h->last; i++)
  {
    printf("%d ", h->elements[i]);
  }
  printf("\n");
}

// 删除元素值为x的节点
void deletebyvalue(struct node *h, int x)
{
  int k = 0, i = 0;
  while (i <= h->last)
  {
    if (h->elements[i] == x)
      k++;
    else
      h->elements[i - k] = h->elements[i];
    i++;
  }
  h->last = h->last - k;
}

// 对已经排序好的线性表删除重复的元素
void deletesame(struct node *h)
{
  int k = 0, i = 0;
  while (i <= h->last)
  {
    int x = h->elements[i];
    if (h->elements[i + 1] == x)
      k++;
    else
      h->elements[i - k] = h->elements[i];
    i++;
  }
  h->last = h->last - k;
}

// 反转
void reverse(struct node *h)
{
  for (int i = 0; i <= h->last / 2; i++)
  {
    int t = h->elements[i];
    h->elements[i] = h->elements[h->last - i];
    h->elements[h->last - i] = t;
  }
}
// 移位,flag为0表示向左，为1表示向右，k为移动的位数
void movek(struct node *h, int flag, int k)
{
  if (flag == 0)
  {
    int *p = (int *)malloc(sizeof(int) * k);
    memcpy(p, h->elements, sizeof(int) * k);
    for (int i = k; i <= h->last; i++)
    {
      h->elements[i - k] = h->elements[i];
    }
    for (int i = h->last - k + 1; i <= h->last; i++)
    {
      h->elements[i] = *(p + i - h->last + k - 1);
    }
  }
  else
  {
    movek(h, 0, h->last - k + 1);
  }
}
// 合并
struct node *merge(struct node *a, struct node *b)
{
  struct node *head = (struct node *)malloc(sizeof(struct node));
  int i = 0, j = 0, k = 0;
  while (i <= a->last && j <= b->last)
  {
    head->elements[k++] = a->elements[i] < b->elements[j] ? a->elements[i++] : b->elements[j++];
  }
  while (i <= a->last)
  {
    head->elements[k++] = a->elements[i++];
  }
  while (j <= b->last)
  {
    head->elements[k++] = b->elements[j++];
  }
  head->last = a->last + b->last + 1;
  return head;
}
int main()
{
  struct node *head = (struct node *)malloc(sizeof(struct node));
  struct node *ss = (struct node *)malloc(sizeof(struct node));

  init(head);
  init2(ss);
  printf("初始化表1:");
  output(head);
  printf("初始化表2:");
  output(ss);
  struct node *out = merge(head, ss);
  printf("合并表:");
  output(out);
  deletesame(out);
  printf("删除合并表上重复元素:");
  output(out);
  deletebyvalue(out, 3);
  printf("删除合并表上值为3的节点:");
  output(out);
  movek(ss, 0, 2);
  printf("表2左移2:");
  output(ss);
  movek(ss, 1, 3);
  printf("表2右移3:");
  output(ss);
  reverse(ss);
  printf("反转表2:");
  output(ss);
  system("pause");
  return 0;
}