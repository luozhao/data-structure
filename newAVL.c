/*
  the struct of the AVL tree
*/
typedef struct node {
  int data;
  struct node *lchild;
  struct node *rchild;
  int height;
} AVLnode;

/*
  destroy the AVL tree
*/
void dispose(AVLnode *node)
{
  if(!node)
     return;
  dispose(node->lchild);
  dispose(node->rchild);
  free(node);
}

/*
  search a specifc node in the AVL tree
*/
AVLnode *search(int e, AVLnode *node)
{
  if(!node)
    return NULL;
  if(e == node->data)
    return node;
  if(e < node->data)
    return search(node->lchild,e);
  else
    return search(node->rchild,e);
}

/*
  find the maximum node in the AVL tree
*/
AVLnode *max_node(const AVLnode *node)
{
  if(!node)
    return NULL;
  while(node->rchild)
    node = node->rchild;
  
  return (AVLnode*)node;
}

/*
  find the minmum node in the AVL tree
*/
AVLnode *min_node(const AVLnode *node)
{
  if(!node)
    return NULL;
  while(node->lchild)
    node = node->lchild;
  
  return (AVLnode*)node;
}

/*
  get the height of specific node
*/
static int height(AVLnode *node)
{
  if(NULL == node)
    return -1;
  else 
    return node->height;
}

/*
  get the maximu of two integers
*/
static int max(int m, int n)
{
  return m > n ? m : n;
}

//接下来是AVL树的集中旋转操作

/*
  case1.single rotate with left
*/
static AVLnode *single_left(AVLnode *t)
{
  AVLnode *p = NULL;
  if(!t)
    return NULL;
  p = t->lchild;
  t->lchild = p->rchild;
  p->rchild = t;
  
  t->height = max(height(t->lchild),height(t->rchild)) + 1;
  p->height = max(height(p->lchild),t->height) + 1;
  
  return p; // the new root
}

/*
  case2.single rotate with right
*/
static AVLnode *single_right(AVLnode *t)
{
  AVLnode *p = NULL;
  if(!t)
    return NULL;
  p = t->rchild;
  t->rchild = p->lchild;
  p->lchild = t;
  
  t->height = max(height(t->lchild),height(t->rchild)) + 1;
  p->height = max(height(p->rchild),t->height) + 1;
  
  return p; // the new root
}

/*
  case3.left-right double rotation
  call double_left only if t node has
  a left child and t's left child has a right child
*/
static double_left(AVLnode *t)
{
  if(!t)
    return NULL;
  t->lchild  = single_right(t->lchild);
  
  return single_left(t);
}

/*
  case4. right-left double rotation
   call double_rotate_with_right only if t has a
   right child and t's right child has a left child
*/
static double_right(AVLnode *t)
{
  if(!t)
    return NULL;
  
  t->rchild = single_left(t->rchild);
  
  return single_right(t);
}

/*
  insert a new node into the AVL tree
*/
AVLnode *insert(int e, AVLnode *node)
{
  if(!node)
  {
    //create and return a one-node AVL tree
    node = (AVLnode*)malloc(sizeof(AVLnode));
    if(!node)
    {
      fprintf(stderr,"Allocate memory error!");
      exit(1);
    }
    node->data    = e;
    node->height  = 0;
    node->lchild  = node->rchild = NULL;
  }
  else if(e < node->data)
  {
    node->lchild = insert(e,node->lchild);
    if(height(node->lchild) - height(node->rchild) == 2)
    {
      if(e < node->lchild->data)
        node = single_left(node);
      else
        node = double_left(node);
    }
  } else if(e > node->data)
  {
    node->rchild = insert(e, node->rchild);
    if(height(node->rchild) - height(node->lchild) == 2)
    {
      if(e > node->rchild->data)
        node = single_right(node);
      else
        node = double_right(node);
    }
  }
  //else the node is in the AVL tree already,we do nothing
  node->height = max(height(node->lchild),height(node->rchild)) + 1;
  return node;
}

/*
  remove a node in the AVL tree 
*/
AVLnode *delete(int e, AVLnode *node)
{
  
  return node;
}

/*
  get the data of the specific node
*/
int get_data(AVLnode *node)
{
  if(!node)
    exit(1);
  return node->data;
}

/*
  display the AVL tree
*/
void display(AVLnode *node)
{
  if(!node)
    return;
  printf("%d ",node->data);
  
  if(node->lchild)
    printf("%d ", node->lchild->data);
  if(node->rchild)
    printf("%d ", node->rchild->data);
  
  printf("\n");
  display(node->lchild);
  display(node->rchild);
}

