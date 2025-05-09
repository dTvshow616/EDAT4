#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "search_queue.h"
#include "bstree.h"

struct _SearchQueue
{
    BSTree *data;
};

SearchQueue *search_queue_new(P_ele_print print_ele, P_ele_cmp cmp_ele);

void search_queue_free(SearchQueue *q);

Bool search_queue_isEmpty(const SearchQueue *q);

Status search_queue_push(SearchQueue *q, void *ele);

void *search_queue_pop(SearchQueue *q);

void *search_queue_getFront(const SearchQueue *q);

void *search_queue_getBack(const SearchQueue *q);

size_t search_queue_size(const SearchQueue *q);

int search_queue_print(FILE *fp, const SearchQueue *q);