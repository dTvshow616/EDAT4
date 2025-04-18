#include "bstree.h"

#define info(pn) ((pn)->info)
#define left(pn) ((pn)->left)
#define right(pn) ((pn)->right)

#define root(pt) ((pt)->root)
#define cmp(pt) ((pt)->cmp_ele)

struct _BSTree {
  BSTNode *root;
  P_ele_print print_ele;
  P_ele_cmp cmp_ele;
};

typedef struct _BSTNode {
  void *info;
  struct BSTNode *left;
  struct BSTNode *right;
} BSTNode;

/*Privadas*/
void _bt_free_rec(BSTNode *pn);
BSTNode *_bst_insert_rec(BSTNode *pn, const void *e, int (*ele_cmp)(const void *, const void *));

BSTNode *node_new() {
  BSTNode *pn = NULL;
  pn = (BSTNode *)malloc(sizeof(BSTNode));
  if (pn == NULL) {
    return NULL;
  }
  info(pn) = left(pn) = right(pn) = NULL;
  return pn;
}

void node_free(BSTNode *node) {
  if (!node) {
    return NULL;
  }
  free(node);
}

/**
 * @brief Public function that creates a new BSTree.
 *
 * Allocates memory for the new Tree. When creating a Tree it is necessary to
 * specify the pointers to functions that:
 * - Print a Tree element.
 * - Compare two elements.
 *
 * @param print_ele Pointer to the function that prints a Tree element.
 * @param cmp_ele Pointer to the function that compares two Tree elements
 *
 * @return Returns the address of the new Tree, or NULL in case of error.
 */
BSTree *tree_init(P_ele_print print_ele, P_ele_cmp cmp_ele) {
  BSTree *pt = NULL;
  if (cmp_ele == NULL) {
    return NULL;
  }
  pt = (BSTree *)malloc(sizeof(BSTree));
  if (pt == NULL) {
    return NULL;
  }
  root(pt) = NULL;
  cmp(pt) = cmp_ele;
  return pt;
}

/**
 * @brief Public function that frees a Tree.
 *
 * Frees all the memory allocated for the Tree.
 *
 * @param tree Pointer to the Tree.
 */
void tree_destroy(BSTree *tree) {
  if (tree == NULL) {
    return;
  }
  _bt_free_rec(root(tree));
  free(tree);
}

/*Privada*/
void _bt_free_rec(BSTNode *pn) {
  if (pn == NULL) {
    return;
  }

  _bt_free_rec(left(pn));
  _bt_free_rec(right(pn));
  free(pn);
}

/**
 * @brief Public function that checks if a Tree is empty.
 *
 * Note that the return value is TRUE for a NULL Tree.
 *
 * @param tree Pointer to the Tree.
 *
 * @return Bool value TRUE if the Tree is empty or NULL, Bool value FALSE
 * otherwise.
 */
Bool tree_isEmpty(const BSTree *tree) {
  if (tree == NULL) {
    return TRUE;
  }
  if (root(tree) == NULL) {
    return TRUE;
  }
  return FALSE;
}

/**
 * @brief Public function that returns the Tree's depth.
 *
 * @param tree Pointer to the Tree.
 *
 * @return -1 if the tree is empty, its depth otherwise, -1 for a NULL Tree.
 */
int tree_depth(const BSTree *tree);

/**
 * @brief Public function that returns the Tree's size (its number of elements).
 *
 * @param tree Pointer to the Tree.
 *
 * @return 0 if the tree is empty, its size otherwise, -1 for a NULL Tree.
 */
size_t tree_size(const BSTree *tree);

/**
 * @brief Public functions that prints the content of a Tree
 * when traversed with preOrder algorithm.
 *
 * Prints all the elements in the Tree to an output stream.
 * To print an element this function calls the function specified when creating
 * the Tree, print_ele.
 *
 * Note that this function simply calls the print_ele function for each Tree
 * element, without printing any additional information. Any desired format must
 * be included in the print_ele function.
 *
 * @param f Output stream.
 * @param tree Pointer to the Tree.
 *
 * @return The sum of the return values of all the calls to print_ele if these
 * values are all positive; the first negative value encountered otherwise. If
 * the function print_ele is well constructed, this means that, upon successful
 * return, this function returns the number of characters printed, and a
 * negative value if an error occurs.
 */
int tree_preOrder(FILE *f, const BSTree *tree) {
  /* Base case: empty tree.*/
  if (bt_is_empty(tree) == TRUE) {
    return;
  }

  /*Visit of the node and recursive calls*/
  visit(tree);
  pt_preorder(left(tree));
  bt_preorder(right(tree));
}

/**
 * @brief Same as tree_preOrder but with inOrder algorithm.
 *
 * @param f Output stream.
 * @param tree Pointer to the Tree.
 *
 * @return See tree_preOrder.
 */
int tree_inOrder(FILE *f, const BSTree *tree) {
  /*Base case: empty tree*/
  if (bt_is_empty(tree) == TRUE) {
    return;
  }

  /*Visit of the node and recursive calls*/
  pt_preorder(left(tree));
  visit(tree);
  bt_preorder(right(tree));
}

