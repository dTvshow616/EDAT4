#include <stdio.h>
#include <stdlib.h>

#include "bstree.h"
#include "file_utils.h"
#include "search_queue.h"

/*EJERCICIO 3
En este ejercicio realizaremos un programa de prueba de vuestro TAD SearchQueue. Este programa debe hacer lo siguiente:

1. Leer las calificaciones en un fichero de entrada que recibe como argumento.
2. Almacenarlas en una SearchQueue implementada sobre un árbol binario de búsqueda.
3. Procesar la información para producir estas salidas en este orden:
  - Todas las notas ordenadas de menor a mayor (usando search_queue_print).
  - Media de las notas (con 2 cifras decimales).
  - Mediana de las notas (con 2 cifras decimales).
  - Tres notas más bajas (usando search_queue_pop, una a una).
  - Tres notas más altas (usando search_queue_getBack y eliminando la nota del árbol para evitar repetición).

Podéis usar file_utils.c para las funciones float_xxxx necesarias.
Un ejemplo de salida para el fichero grades.txt proporcionado, el cual contiene 20 notas, es el siguiente. Generad esta salida en la terminal, usando
stdout.

Ordered grades: 2.90 3.30 3.90 4.00 4.40 5.50 5.80 6.20 6.50 6.70 6.80 7.00 7.10 7.30 7.80 8.00 8.30 8.50 9.20 9.90
Mean: 6.47
Median: 6.60
Lowest grades: 2.90 3.30 3.90
Highest grades: 9.90 9.20 8.50*/

int main(int argc, char *argv[]) {
  /*ANCHOR - Hecho :)*/
  FILE *fich_notas = NULL;
  SearchQueue *search_queue;
  SearchQueue *aux_queue;
  P_ele_print print_ele = float_print;
  P_ele_cmp cmp_ele = float_cmp;
  int i = 0;
  void *top_grade = NULL;
  float media = 0;
  float mediana = 99999;
  float num_notas = 0;
  float suma = 0;
  float *notas = NULL;
  /*void *ele = NULL;*/

  fich_notas = fopen(argv[1], "r");
  if (!fich_notas) {
    return -1;
  }

  search_queue = search_queue_new(print_ele, cmp_ele);
  if (!search_queue) {
    fclose(fich_notas);
    return -1;
  }

  aux_queue = search_queue_new(print_ele, cmp_ele);
  if (!aux_queue) {
    search_queue_free(search_queue);
    fclose(fich_notas);
    return -1;
  }

  fscanf(fich_notas, "%f", &num_notas);

  notas = (float *)calloc(num_notas, sizeof(float));
  if (!search_queue) {
    search_queue_free(search_queue);
    search_queue_free(aux_queue);
    fclose(fich_notas);
    return -1;
  }

  /*Builds a tree from a previously allocated empty collection TaD*/
  for (i = 0; i < num_notas; i++) {
    fscanf(fich_notas, "%f", &notas[i]);
    search_queue_push(search_queue, &notas[i]);
    search_queue_push(aux_queue, &notas[i]);
  }

  fclose(fich_notas);

  /* Todas las notas ordenadas de menor a mayor (usando search_queue_print).*/
  fprintf(stdout, "Ordered grades: ");
  search_queue_print(stdout, search_queue);

  /* Media de las notas (con 2 cifras decimales).*/
  suma = search_queue_get_tree_nodes_sum(search_queue);
  media = suma / num_notas;

  fprintf(stdout, "Mean: %.2f\n", media);

  /* Mediana de las notas (con 2 cifras decimales).*/
  /*TODO - No sé cómo dividir esto :( )*/
  mediana = search_queue_get_median(aux_queue);

  fprintf(stdout, "Median: ");
  float_print(stdout, &mediana);
  fprintf(stdout, "\n");

  /* Tres notas más bajas (usando search_queue_pop, una a una).*/
  fprintf(stdout, "Lowest grades: ");
  for (i = 0; i < 3; i++) {
    print_ele(stdout, search_queue_pop(search_queue));
    fprintf(stdout, " ");
  }
  fprintf(stdout, "\n");

  /* Tres notas más altas (usando search_queue_getBack y eliminando la nota del árbol para evitar repetición).*/
  fprintf(stdout, "Highest grades: ");
  for (i = 0; i < 3; i++) {
    top_grade = search_queue_getBack(search_queue);
    if (!top_grade) {
      search_queue_free(search_queue);
      search_queue_free(aux_queue);
      free(notas);
      return 1;
    }

    print_ele(stdout, top_grade);
    fprintf(stdout, " ");
    search_queue_remove(search_queue, top_grade);
  }
  fprintf(stdout, "\n");

  search_queue_free(aux_queue);
  search_queue_free(search_queue);
  free(notas);
}
