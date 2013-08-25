/*
  AVL with c implentation
*/

typedef enum { LEFT = 0, RIGHT = 1 } direction_t;

#define MAX(a,b)  ( (a) > (b) ? (a) : (b) )
#define MIN(a,b)  ( (a) < (b) ? (a) : (b) )

#define  OTHER_DIR(x)   direction_t( 1 - (x) )

typedef struct avl_node {
  DATA_TYPE       data;
  short           bal;
  strutc avl_node *subtree[2];
}AVLnode_t, *AVLtree_t;/* avl_node */

const AVLtree_t *AVLnull = ((AVLtree_t)NULL);

/*
 * rotate_once()  --  rotate a given node in the given direction
 *                    to restore the balance of a tree
 */
short rotate_once(AVLtree_t *rootp, direction_t dir)
{
  direction_t other_dir = OTHER_DIR(dir); /* opposite of "dir" */
  AVLtree_t old_root = *rootp;            /* copy of original root */
  short ht_unchanged;                     /* true if height unchanged */
  
  /* Here we need to take into account the special case that occurs
  ** when a single rotation was made but the HEIGHT of the rotated
  ** tree did NOT change as a result of the rotation (we will need
  ** this later)
  */
  ht_unchanged = ((*rootp)->subtree[other_dir]->bal) ? FALSE : TRUE;
  
    /* assign new root */
  *rootp = old_root->subtree[other_dir];
  
    /* new-root exchanges it's "dir" subtree for it's parent */
  old_root->subtree[other_dir] = (*rootp)->subtree[dir];
  (*rootp)->subtree[dir]       =   old_root;
  
    /* update balances */
  old_root->bal = -(dir == LEFT ? --((*rootp)->bal) : ++((*rootp)->bal));
  
   return  ht_unchanged;
  
}/* rotate_once */

/* rotate_twice()  --  rotate a given node in the given direction
 *                     and then in the opposite direction
 *                     to restore the balance of a tree
 */
void  rotate_twice(AVLtree   *rootp, direction_t  dir) 
{
  direction_t  other_dir  = OTHER_DIR(dir);
  AVLtree_t    old_root   = *rootp;
  AVLtree_t    old_other_dir_subtree = (*rootp)->subtree[other_dir];

      /* assign new root */
  *rootp = old_root->subtree[other_dir]->subtree[dir];

      /* new-root exchanges it's "dir" subtree for it's grandparent */
  old_root->subtree[other_dir]  =   (*rootp)->subtree[dir];
  (*rootp)->subtree[dir]        =   old_root;

       /* new-root exchanges it's "other-dir" subtree for it's parent */
  old_other_dir_subtree->subtree[dir] =   (*rootp)->subtree[other_dir];
  (*rootp)->subtree[other_dir]        =   old_other_dir_subtree;

        /* update balances */
  (*rootp)->subtree[LEFT]->bal   =  -MAX((*rootp)->bal, 0);
  (*rootp)->subtree[RIGHT]->bal  =  -MIN((*rootp)->bal, 0);
  (*rootp)->bal                  =  0;

}/* rotate_twice */

 /* Balance Definitions */
