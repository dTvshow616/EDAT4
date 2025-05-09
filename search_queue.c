#include "search_queue.h"

#include <stdlib.h>

#include "bstree.h"

struct _SearchQueue {
  BSTree *data;
};

Status search_queue_remove(SearchQueue *search_queue, void *ele) {
  /*REVIEW - La he hecho para el e3*/
  if (!search_queue || !ele) {
    return ERROR;
  }

  return tree_remove(search_queue->data, ele);
}

float search_queue_get_median(SearchQueue *search_queue) {
  /*REVIEW - */
  if (!search_queue) {
    return -1;
  }

  return tree_get_median(search_queue->data);
}

/* START [_queue_new] */
/**
 * @brief This function creates and initializes a SearchQueue.
 *
 * Allocates memory for the new SearchQueue. When creating a SearchQueue it is
 * necessary to specify the pointers to functions that:
 * - Print an element.
 * - Compare two elements
 *
 * @param print_ele Pointer to the function that prints a SearchQueue element.
 * @param cmp_ele Pointer to a function that compare two SearchQueue elements
 *
 * @return A pointer to the SearchQueue if it could be created or NULL in case
 * of error.
 */
SearchQueue *search_queue_new(P_ele_print print_ele, P_ele_cmp cmp_ele) {
  /*REVIEW - */
  SearchQueue *new_search_queue = NULL;

  new_search_queue = (SearchQueue *)calloc(1, sizeof(SearchQueue));
  if (!new_search_queue) {
    return NULL;
  }

  new_search_queue->data = tree_init(print_ele, cmp_ele);
  if (!(new_search_queue->data)) {
    return NULL;
  }

  return new_search_queue;
}
/* END [_queue_new] */

/**
 * @brief This function frees the memory used by the SearchQueue, but not the
 * elements that it may contain.
 *
 * @param q A pointer to the queue to be freed.
 *  */
void search_queue_free(SearchQueue *q) {
  /*REVIEW - */
  if (!q) {
    return;
  }

  tree_destroy(q->data);
  free(q);
  q = NULL;
}

/**
 * @brief Checks whether the SearchQueue is empty or not.
 *
 * @param q A pointer to the SearchQueue.
 *
 * @return TRUE if the SearchQueue is empty, FALSE if it is not.
 */
Bool search_queue_isEmpty(const SearchQueue *q) {
  /*REVIEW - */
  if (!q) {
    return TRUE;
  }

  return tree_isEmpty(q->data);
}

Bool w_search_queue_isEmpty(const void *tad) {
  /*REVIEW - es para read_tad_from_file*/
  return search_queue_isEmpty(tad);
}

/**
 * @brief This function is used to insert an element at the back position of a
 * SearchQueue. A reference to the element is added.
 *
 * @param q A pointer to the SearchQueue.
 * @param ele A pointer to the element to be inserted.
 *
 * @return OK on success, ERROR otherwise.
 *  */
Status search_queue_push(SearchQueue *q, void *ele) {
  /*REVIEW - */
  if (!q || !ele) {
    return ERROR;
  }

  return tree_insert(q->data, ele);
}

Status w_search_queue_push(void *tad, const void *ele) {
  /*REVIEW - es para read_tad_from_file*/
  return search_queue_push(tad, (void *)ele);
}

/**
 * @brief This function is used to extract an element from the front position of
 * a SearchQueue. In particular, it will always return the smallest element
 * according to the comparison function passed in search_queue_new.
 *
 * @param q pointer to the SearchQueue.
 *
 * @return A pointer to the extracted element on success, NULL in case of error.
 * */
void *search_queue_pop(SearchQueue *q) {
  void *ele = NULL;
  /*REVIEW - */
  if (!q) {
    return NULL;
  }

  ele = tree_find_min(q->data);
  if (!ele) {
    return NULL;
  }

  if (tree_remove(q->data, ele) == ERROR) {
    return NULL;
  }

  return ele;
}

/**
 * @brief This function is used to get a reference to the element in the front
 * position of a SearchQueue; this element should correspond with the smallest
 * element according to the comparison function passed in search_queue_new.
 *
 * @param q A pointer to the SearchQueue.
 *
 * @return A pointer to the element in the front position, NULL in case of
 * error.
 * */
void *search_queue_getFront(const SearchQueue *q) {
  /*REVIEW - */
  if (!q) {
    return NULL;
  }

  return tree_find_min(q->data);
}

/**
 * @brief This function is used to get a reference to the element in the back
 * position of a SearchQueue; this element should correspond with the largest
 * element according to the comparison function passed in search_queue_new.
 *
 * @param q A pointer to the SearchQueue.
 *
 * @return A pointer to the element in the back position, NULL in case of error.
 * */
void *search_queue_getBack(const SearchQueue *q) {
  /*REVIEW - */
  if (!q) {
    return NULL;
  }

  return tree_find_max(q->data);
}

/**
 * @brief This function returns the size of a SearchQueue. Note that the
 * function returns 0 if it is called with a NULL pointer.
 *
 * @param q A pointer to the SearchQueue.
 *
 * @return The SearchQueue size, 0 in case of error.
 */
size_t search_queue_size(const SearchQueue *q) {
  /*REVIEW - */
  if (!q || (!q->data)) {
    return 0;
  }

  return tree_size(q->data);
}

/**
 * @brief This function prints the SearchQueue content to an output stream.
 *
 * @param fp A pointer to the stream.
 * @param q A pointer to the SearchQueue to be printed.
 *
 * @return On success this function returns the number of characters printed. In
 * case of error it returns a negative value.
 *  */
int search_queue_print(FILE *fp, const SearchQueue *q) {
  /*TODO - */
  int chars_printed = 0;
  if (!fp || !q) {
    return -1;
  }

  return chars_printed;
}

/* REVIEW - La he hecho para el ej 3*/
float search_queue_get_tree_nodes_sum(SearchQueue *q) {
  if (!q) {
    return 0;
  }

  /* El casting raro de *(int*) es pq info es un puntero void* */
  return tree_sum_nodes(q->data);
}
