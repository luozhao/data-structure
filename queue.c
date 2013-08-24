/*
  单链队列的实现：单链队列使用链表作为基本数据结构，所以不存在溢出问题(除非主存耗完)，队列长度也没有限制。
  但是插入和读取的时间成本较高。
*/
/* 单链队列--队列的链式存储结构 */
typedef struct QNode {
  QElemType data;
  struct QNode *next;
}QNode, *QueuePtr;

typedef struc {
  QueuePtr front, rear; /* 队头队尾指针  */
}LinkQueue;

/* 链队列的基本操作(9个) */

/* 构造一个空队列 */
void InitQueue(LinkQueue *Q)
{
  Q->font = Q->rear = malloc(sizeof(QNode);
  if(!Q->font)
    exit(1);
  Q->front->next = NULL;
}

/* 销毁队列Q  */
void DestroyQueue(LinkQueue *Q)
{
  while(Q->front) {
    Q->rear = Q->front->next;
    free(Q->front);
    Q->front = Q->rear;
  }
}

/* 清空队列Q */
void ClearQueue(LinkQueue *Q)
{
  QueuePtr p,q;
  Q->rear = Q->front;
  p = Q->front->next;
  Q->front->next = NULL;
  while(p) {
    q = p;
    p = q->next;
    free(q);
  }
}

/* 若Q为空队列，则返回TRUE，否则返回FALSE */
Status QueueEmpty(LinkQueue Q)
{
  if(Q->font->next == NULL)
    return TRUE;
  else
    return FALSE;
}

/*  求队列的长度 */
int QueueLength(LinkQueue Q)
{
  int i = 0;
  QueuePtr p;
  p = Q.front;
  while(Q.rear != p) {
    i++;
    p = p->next;
  }
  return i;
}

/* 若队列不为空，则用e返回Q的队头元素，并返回OK，否则返回ERROR */
Status GetHead_Q(LinkQueue Q, QElemType *e)
{
  QueuePtr p;
  if(Q.front == Q.rear)
    return ERROR;
  p = Q.front->next;
  *e = p->data;
  return OK;
}

/*  插入e作为Q新的队尾元素 */
void EnQueue(LinkQueue *Q, QElemType e)
{
  QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
  if(!p)
    exit(1);
  p->data = e;
  p->next = NULL;
  Q->rear->next = p;
  Q->rear = p;
}

/*  若队列不空，删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR */
Status DeQueue(LinkQueue *Q, QElemType *e)
{
  QueuePtr p;
  if(Q->front == Q->rear)
    return ERROR;
  p = Q->front; /* 指向头结点 */
  *e = p->data;
  Q->front = p->next;
  if(Q->rear == p)
    Q->rear = Q->front;
  free(p);
  return OK;
}

/* 从队头到队尾依次对队列Q中每个元素调用函数vi() */
void QueueTraverse(LinkQueue Q, (void)(*visit)(QElemType))
{
  QueuePtr p;
  p = Q.front->next;
  while(p) {
    visit(p->data);
    p = p->next;
  }
  printf("\n");
}
--------------------------------------我就是分割线啦----------------------------------------------------------
循环队列
循环队列可以更简单防止伪溢出的发生，但队列大小是固定的。
/* 队列的顺序存储结构(循环队列) */
#define MAX_QSIZE 5 /* 最大队列长度加1*/
typedef struct {
  QElemType *base;/* 初始化的动态分配存储空间 */
  int front;/* 头指针，若队列不空，指向队列头元素 */
  int rear;/* 尾指针，若队列不空，指向队列尾元素的下一个位置 */
}SqQueue;

循环队列的基本操作(9个)
/* 构造一个空队列 */
void InitQueue(SqQueue *Q)
{
  Q->base = malloc(MAX_QSIZE * sizeof(QElemType));
  if(!Q->base)
    exit(1);
  Q->front = Q->rear = 0;
}

/* 销毁队列Q，Q不再存在 */
void DestroyQueue(SqQueue *Q)
{
  if(Q->base)
    free(Q->base);
  Q->base = NULL;
  Q->front = Q->rear = 0;
}

/* 将Q清为空队列 */
void ClearQueue(SeQueue *Q)
{
  Q->front = Q->rear = 0;
}

/* 若队列Q为空队列，则返回TRUE；否则返回FALSE */
Status QueueEmpty(SqQueue Q)
{
  if(Q.front == Q.rear)
    return TRUE:
  else
    return FALSE:
}

/* 返回Q的元素个数，即队列的长度 */
int QueueLength(SeqQueue Q)
{
  return (Q.rear - Q.front + MAX_QSIZE) % MAX_QSIZE;
}

/* 若队列不空，则用e返回Q的队头元素，并返回OK；否则返回ERROR */
Status GetHead(SqQueue Q, QElemType *e)
{
  if(Q.front == Q.rear)
    return ERROR; //  队列为空
  *e = Q.base[Q.front];
  return OK;
}

/* 插入元素e为Q的新的队尾元素 */
Status EnQueue (SeQueue *Q, QElemType *e)
{
  if((Q->rear+1)% MAX_QSIZE == Q->front)  //  队列满
    return ERROR;
  Q->base[Q->rear] = e;
  Q->rear = (Q->rear + 1) % MAX_QSIZE;
  return OK;
}

/* 若队列不空，则删除Q的队头元素，用e返回其值，并返回OK；否则返回ERROR */
Status DeQueue(SqQueue *Q, ElemType *e)
{
  if(Q->front == Q->rear) //  队列空
    return ERROR;
  *e = Q->base[Q->front];
  Q->front = (Q->front+1) % MAX_QSIZE;
  return OK;
}

/* 从队头到队尾依次对队列Q中每个元素调用函数visit() */
void QueueTraverse(SqQueue Q, void(*visit)(QElemType))
{
  int i ;
  i = Q.front;
  while(i!=Q.rear)
  {
    visit(Q.base[i];
    i = (i+1)%MAX_QSIZE;
  }
  printf("\n");
}
---------------------------------------------我还是分割线-------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
/*阵列结构，说白了就是用数组存储元素 */
struct Queue
{
  int Array[10];//阵列空间大小
  int head;//前端(front)
  int tail;//后端(rear)
  int length;//当前队列长度，并且使用此成员判断满和空    
};

/*元素插入队列*/
void EnQueue(struct Queue *Queue1,int x)
{
  Queue1->Array[Queue1->tail]=x;
  if(Queue1->tail+1==10)//Queue1->length 改空间大小为10
  {
    Queue1->tail=0;//1改为0                 
  }
  else
  {
    Queue1->tail=Queue1->tail+1;
  }
  Queue1->length=Queue1->length+1;//当前个数增1
}

/*删除队列元素*/
int DeQueue(struct Queue *Queue1)
{
  int x=Queue1->Array[Queue1->head];
  if(Queue1->head+1==10)//空間大小10
  {
    Queue1->head=0;                               
  }
  else
  {
    Queue1->head=Queue1->head+1;    
  }
  Queue1->length=Queue1->length-1;//移出后減少1
  return x;
}
/*基本操作*/
int main()
{
  struct Queue *Queue1=malloc(sizeof(struct Queue));
  Queue1->length=0;
  Queue1->head=0;
  Queue1->tail=0;
  EnQueue(Queue1,5);//將5放入
  EnQueue(Queue1,8);//將8放入
  EnQueue(Queue1,3);//將3放入
  EnQueue(Queue1,2);//將2放入
  printf("%d ",DeQueue(Queue1));  
  printf("%d ",DeQueue(Queue1));
  printf("%d ",DeQueue(Queue1));
  system("pause");   
}

Note:以上便是队列的基本介绍，包括队列的概念以及应用，最后介绍了，队列的几种常见实现方式。
