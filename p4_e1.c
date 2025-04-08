#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bstree.h"
#include "types.h"
#include "vertex.h"

#define MAX_LINE 150

void freeData(Vertex **data, int n) {
  int i;

  if (!data || (n <= 0)) {
    return;
  }

  for (i = 0; i < n; i++) {
    if (data[i]) {
      vertex_free(data[i]);
    }
  }

  free(data);
}

Vertex **loadData(FILE *pf, int n) {
  int i;
  char string[MAX_LINE];
  Vertex **data = NULL;

  if (!pf || (n <= 0)) {
    return NULL;
  }

  data = (Vertex **)malloc(n * sizeof(Vertex *));
  if (!data) {
    return NULL;
  }

  for (i = 0; i < n; i++) {
    data[i] = NULL;
  }

  for (i = 0; i < n; i++) {
    if (!fgets(string, MAX_LINE, pf) || !(data[i] = vertex_initFromString(string))) {
      freeData(data, n);
      return NULL;
    }
  }

  return data;
}

void loadBalancedTree_rec(Vertex **sorted_data, BSTree *t, int first, int last) {
  int middle = (first + last) / 2;
  Vertex *v;

  if (first <= last) {
    v = *(&(sorted_data[0]) + middle);
    if (tree_insert(t, v) == ERROR) {
      fprintf(stdout, "Vertex ");
      vertex_print(stdout, v);
      fprintf(stdout, " not inserted!\n");
    }

    loadBalancedTree_rec(sorted_data, t, first, middle - 1);
    loadBalancedTree_rec(sorted_data, t, middle + 1, last);
  }
}

BSTree *loadBalancedTree(Vertex **data, int n) {
  BSTree *t;

  if (!data || (n <= 0)) {
    return NULL;
  }

  if (!(t = tree_init(vertex_print, vertex_cmp))) {
    return NULL;
  }

  loadBalancedTree_rec(data, t, 0, n - 1);

  return t;
}

BSTree *loadUnbalancedTree(Vertex **data, int n) {
  BSTree *t;
  Vertex *v;
  int i;

  if (!data || (n <= 0)) {
    return NULL;
  }

  if (!(t = tree_init(vertex_print, vertex_cmp))) {
    return NULL;
  }

  for (i = 0; i < n; i++) {
    v = data[i];
    if (tree_insert(t, v) == ERROR) {
      fprintf(stdout, "Vertex ");
      vertex_print(stdout, v);
      fprintf(stdout, " not inserted!\n");
    }
  }

  return t;
}

int getNumberLines(FILE *pf){
    char line[MAX_LINE];
    int n = 0;

    while (fgets(line, MAX_LINE, pf) != NULL) {
      n++;
    }

    return n;
}

int qsort_fun(const void *e1, const void *e2){
  Vertex **pv1, **pv2;

  pv1 = (Vertex **) e1;
  pv2 = (Vertex **) e2;

  return vertex_cmp(*pv1, *pv2);
}

int main(int argc, char const *argv[]) {
  FILE *f_in = NULL, *f_out = NULL;
  BSTree *t = NULL;
  Vertex **data, *v;
  const char *mode, *desc;
  int n;
  time_t time;

  if (argc != 4) {
    printf("Usage: %s vertex_file vertex_desc mode[normal|sorted]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  mode = argv[3];
  if (strcmp(mode, "normal") && strcmp(mode, "sorted")) {
    printf("Incorrect mode: %s\n", mode);
    exit(EXIT_FAILURE);
  }

  f_in = fopen(argv[1], "r");
  if (!f_in) {
    exit(EXIT_FAILURE);
  }
  f_out = stdout;

  desc = argv[2];
  v = vertex_initFromString((char *)desc);
  if (v == NULL) {
    printf("Error when initialising vertex with description: %s\n", desc);
    fclose(f_in);
    exit(EXIT_FAILURE);
  }

  n = getNumberLines(f_in); fclose(f_in);
  fprintf(f_out, "No. lines: %d\n", n);
  f_in = fopen(argv[1], "r");
  if (!(data = loadData(f_in, n))) {
    fclose(f_in);
    exit(EXIT_FAILURE);
  }
  fclose(f_in);

  if (!strcmp(mode, "normal")) {
    fprintf(f_out, "Mode: normal\n");
    time = clock();
    t = loadUnbalancedTree(data, n);
    time = clock() - time;
  }
  else {
    qsort(data, n, sizeof(Vertex *), qsort_fun);
    fprintf(f_out, "Mode: sorted\n");
    time = clock();
    t = loadBalancedTree(data, n);
    time = clock() - time;
  }
  if (!t) {
    freeData(data, n);
    exit(EXIT_FAILURE);
  }

  fprintf(f_out, "Tree building time: %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);
  fprintf(f_out, "Tree size: %ld\nTree depth: %d\n", tree_size(t), tree_depth(t));

  fprintf(f_out, "Min element in tree: ");
  time = clock();
  vertex_print(f_out, tree_find_min(t));
  time = clock() - time;
  fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);

  fprintf(f_out, "Max element in tree: ");
  time = clock();
  vertex_print(f_out, tree_find_max(t));
  time = clock() - time;
  fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);

  time = clock();
  if (tree_contains(t, v) == TRUE) {
    fprintf(f_out, "Element found");
    time = clock() - time;
    fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);

    fprintf(f_out, "Removing element in tree: ");
    time = clock();
    fprintf(f_out, "%s", tree_remove(t, v) == OK ? "OK" : "ERR");
    time = clock() - time;
    fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);
    fprintf(f_out, "Tree size: %ld\nTree depth: %d\n", tree_size(t), tree_depth(t));
  } else {
    fprintf(f_out, "Element NOT found");
    time = clock() - time;
    fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);
  }

  freeData(data, n);
  tree_destroy(t);
  vertex_free(v);

  exit(EXIT_SUCCESS);
}