enum { LEFT_HEAVY = -1, BALANCED = 0, RIGHT_HEAVY = 1 };
#define  LEFT_IMBALANCE(nd)    ( (nd)->bal < LEFT_HEAVY  )
#define  RIGHT_IMBALANCE(nd)   ( (nd)->bal > RIGHT_HEAVY )

 /*
  * balance()  --  determines and performs the sequence of rotations needed
  *                (if any) to restore the balance of a given tree.
  *
  *     Returns 1 if tree height changed due to rotation; 0 otherwise
  */
  short
  balance(AVLtree_t  *rootp) {
      short  special_case = FALSE;

      if (LEFT_IMBALANCE(*rootp))  {   /* need a right rotation */
        if ((*rootp)->subtree[LEFT]->bal == RIGHT_HEAVY) {
            rotate_twice(rootp, RIGHT);   /* double RL rotation needed */
        } else {   /* single RR rotation needed */
            special_case = rotate_once(rootp, RIGHT);
        }
      } else if (RIGHT_IMBALANCE(*rootp))  {   /* need a left rotation */
        if ((*rootp)->subtree[RIGHT]->bal == LEFT_HEAVY) {
            rotate_twice(rootp, LEFT);    /* double LR rotation needed */
        } else {   /* single LL rotation needed */
            special_case = rotate_once(rootp, LEFT);
        }
      } else {
        return  HEIGHT_UNCHANGED;     /* no rotation occurred */
      }

      return  (special_case) ? HEIGHT_UNCHANGED : HEIGHT_CHANGED;
  }/* balance */
 
 /*
  * ckalloc(size) -- allocate space; check for success
  */
  void *
  ckalloc(unsigned  size) {
      void  *ptr;

      if ((ptr = malloc(size)) == NULL)  {
        fprintf(stderr, "Unable to allocate storage.");
        exit(1);
      }/* if */

      return  ptr;
  }/* ckalloc */


 /*
  * new_node() -- get space for a new node and its data;
  *               return the address of the new node
  */
  AVLtree_t
  new_node(void *data, unsigned  size) {
      AVLtree_t  root;

      root = (AVLtree_t) ckalloc(sizeof(AVLnode));
      root->data = (void *) ckalloc(size);
      memmove(root->data, data, size);
      root->bal  = BALANCED;
      root->subtree[LEFT] = root->subtree[RIGHT] = AVLnull;

      return  root;
  }/* new_node */


 /*
  * free_node()  --  free space for a node and its data!
  *                  reset the node pointer to NULL
  */
  void
  free_node(AVLtree_t  *rootp) {
      free((void *) *rootp);
      *rootp = AVLnull;
  }/* free_node */


 /*
  * node_type() -- determine the number of null pointers for a given
  *                node in an AVL tree, Returns a value of type node_t
  *                which is an enumeration type with the following
  *                values:
  *
  *     IS_TREE     --  both subtrees are non-empty
  *     IS_LBRANCH  --  left subtree is non-empty; right is empty
  *     IS_RBRANCH  --  right subtree is non-empty; left is empty
  *     IS_LEAF     --  both subtrees are empty
  *     IS_NULL     --  given tree is empty
  */
  
  typedef enum { IS_TREE, IS_LBRANCH, IS_RBRANCH, IS_LEAF, IS_NULL } node_t;
  
  node_t
  node_type(AVLtree_t  tree) {
      if (tree == AVLnull) {
        return  IS_NULL;
      } else if ((tree->subtree[LEFT]  != AVLnull) &&
                 (tree->subtree[RIGHT] != AVLnull)) {
        return  IS_TREE;
      } else if (tree->subtree[LEFT] != AVLnull) {
        return  IS_LBRANCH;
      } else if (tree->subtree[RIGHT] != AVLnull) {
        return  IS_RBRANCH;
      } else {
        return  IS_LEAF;
      }
  }/* node_type */
  
  /*
      * avl_min() -- comparator used to find the minimal element in a tree
      */
      int
      avl_min(void  *el1, void  *el2, node_t  nd_typ) {
          if ((nd_typ == IS_RBRANCH) || (nd_typ == IS_LEAF)) {
            return   0;   /* left subtree is empty -- this is the minimum */
          } else {
            return  -1;   /* keep going left */
          }
      }/* avl_min */


     /*
      * avl_max() -- comparator used to find the maximal element in a tree
      */
      int
      avl_max(void  *el1, void  *el2, node_t  nd_typ) {
          if ((nd_typ == IS_LBRANCH) || (nd_typ == IS_LEAF)) {
            return  0;   /* right subtree is empty -- this is the maximum */
          } else {
            return  1;   /* keep going right */
          }
      }/* avl_max */
      
       /*
      * avl_compare() -- compare an item with a node-item in an avl tree
      */
      int
      avl_compare(void  *el1, void  *el2, node_t  nd_typ, int (*el_cmp)(...)) {
         if ((el_cmp == avl_min) || (el_cmp == avl_max)) {
           return  (*el_cmp)(el1, el2, nd_typ);
         } else {
           return  (*el_cmp)(el1, el2);
         }
      }/* avl_compare */


/*
      * avl_insert() -- insert an item into the given tree
      *
      *   PARAMETERS:
      *       data       --  a pointer to a pointer to the data to add;
      *                      On exit, *data is NULL if insertion succeeded,
      *                      otherwise address of the duplicate key
      *       rootp      --  a pointer to an AVL tree
      *       compar     --  name of the function to compare 2 data items
      */
      short
      avl_insert(void  **data, AVLtree_t  *rootp, int (*el_cmp)(...)) {
          short increase;
          int   cmp;

          if (*rootp == AVLnull)  {  /* insert new node here */
            *rootp = new_node(*data, SIZE_OF_DATA);
            *data  = NULL;     /* set return value in data */
            return  HEIGHT_CHANGED;
          }/* if */

          cmp = (*el_cmp)(*data, (*rootp)->data);   /* compare data items */

          if (cmp < 0)  {  /* insert into the left subtree */
            increase =  -avl_insert(data, &((*rootp)->subtree[LEFT]), el_cmp);
            if (*data != NULL)  return  HEIGHT_UNCHANGED;
          } else if (cmp > 0) {  /* insert into the right subtree */
            increase =  avl_insert(data, &((*rootp)->subtree[RIGHT]), el_cmp);
            if (*data != NULL)  return  HEIGHT_UNCHANGED;
          } else  {   /* data already exists */
            *data = (*rootp)->data;   /* set return value in data */
            return  HEIGHT_UNCHANGED;
          }

          (*rootp)->bal += increase;    /* update balance factor */

        /**********************************************************************
        * re-balance if needed -- height of current tree increases only if its
        * subtree height increases and the current tree needs no rotation.
        **********************************************************************/
          if (increase  &&  (*rootp)->bal) {
            return  (1 - balance(rootp));
          } else {
            return  HEIGHT_UNCHANGED;
          }
      }/* avl_insert */


