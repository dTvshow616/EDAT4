#include <stdio.h>
#include <stdlib.h>

#include "file_utils.h"
#include "search_queue.h"

/*En este ejercicio se implementará un SearchQueue que almacenará los elementos ordenados según una función de comparación que recibirá como puntero
al inicializarse. Para implementarlo se usará como base el TAD BST del ejercicio anterior, que permite mantener los elementos ordenados.
A la hora de extraer elementos siempre se hará según el elemento mínimo de dicho árbol.*/

int main(int argc, char *argv[]) {
  /*REVIEW - */
  FILE *input_file, *output_file = NULL;
  char line[1024];
  SearchQueue *queue = NULL;
  P_ele_print print_ele = string_print;
  P_ele_cmp cmp_ele = string_cmp;
  int i, num_elems = 0;

  /* Reciba dos argumentos: fichero de entrada, y fichero de salida.*/
  input_file = fopen(argv[1], "r");
  if (!input_file) {
    return 1;
  }

  output_file = fopen(argv[2], "w");
  if (!output_file) {
    fclose(input_file);
    return 1;
  }

  queue = search_queue_new(print_ele, cmp_ele);
  if (!queue) {
    fclose(input_file);
    fclose(output_file);
    return 1;
  }

  /* A continuación, el programa leerá cada línea del fichero de entrada, insertando la cadena leída en una cola SQ.*/
  while (fscanf(input_file, "%s", line) == 1) {
    if (search_queue_push(queue, line) == OK) {
      num_elems++;
    }
  }

  /*Una vez leído el fichero de entrada, se vaciará la cola elemento a elemento imprimiendo cada línea en el fichero de salida.*/
  for (i = 0; i < num_elems; i++) {
    print_ele(output_file, search_queue_pop(queue));
  }

  /*De esta forma, cuando termine la ejecución el fichero de salida deberá contener las líneas del fichero de entrada, pero ordenadas alfabéticamente.
  Podéis usar file_utils.c para las funciones string_xxxx necesarias. El programa debe funcionar sin fugas de memoria. Como ejemplo de ejecución, se
  puede ver el fichero de salida esperado data_string_10.out cuando el fichero de entrada es data_string_10.txt.*/

  fclose(input_file);
  fclose(output_file);
  search_queue_free(queue);
}
