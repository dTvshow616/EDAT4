#include "bstree.h"
#include "file_utils.h"

/*Se pide implementar la primitiva pública del TAD BST tree_remove para eliminar un elemento del árbol, cuya declaración se encuentra en bstree.h.

Para ello hay que implementar también la función privada recursiva _bst_remove_rec. Al igual que el resto de funciones privadas recursivas de BST,
esta tendrá que recibir como argumento o bien el árbol (para poder acceder a las funciones que necesite), o bien directamente los punteros a función
que requiera.

En este caso, se aconseja diseñarlo de la segunda forma, de manera que _bst_remove_rec reciba como argumentos un puntero al nodo desde el que
arrancará la búsqueda, un puntero al elemento que se está buscando (para ser eliminado) y un puntero a la función de comparación. Lo primero que hará
será comparar el elemento recibido con el campo info del nodo, usando la función de comparación. Si el elemento que se busca es menor que el que tiene
el nodo continuará buscando en su subárbol izquierdo, y si es mayor en el subárbol derecho.

En caso de que el elemento buscado esté en el nodo actual habrá que eliminarlo, y se dan tres posibles situaciones:  Si el nodo no tiene ningún
hijo simplemente se libera.  Si tiene solo un hijo, ya sea izquierdo o derecho, se libera el nodo y se deja en su lugar a su hijo.  En caso de
tener dos hijos, hay que reemplazarlo por el siguiente elemento más grande, que será siempre el elemento mínimo del subárbol derecho (el elemento más
pequeño del subárbol en el que todos los elementos son mayores que el elemento actual). Una vez reemplazado, se elimina el elemento del subárbol
derecho, ya que ha cambiado de posición.

En cualquiera de los casos, la función devolverá un puntero al nodo que se quedará en esa posición del árbol, ya sea el nodo original, uno de sus
hijos, o NULL si la posición queda vacía. A continuación, se proporciona un pseudocódigo para la función privada recursiva _bst_remove_rec:
*/

Bool bt_is_always_right(BSTree *tree);
Bool bt_is_always_right_rec(BSTNode *node);
Bool bt_is_always_left(BSTree *tree);
Bool bt_is_always_left_rec(BSTNode *node);

int main(int argc, char const *argv[]) {
  P_ele_cmp *cmp_ele;
  BSTree *tree;
  void *elem;

  _bst_remove_rec(tree, elem, cmp_ele);
}

_bst_remove_rec(BSTree *pn, void *elem, int (*cmp_ele)(const void *, const void *)) {
  BSTNode *ret_node, *aux_node;
  if (!pn) {
    return NULL;
  }
  /*Comparación de elem con la información del nodo actual*/
  if (elem < pn->root->info) {
    /*Buscar en el subárbol izquierdo*/
    pn->root->left = _bst_remove_rec(pn->root->left, elem, cmp_ele);

  } else if (elem > pn->root->info) {
    /*Buscar en el subárbol derecho*/
    pn->root->right = _bst_remove_rec(pn->root->right, elem, cmp_ele);
  } else if (elem == pn->root->info) {
    /*Se ha encontrado el elemento que se va a eliminar*/
  }

  if (tree_depth(pn) == 0) {
    node_free(pn);
    return NULL;
  } else if (bt_is_always_right(pn) == TRUE) {
    ret_node = pn->root->right;
    node_free(pn);
    return ret_node;
  } else if (bt_is_always_left(pn) == TRUE) {
    ret_node = pn->root->left;
    _bst_node_free(pn);
    return ret_node;
  } else if ((bt_is_always_right(pn) == FALSE) && (bt_is_always_right(pn) == FALSE) && (tree_isEmpty(pn) == FALSE)) {
    /*Se libera pn y se reemplaza por el mínimo el subárbol derecho, que se elimina de su posición actual*/
    aux_node = tree_find_min_rec(pn->root->right);
    pn->root->info = aux_node->info;
    pn->root->right = _bst_remove_rec(pn->root->right, aux_node->info, cmp_ele);
    return pn;
  }

  return pn;
}

Bool bt_is_always_right(BSTree *tree) {
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
}