/**
 * @brief Same as tree_preOrder but with postOrder algorithm.
 *
 * @param f Output stream.
 * @param tree Pointer to the Tree.
 *
 * @return See tree_preOrder.
 */
int tree_postOrder(FILE *f, const BSTree *tree) {
  /*Base case: empty tree*/
  if (bt_is_empty(tree) == TRUE) {
    return;
  }

  /*Visit of the node and recursive calls*/
  pt_preorder(left(tree));
  bt_preorder(right(tree));
  visit(tree);
}

/**
 * @brief Public function that finds the minimum element in a Binary Search
 * Tree.
 *
 * Note that it is necessary to descend the subtree to obtain the
 * minimum element. So this operation is linear with the length of the path
 * from the leaf to the root.
 *
 * @param tree Pointer to the Tree.
 *
 * @return Pointer to the minimum element if found, NULL otherwise.
 */
void *tree_find_min(BSTree *tree);

/**
 * @brief Public function that finds the maximum element in a Binary Search
 * Tree.
 *
 * Note that it is necessary to descend the subtree to obtain the
 * maximum element. So this operation is linear with the length of the path
 * from the leaf to the root.
 *
 * @param tree Pointer to the Tree.
 *
 * @return Pointer to the maximum element if found, NULL otherwise.
 */
void *tree_find_max(BSTree *tree);

/**
 * @brief Public function that tells if an element is in a Binary Search Tree.
 *
 * @param tree Pointer to the Tree.
 * @param elem Pointer to the element to be found in the Tree.
 *
 * @return Bool value TRUE if the element was found, FALSE otherwise.
 */
Bool tree_contains(BSTree *tree, const void *elem) {
  BSTNode *found = NULL;
  if ((tree == NULL) || (elem == NULL)) {
    return NULL;
  }
  found = _bst_search_rec(root(tree), elem, cmp(tree));

  return (found ? TRUE : FALSE);
}

/*Privada*/
BSTNode *_bst_search_rec(BSTNode *pn, void *e, int (*ele_cmp)(const void *, const void *)) {
  int cmp = 0;
  if (pn == NULL) {
    return NULL;
  }
  cmp = ele_cmp(e, info(pn));
  if (cmp == 0) {
    return pn;
  }
  if (cmp < 0) {
    return _bst_search_rec(left(pn), e, ele_cmp);
  }
  return _bst_search_rec(right(pn), e, ele_cmp);
}

/**
 * @brief Public function that inserts an element into a Binary Search Tree.
 *
 * Inserts as a leaf the pointer of the element received as argument. If the
 * element is already in the BST it returns OK.
 *
 * Note that it is necessary to descend the subtree to obtain the
 * insert position. So this operation is linear with the length of the path
 * from the leaf to the root.
 *
 * @param tree Pointer to the Tree.
 * @param elem Pointer to the element to be inserted into the Tree.
 *
 * @return Status value OK if the insertion could be done or the element was
 * already in the BST, Status value ERROR otherwise.
 */
Status tree_insert(BSTree *tree, const void *elem) {
  BSTNode *root;
  if ((tree == NULL) || (elem == NULL)) {
    return ERROR;
  }
  root = _bst_insert_rec(root(tree), elem, cmp(tree));
  if (root == NULL) {
    return ERROR;
  }
  root(tree) = root;
  return OK;
}

/*Privada*/
BSTNode *_bst_insert_rec(BSTNode *pn, const void *e, int (*ele_cmp)(const void *, const void *)) {
  int cmp;
  if (pn == NULL) {
    pn = node_new();
    if (pn == NULL) {
      return NULL;
    }
    info(pn) = (void *)e;
    return pn;
  }
  cmp = ele_cmp(e, info(pn));
  if (cmp < 0) {
    left(pn) = _bst_insert_rec(left(pn), e, ele_cmp);
  } else if (cmp > 0) {
    right(pn) = _bst_insert_rec(right(pn), e, ele_cmp);
  }
  return pn;
}

/**
 * @brief Public function that removes an element into a Binary Search Tree.
 *
 * Removes the (first) occurrence of the element received as argument.
 *
 * Note that it is necessary to descend the subtree to obtain the
 * remove position. So this operation is linear with the length of the path
 * from the leaf to the root.
 *
 * @param tree Pointer to the Tree.
 * @param elem Pointer to the element to be removed from the Tree.
 *
 * @return Status value OK if the removal could be done or the element was not
 * in the BST, Status value ERROR otherwise.
 */
Status tree_remove(BSTree *tree, const void *elem);

/*tree_find_min: devuelve el elemento más pequeño almacenado en el árbol.
 tree_find_max: devuelve el elemento más grande almacenado en el árbol.
 tree_contains: comprueba si un elemento existe en el árbol.
 tree_insert: inserta un nuevo elemento en el árbol (si el elemento ya se encuentra
en el árbol no se debe insertar, pero la función devolverá OK).*/

void *tree_find_min(); /*TODO - */
void *tree_find_max(); /*TODO - */
Bool tree_contains();  /*TODO - */
Status tree_insert();  /*TODO - */