/*
      * avl_delete() -- delete an item from the given tree
      *
      *   PARAMETERS:
      *       data       --  a pointer to a pointer to the key to delete
      *                      On exit, *data points to the deleted data item
      *                      (or NULL if deletion failed).
      *       rootp      --  a pointer to an AVL tree
      *       compar     --  name of function to compare 2 data items
      */
      short
      avl_delete(void  **data, AVLtree_t  *rootp, int (*el_cmp)(...)) {
          short        decrease;
          int          cmp;
          AVLtree_t    old_root  = *rootp;
          node_t       nd_typ    = node_type(*rootp);
          direction_t  dir       = (nd_typ == IS_LBRANCH) ? LEFT : RIGHT;

          if (*rootp == AVLnull)  {  /* data not found */
            *data = NULL;    /* set return value in data */
            return  HEIGHT_UNCHANGED;
          }/* if */

             /* compare data items */
                /* NOTE the extra parameter to compare this time */
          cmp = el_cmp(*data, (*rootp)->data, nd_typ);

          if (cmp < 0)  {  /* delete from left subtree */
            decrease =  -avl_delete(data, &((*rootp)->subtree[LEFT]), el_cmp);
            if (*data == NULL)  return  HEIGHT_UNCHANGED;
          } else if (cmp > 0)  {  /* delete from right subtree */
            decrease =  avl_delete(data, &((*rootp)->subtree[RIGHT]), el_cmp);
            if (*data == NULL)  return  HEIGHT_UNCHANGED;
          } else {

        /**********************************************************************
        *  At this point we know that if "cmp" is zero then "*rootp" points to
        *  the node that we need to delete.  There are three cases:
        *
        *     1) The node is a leaf.  Remove it and return.
        *
        *     2) The node is a branch (has only 1 child). Make "*rootp"
        *        (the pointer to this node) point to the child.
        *
        *     3) The node has two children. We swap data with the successor of
        *        "*rootp" (the smallest item in its right subtree) and delete
        *        the successor from the right subtree of "*rootp".  The
        *        identifier "decrease" should be reset if the subtree height
        *        decreased due to the deletion of the successor of "rootp".
        **********************************************************************/

               /* cmp == 0 */
            *data = (*rootp)->data;  /* set return value in data */

            switch (nd_typ)  {  /* what kind of node are we removing? */
               case  IS_LEAF :
                  free_node(rootp);        /* free the leaf, its height     */
                  return  HEIGHT_CHANGED;  /* changes from 1 to 0, return 1 */

               case  IS_RBRANCH :       /* only child becomes new root */
               case  IS_LBRANCH :
                  *rootp = (*rootp)->subtree[dir];
                  free_node(&old_root);    /* free the deleted node */
                  return  HEIGHT_CHANGED;  /* just shortened "dir" subtree */

               case  IS_TREE  :
                  decrease = avl_delete(&((*rootp)->data),
                                        &((*rootp)->subtree[RIGHT]),
                                        avl_min);
            } /* switch */
          } /* else */

          (*rootp)->bal -= decrease;       /* update balance factor */

        /**********************************************************************
        * Rebalance if necessary -- the height of current tree changes if one
        * of two things happens: (1) a rotation was performed which changed
        * the height of the subtree (2) the subtree height decreased and now
        * matches the height of its other subtree (so the current tree now
        * has a zero balance when it previously did not).
        **********************************************************************/
          if (decrease && (*rootp)->bal) {    /* return 1 if height      */
            return  balance(rootp);           /* changed due to rotation */
          } else if (decrease && !(*rootp)->bal) {
                                              /* or if balance is 0 from    */
            return  HEIGHT_CHANGED;           /* height decrease of subtree */
          } else {
            return  HEIGHT_UNCHANGED;
          }
      }/* avl_delete */
