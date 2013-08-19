/*
  双向链表的数据结构及基本操作
*/

/* 线性表的双向链表存储结构 */
typedef struct DuLNode 
{
  ElemType data;
  struct DuLNode *prior, *next;
}DuLNode,*DuLinkList;

/* 带头结点的双向循环链表的基本操作 */
void InitList(DuLinkList *L)
{
  /* 产生空的双向循环链表L */
  *L = (DuLinkList)malloc(sizeof(DuLNode);
  if(*L)
    (*L)->next = (*L)->prior = *L;
  else
    exit(OVERFLOW);
}

/* 销毁双链表 */
void DestroyList(DuLinkList *L)
{
  DuLinkList q, p = (*L)->next; /*  p指向第一个结点 */
  while(p!=*L)  /*  p没到表头 */
  {
    q = p->next;
    free(p);
    p = q;
  }
  free(*L);
  *L = NULL;
}

/* 初始条件：L已存在。 操作结果：将L重置为空表 */
void ClearList(DuLinkList *L)
{
  DuLinkList q, p = L->next;  /*  p指向第一个结点 */  
  while(p!=L) /*  p没到表头*/
  {
    q = p->next;
    free(p);
    p = q;
  }
  L->next = L->prior = L; /*  头结点的两个指针域均指向自身 */
}

/* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
void ListEmpty(DuLinkList L)
{
  if(L->next == L && L->prior == L)
    return TRUE;
  else
    return FALSE:
}

/* 初始条件：L已存在。操作结果：返回L中数据元素个数 */
int ListLength(DuLinkList L)
{
  int ret = 0;
  DuLinkList p = L->next; /* p指向第一个结点 */
  while(p!=L)
  {
    ret++;
    p = p->next;
  }
  return ret;
}

/* 当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR */
Status GetElem(DuLinkList L, int i, ElemType *e)
{
  int j = 1;  /*  j为计数器 */
  DuLinkList p = L->next; /*  p指向第一个结点*/
  while(p!=L && j < i)
  {
    j++;
  }
  if(p == L || j > i) /*  第i个元素不存在*/
    return ERROR;
  *e = p->data;       /*  取第i个元素*/
  return OK;
}

/* 初始条件：L已存在，compare()是数据元素判定函数 */
/* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
/*           若这样的数据元素不存在，则返回值为0 */
int LocateElem(DuLinkList L, ElemType e, Status(*compare)(ElemType,ElemTyoe))
{
  int i = 0;
  DuLinkList p = L->next; /*  p指向第一个元素*/
  while(p!=L)
  {
    i++;
    if(compare(p->data,e))  /*  找到这样的数据元素 */
      return i;
    p = p->next;
  }
  return 0;
}

/* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
/*           否则操作失败，pre_e无定义 */
Status PriorElem(DuLinkList L,ElemType cur_e,ElemType *pre_e)
{ 
  DuLinkList p=L->next->next; /* p指向第2个元素 */
  while(p!=L) /* p没到表头 */
  {
    if(p->data==cur_e)
    {
      *pre_e=p->prior->data;
      return TRUE;
    }
    p=p->next;
  }
  return FALSE;
}

/* 操作结果：若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继， */
/*           否则操作失败，next_e无定义 */
Status NextElem(DuLinkList L,ElemType cur_e,ElemType *next_e)
{ 
  DuLinkList p=L->next->next; /* p指向第2个元素 */
  while(p!=L) /* p没到表头 */
  {
    if(p->prior->data==cur_e)
    {
      *next_e=p->data;
      return TRUE;
    }
    p=p->next;
  }
  return FALSE;
}


/* 在双向链表L中返回第i个元素的地址。i为0，返回头结点的地址。若第i个元素不存在，*/
/* 返回NULL */
DuLinkList GetElemP(DuLinkList L,int i) /* 另加 */
{ 
  int j;
  DuLinkList p=L; /* p指向头结点 */
  if(i<0||i>ListLength(L)) /* i值不合法 */
    return NULL;
  for(j=1;j<=i;j++)
    p=p->next;
  return p;
}

/* 在带头结点的双链循环线性表L中第i个位置之前插入元素e，i的合法值为1≤i≤表长+1 */
/* 改进算法2.18，否则无法在第表长+1个结点之前插入元素 */
Status ListInsert(DuLinkList L,int i,ElemType e)
{ 
  DuLinkList p,s;
  if(i<1||i>ListLength(L)+1) /* i值不合法 */
    return ERROR;
  p=GetElemP(L,i-1); /* 在L中确定第i个元素前驱的位置指针p */
  if(!p) /* p=NULL,即第i个元素的前驱不存在(设头结点为第1个元素的前驱) */
    return ERROR;
  s=(DuLinkList)malloc(sizeof(DuLNode));
  if(!s)
    return OVERFLOW;
  s->data=e;
  s->prior=p; /* 在第i-1个元素之后插入 */
  s->next=p->next;
  p->next->prior=s;
  p->next=s;
  return OK;
}


/* 删除带头结点的双链循环线性表L的第i个元素，i的合法值为1≤i≤表长 */
Status ListDelete(DuLinkList L,int i,ElemType *e)
{
  DuLinkList p;
  if(i<1) /* i值不合法 */
    return ERROR;
  p=GetElemP(L,i);  /* 在L中确定第i个元素的位置指针p */
  if(!p) /* p=NULL,即第i个元素不存在 */
    return ERROR;
  *e=p->data;
  p->prior->next=p->next;
  p->next->prior=p->prior;
  free(p);
  return OK;
}

/* 由双链循环线性表L的头结点出发，正序对每个数据元素调用函数visit() */
void ListTraverse(DuLinkList L,void(*visit)(ElemType))
{ 
  DuLinkList p=L->next; /* p指向头结点 */
  while(p!=L)
  {
    visit(p->data);
    p=p->next;
  }
  printf("\n");
}


/* 由双链循环线性表L的头结点出发，逆序对每个数据元素调用函数visit()。另加 */
void ListTraverseBack(DuLinkList L,void(*visit)(ElemType))
{ 
  DuLinkList p=L->prior; /* p指向尾结点 */
  while(p!=L)
  {
    visit(p->data);
    p=p->prior;
  }
  printf("\n");
}
