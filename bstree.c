#include "bstree.h"

#include <stdio.h>
#include <stdlib.h>

#include "vertex.h"

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

P_ele_print *bst_get_print(BSTree *tree) {
  /*REVIEW - La he metido yo para el e3*/
  if (!tree) {
    return NULL;
  }

  return &(tree->print_ele);
}

P_ele_cmp *bst_get_cmp(BSTree *tree) {
  /*REVIEW - La he metido yo para el e3*/
  if (!tree) {
    return NULL;
  }

  return &(tree->cmp_ele);
}

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
  /*REVIEW - p4_e1a*/
  if (!pn || !left(pn)) {
    return pn;
  }

  return _bst_find_min_rec(left(pn));
}

BSTNode *_bst_find_max_rec(BSTNode *pn) {
  /*REVIEW - p4_e1a*/
  if (!pn || !right(pn)) {
    return pn;
  }

  return _bst_find_max_rec(right(pn));
}

Bool _bst_contains_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_elem) {
  /*REVIEW - p4_e1a*/
  int cmp;
  if (!pn) {
    return FALSE;
  }

  cmp = cmp_elem(info(pn), elem);

  if (cmp == 0) {
    printf("-----FOUND IT!!\n");
    return TRUE;
  } else if (cmp > 0) {
    /*El elemento es mayor que el buscado*/
    return _bst_contains_rec(right(pn), elem, cmp_elem);
  } else if (cmp < 0) {
    /*El elemento es menor que el buscado*/
    return _bst_contains_rec(left(pn), elem, cmp_elem);
  }

  return FALSE;
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
 * @return Status value OK if the insertion could be done or the element was
 * already in the BST, Status value ERROR otherwise.
 */
/*a
b   c
    d e*/
BSTNode *_bst_insert_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_elem) {
  /*REVIEW - p4_e1a*/
  BSTNode *new_node = NULL;
  int cmp;

  /*If the tree is empty, return a new node*/
  if (!pn) {
    new_node = _bst_node_new();
    if (!new_node) {
      return NULL;
    }
    new_node->info = (void *)elem;
    return new_node;
  }

  cmp = cmp_elem(pn->info, elem);

  /*If the key is already present in the tree, return the node*/
  if (cmp == 0) {
    return pn;
  } else if (cmp < 0) {
    /*Otherwise, recur down the tree. If the key to be inserted is greater than the node's key, insert it in the right subtree*/
    pn->right = _bst_insert_rec(pn->right, elem, cmp_elem);

  } else {
    /*If the key to be inserted is smaller than the node's key,insert it in the left subtree*/
    pn->left = _bst_insert_rec(pn->left, elem, cmp_elem);
  }

  /*Return the (unchanged) node pointer*/
  return pn;
}

/*Lo primero que hará será comparar el elemento recibido con el campo info del nodo, usando la función de comparación. Si el elemento que se busca es
  menor que el que tiene el nodo continuará buscando en su subárbol izquierdo, y si es mayor en el subárbol derecho. En caso de que el elemento
  buscado esté en el nodo actual habrá que eliminarlo, y se dan tres posibles situaciones:
  - Si el nodo no tiene ningún hijo simplemente se libera.
  - Si tiene solo un hijo, ya sea izquierdo o derecho, se libera el nodo y se deja en su lugar a su hijo.
  - En caso de tener dos hijos, hay que reemplazarlo por el siguiente elemento más grande, que será siempre el elemento mínimo del subárbol derecho
  (el elemento más pequeño del subárbol en el que todos los elementos son mayores que el elemento actual). Una vez reemplazado, se elimina el elemento
  del subárbol derecho, ya que ha cambiado de posición. En cualquiera de los casos, la función devolverá un puntero al nodo que se quedará en esa
  posición del árbol, ya sea el nodo original, uno de sus hijos, o NULL si la posición queda vacía.
  A continuación,*/
