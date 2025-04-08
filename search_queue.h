#ifndef SEARCHQUEUE_H
#define SEARCHQUEUE_H

#include <stdio.h>

#include "types.h"

/**
 * @brief Data type to declare a SearchQueue variable.
 *
 **/
typedef struct _SearchQueue SearchQueue;

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
SearchQueue *search_queue_new(P_ele_print print_ele, P_ele_cmp cmp_ele);
/* END [_queue_new] */

/**
 * @brief This function frees the memory used by the SearchQueue, but not the
 * elements that it may contain.
 *
 * @param q A pointer to the queue to be freed.
 *  */
void search_queue_free(SearchQueue *q);

/**
 * @brief Checks whether the SearchQueue is empty or not.
 *
 * @param q A pointer to the SearchQueue.
 *
 * @return TRUE if the SearchQueue is empty, FALSE if it is not.
 */
Bool search_queue_isEmpty(const SearchQueue *q);

/**
 * @brief This function is used to insert an element at the back position of a
 * SearchQueue. A reference to the element is added.
 *
 * @param q A pointer to the SearchQueue.
 * @param ele A pointer to the element to be inserted.
 *
 * @return OK on success, ERROR otherwise.
 *  */
Status search_queue_push(SearchQueue *q, void *ele);

/**
 * @brief This function is used to extract an element from the front position of
 * a SearchQueue. In particular, it will always return the smallest element
 * according to the comparison function passed in search_queue_new.
 *
 * @param q pointer to the SearchQueue.
 *
 * @return A pointer to the extracted element on success, NULL in case of error.
 * */
void *search_queue_pop(SearchQueue *q);

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
void *search_queue_getFront(const SearchQueue *q);

/**
 * @brief This function is used to get a reference to the element in the back
 * position of a SearchQueue; this element should correspond with the largest
 * element according to the comparison function passed in search_queue_new.
 *
 * @param q A pointer to the SearchQueue.
 *
 * @return A pointer to the element in the back position, NULL in case of error.
 * */
void *search_queue_getBack(const SearchQueue *q);

/**
 * @brief This function returns the size of a SearchQueue. Note that the
 * function returns 0 if it is called with a NULL pointer.
 *
 * @param q A pointer to the SearchQueue.
 *
 * @return The SearchQueue size, 0 in case of error.
 */
size_t search_queue_size(const SearchQueue *q);

/**
 * @brief This function prints the SearchQueue content to an output stream.
 *
 * @param fp A pointer to the stream.
 * @param q A pointer to the SearchQueue to be printed.
 *
 * @return On success this function returns the number of characters printed. In
 * case of error it returns a negative value.
 *  */
int search_queue_print(FILE *fp, const SearchQueue *q);

#endif
