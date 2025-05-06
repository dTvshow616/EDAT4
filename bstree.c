#include "bstree.h"

#include <stdio.h>
#include <stdlib.h>

#define info(pn) ((pn)->info)
#define left(pn) ((pn)->left)
#define right(pn) ((pn)->right)

#define root(pt) ((pt)->root)
#define cmp(pt) ((pt)->cmp_ele)

/* START [_BSTNode] */
typedef struct _BSTNode {
  void *info;
  struct _BSTNode *left;
  struct _BSTNode *right;
} BSTNode;
/* END [_BSTNode] */

/* START [_BSTree] */
struct _BSTree {
  BSTNode *root;
  P_ele_print print_ele;
  P_ele_cmp cmp_ele;
};
/* END [_BSTree] */

/*** BSTNode TAD private functions ***/
BSTNode *_bst_node_new() {
  BSTNode *pn = NULL;

  pn = malloc(sizeof(BSTNode));
  if (!pn) {
    return NULL;
  }

  pn->left = NULL;
  pn->right = NULL;
  pn->info = NULL;

  return pn;
}

void _bst_node_free(BSTNode *pn) {
  if (!pn) {
    return;
  }

  free(pn);
}

void _bst_node_free_rec(BSTNode *pn) {
  if (!pn) {
    return;
  }

  _bst_node_free_rec(pn->left);
  _bst_node_free_rec(pn->right);
  _bst_node_free(pn);

  return;
}

int _bst_depth_rec(BSTNode *pn) {
  int depth_l, depth_r;

  if (!pn) {
    return 0;
  }

  depth_l = _bst_depth_rec(pn->left);
  depth_r = _bst_depth_rec(pn->right);

  if (depth_r > depth_l) {
    return depth_r + 1;
  } else {
    return depth_l + 1;
  }
}

int _bst_size_rec(BSTNode *pn) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_size_rec(pn->left);
  count += _bst_size_rec(pn->right);

  return count + 1;
}

int _bst_preOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += print_ele(pf, pn->info);
  count += _bst_preOrder_rec(pn->left, pf, print_ele);
  count += _bst_preOrder_rec(pn->right, pf, print_ele);

  return count;
}

int _bst_inOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_inOrder_rec(pn->left, pf, print_ele);
  count += print_ele(pf, pn->info);
  count += _bst_inOrder_rec(pn->right, pf, print_ele);

  return count;
}

int _bst_postOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele) {
  int count = 0;

  if (!pn) {
    return count;
  }

  count += _bst_postOrder_rec(pn->left, pf, print_ele);
  count += _bst_postOrder_rec(pn->right, pf, print_ele);
  count += print_ele(pf, pn->info);

  return count;
}

/*** BSTree TAD functions ***/
BSTree *tree_init(P_ele_print print_ele, P_ele_cmp cmp_ele) {
  BSTree *tree;

  if (!print_ele || !cmp_ele) {
    return NULL;
  }

  tree = malloc(sizeof(BSTree));
  if (!tree) {
    return NULL;
  }

  tree->root = NULL;
  tree->print_ele = print_ele;
  tree->cmp_ele = cmp_ele;

  return tree;
}

void tree_destroy(BSTree *tree) {
  if (!tree) {
    return;
  }

  _bst_node_free_rec(tree->root);
  free(tree);

  return;
}

Bool tree_isEmpty(const BSTree *tree) {
  if (!tree || !tree->root) {
    return TRUE;
  }
  return FALSE;
}

int tree_depth(const BSTree *tree) {
  if (!tree) {
    return -1;
  }

  return _bst_depth_rec(tree->root);
}

size_t tree_size(const BSTree *tree) {
  if (!tree) {
    return -1;
  }

  return _bst_size_rec(tree->root);
}

int tree_preOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_preOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_inOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_inOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_postOrder(FILE *f, const BSTree *tree) {
  if (!f || !tree) {
    return -1;
  }

  return _bst_postOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

/**** TODO: find_min, find_max, insert, contains, remove ****/
BSTNode *_bst_find_min_rec(BSTNode *pn) {
  /*TODO - */
  while (left(pn)) {
    pn = left(pn);
  }

  return info(pn);
}

BSTNode *_bst_find_max_rec(BSTNode *pn) {
  /*TODO - */
  while (right(pn)) {
    pn = right(pn);
  }

  return pn;
}

Bool _bst_contains_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_elem) {
  int cmp, depth;
  if (!pn) {
    return FALSE;
  }

  cmp = cmp_ele(info(pn), elem);

  if (cmp == 0) {
    return TRUE;
  } else if (cmp > 0) {
    /*El elemento es mayor que el buscado*/
    tree_contains_recursive(right(pn), elem, cmp_ele);
  } else {
    /*El elemento es menor que el buscado*/
    tree_contains_recursive(left(pn), elem, cmp_ele);
  }

  return FALSE;
}

BSTNode *_bst_insert_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_elem) {
  /*REVIEW - */
  int cmp;
  if (pn == NULL) {
    pn = node_new();
    if (pn == NULL) {
      return NULL;
    }

    info(pn) = (void *)elem;

    return pn;
  }

  cmp = ele_cmp(elem, info(pn));

  if (cmp < 0) {
    left(pn) = _bst_insert_rec(left(pn), elem, ele_cmp);
  } else if (cmp > 0) {
    right(pn) = _bst_insert_rec(right(pn), elem, ele_cmp);
  }

  return pn;
}

BSTNode *_bst_remove_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_elem) { /*REVIEW - Esta función la he metido yo*/ /*TODO - */ }

void *tree_find_min(BSTree *tree) {
  /*REVIEW - */
  BSTNode *node;
  /*Podemos usar recursión pero no hace falta*/
  /*Falta CdE*/

  node = root(tree);
  /*Nos vamos a left pq nuestro arbol tiene el min a la izq*/
  while (left(node)) {
    node = left(node);
  }

  return info(node);
}

void *tree_find_max(BSTree *tree) {
  /*REVIEW - */
  BSTNode *node;
  /*Podemos usar recursión pero no hace falta*/
  /*Falta CdE*/

  node = root(tree);
  /*Nos vamos a left pq nuestro arbol tiene el min a la izq*/
  while (right(node)) {
    node = right(node);
  }

  return info(node);
}

Bool tree_contains(BSTree *tree, const void *elem) {
  /*REVIEW - */
  P_ele_cmp *cmp_ele;

  return _bst_remove_rec(root(tree), elem, cmp_ele);
}

Status tree_insert(BSTree *tree, const void *elem) {
  /*REVIEW - */
  P_ele_cmp *cmp_ele;

  _bst_insert_rec(root(tree), elem, cmp_ele);
  return OK;
}

Status tree_remove(BSTree *tree, const void *elem) { /*TODO - */ }