BSTNode *_bst_remove_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_elem) {
  /*REVIEW - p4_e1b*/
  int cmp;
  BSTNode *ret_node, *aux_node;
  if (!pn) {
    return NULL;
  }

  cmp = cmp_elem(elem, info(pn));
  /*Comparación de elem con la información del nodo actual*/
  if (cmp < 0) {
    /*Buscar en el subárbol izquierdo*/
    left(pn) = _bst_remove_rec(left(pn), elem, cmp_elem);

  } else if (cmp > 0) {
    /*Buscar en el subárbol derecho*/
    right(pn) = _bst_remove_rec(right(pn), elem, cmp_elem);

  } else if (cmp == 0) {
    /*Se ha encontrado el elemento que se va a eliminar*/
    if (!right(pn) && !left(pn)) {
      _bst_node_free(pn);
      return NULL;

    } else if (right(pn) && !left(pn)) {
      ret_node = right(pn);
      _bst_node_free(pn);
      return ret_node;

    } else if (!right(pn) && left(pn)) {
      ret_node = left(pn);
      _bst_node_free(pn);
      return ret_node;

    } else if (right(pn) && left(pn)) {
      /*Se libera pn y se reemplaza por el mínimo el subárbol derecho, que se elimina de su posición actual*/
      aux_node = _bst_find_min_rec(right(pn));
      info(pn) = info(aux_node);
      right(pn) = _bst_remove_rec(right(pn), info(aux_node), cmp_elem);
      return pn;
    }
  }

  return pn;
}

/**
 * @brief Public function that finds the minimum element in a Binary Search Tree.
 */
void *tree_find_min(BSTree *tree) {
  /*REVIEW - p4_e1a*/
  BSTNode *node;
  if (!tree || !root(tree)) {
    return NULL;
  }
  /*Podemos usar recursión pero no hace falta*/
  node = root(tree);
  /*Nos vamos a left pq nuestro arbol tiene el min a la izq*/
  while (left(node)) {
    node = left(node);
  }

  return info(node);
}

/**
 * @brief Public function that finds the maximum element in a Binary Search Tree.
 */
void *tree_find_max(BSTree *tree) {
  /*REVIEW - p4_e1a*/
  BSTNode *node;
  if (!tree || !root(tree)) {
    return NULL;
  }
  /*Podemos usar recursión pero no hace falta*/
  node = root(tree);
  /*Nos vamos a right pq nuestro arbol tiene el max a la dch*/
  while (right(node)) {
    node = right(node);
  }

  return info(node);
}

/**
 * @brief Public function that tells if an element is in a Binary Search Tree.
 *
 * @param tree Pointer to the Tree.
 * @param elem Pointer to the element to be found in the Tree.
 *
 * @return Bool value TRUE if the element was found, FALSE otherwise.
 */
Bool tree_contains(BSTree *tree, const void *elem) {
  /*REVIEW - p4_e1a*/
  if (!tree || !elem || !cmp(tree)) {
    return FALSE;
  }

  return _bst_contains_rec(root(tree), elem, cmp(tree));
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
  /*REVIEW - p4_e1a*/
  BSTNode *new_root;

  if (!tree || !elem) {
    return ERROR;
  }

  new_root = _bst_insert_rec(root(tree), elem, cmp(tree));

  if (!new_root) {
    return ERROR;
  }

  root(tree) = new_root;
  return OK;
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
Status tree_remove(BSTree *tree, const void *elem) {
  /*REVIEW - p4_e1b*/
  if (!tree || (tree_isEmpty(tree) == TRUE)) {
    return OK;
  }

  _bst_remove_rec(root(tree), elem, cmp(tree));
  return OK;
}

/*Me las he hecho pensando que hacían falta :/*/
/*Bool bt_is_always_right(BSTree *tree) {

  if (!tree) {
    return TRUE;
  }

  return bt_is_always_right_rec(root(tree));
}

Bool bt_is_always_right_rec(BSTNode *node) {

  if (!right(node) && !left(node)) {
    return TRUE;
  } else if (left(node)) {
    return FALSE;
  }
  return bt_is_always_right_rec(right(node));
}

Bool bt_is_always_left(BSTree *tree) {

  if (!tree) {
    return TRUE;
  }

  return bt_is_always_left_rec(root(tree));
}

Bool bt_is_always_left_rec(BSTNode *node) {

  if (!right(node) && !left(node)) {
    return TRUE;
  } else if (left(node)) {
    return FALSE;
  }
  return bt_is_always_left_rec(right(node));
}*/