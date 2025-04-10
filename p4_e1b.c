#include "bstree.h"
/*Se pide implementar la primitiva pública del TAD BST tree_remove para eliminar un elemento del árbol, cuya declaración se encuentra en bstree.h.

Para ello hay que implementar también la función privada recursiva _bst_remove_rec. Al igual que el resto de funciones privadas recursivas de BST,
esta tendrá que recibir como argumento o bien el árbol (para poder acceder a las funciones que necesite), o bien directamente los punteros a función
que requiera.

En este caso, se aconseja diseñarlo de la segunda forma, de manera que _bst_remove_rec reciba como argumentos un puntero al nodo desde
el que arrancará la búsqueda, un puntero al elemento que se está buscando (para ser eliminado) y un puntero a la función de comparación. Lo primero
que hará será comparar el elemento recibido con el campo info del nodo, usando la función de comparación. Si el elemento que se busca es menor que el
que tiene el nodo continuará buscando en su subárbol izquierdo, y si es mayor en el subárbol derecho.

En caso de que el elemento buscado esté en el
nodo actual habrá que eliminarlo, y se dan tres posibles situaciones:  Si el nodo no tiene ningún hijo simplemente se libera.  Si tiene solo
un hijo, ya sea izquierdo o derecho, se libera el nodo y se deja en su lugar a su hijo.  En caso de tener dos hijos, hay que reemplazarlo por el
siguiente elemento más grande, que será siempre el elemento mínimo del subárbol derecho (el elemento más pequeño del subárbol en el que todos los
elementos son mayores que el elemento actual). Una vez reemplazado, se elimina el elemento del subárbol derecho, ya que ha cambiado de posición.

En cualquiera de los casos, la función devolverá un puntero al nodo que se quedará en esa posición del árbol, ya sea el nodo original, uno de sus
hijos, o NULL si la posición queda vacía. A continuación, se proporciona un pseudocódigo para la función privada recursiva _bst_remove_rec:

*/

_bst_remove_rec(BSTree* pn, void* elem, f(cmp_elem)) {
  if (!pn) {
    return NULL;
  }

  /*Comparación de elem con la información del nodo actual*/
  if (elem < pn.info) {
    /*Buscar en el subárbol izquierdo*/
    pn.left = _bst_remove_rec(pn.left, elem, cmp_elem);

  } else if (elem > pn.info) {
    /*Buscar en el subárbol derecho*/
    pn.right = _bst_remove_rec(pn.right, elem, cmp_elem);
  } else if (elem == pn.info) {
    /*Se ha encontrado el elemento que se va a eliminar*/
  }
  if (/*Tree has no sons*/) {
    _bst_node_free(pn);
    return NULL;
  } else if (/*Tree only has right sons*/) {
    ret_node = pn.right;
    _bst_node_free(pn);
    return ret_node;
  } else if (/*Tree only has left sons*/) {
    ret_node = pn.left;
    _bst_node_free(pn);
    return ret_node;
  } else if (/*Tree has left and right sons*/) {
    /*Se libera pn y se reemplaza por el mínimo el subárbol derecho, que se elimina de su posición actual*/
    aux_node = _bst_find_min_rec(pn.right);
    pn.info = auz_node.info;
    pn.right = _bst_remove_rec(pn.right, aux_node.info, cmp_elem);
    return pn;
  }
  return pn;
}