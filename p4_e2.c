
/*En este ejercicio se implementará un TAD Cola de Búsqueda (SQ, del inglés SearchQueue) que
almacenará los elementos ordenados según una función de comparación que recibirá como
puntero al inicializarse.
Para implementarlo se usará como base el TAD BST del ejercicio anterior, que permite
mantener los elementos ordenados. A la hora de extraer elementos siempre se hará según el
elemento mínimo de dicho árbol.
Ejercicio 2b: Ordenación de ficheros de texto
Para comprobar el correcto funcionamiento del TAD SQ, se pide implementar un nuevo
programa principal, p4_e2.c, que reciba dos argumentos, correspondientes al nombre de un
fichero de entrada, y al nombre de un fichero de salida.
A continuación, el programa leerá cada línea del fichero de entrada, insertando la cadena leída
en una cola SQ. Una vez leído el fichero de entrada, se vaciará la cola elemento a elemento
imprimiendo cada línea en el fichero de salida. De esta forma, cuando termine la ejecución el
fichero de salida deberá contener las líneas del fichero de entrada, pero ordenadas
alfabéticamente.
Podéis usar file_utils.c para las funciones string_xxxx necesarias.
El programa debe funcionar sin fugas de memoria. Como ejemplo de ejecución, se puede ver el
fichero de salida esperado data_string_10.out cuando el fichero de entrada es
data_string_10.txt.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"
#include "search_queue.h"

/*En este ejercicio se implementará un SearchQueue que almacenará los elementos ordenados según una función de comparación que recibirá como puntero
al inicializarse. Para implementarlo se usará como base el TAD BST del ejercicio anterior, que permite mantener los elementos ordenados.
A la hora de extraer elementos siempre se hará según el elemento mínimo de dicho árbol.*/

int main(int argc, char *argv[]) {
  FILE *input_file, *output_file = NULL;
  SearchQueue *queue = NULL;
  P_ele_print print_ele = string_print;
  P_ele_cmp cmp_ele = string_cmp;
  char **line = NULL;
  int i = 0, num_lines = 0;

  /* Open input file */
  input_file = fopen(argv[1], "r");
  if (!input_file) {
    return -1;
  }

  /* Open output file */
  output_file = fopen(argv[2], "w");
  if (!output_file) {
    fclose(input_file);
    return -1;
  }

  line = (char **)malloc(1 * sizeof(char *));
  if (!line) {
    fclose(input_file);
    fclose(output_file);
    return -1;
  }

  line[0] = (char *)malloc(1 * sizeof(char));
  if (!line) {
    free(line);
    fclose(input_file);
    fclose(output_file);
    return -1;
  }

  /* Initialize search queue */
  queue = search_queue_new(print_ele, cmp_ele);
  if (!queue) {
    fclose(input_file);
    fclose(output_file);
    return -1;
  }

  /* Read each line from input file and push to queue */
  while (fscanf(input_file, "%s", line[i]) == 1) {
    if (search_queue_push(queue, line[i]) == ERROR) {
      search_queue_free(queue);
      fclose(input_file);
      fclose(output_file);
      return -1;
    }
    line = (char **)realloc(line, num_lines * sizeof(line));
    if (!line) {
      for (i = 0; i < num_lines; i++) {
        free(line[i]);
      }
      free(line);
      fclose(input_file);
      fclose(output_file);
      return -1;
    }
    line[i] = (char *)malloc(1 * sizeof(char));
    if (!line) {
      for (i = 0; i < num_lines; i++) {
        free(line[i]);
      }
      free(line);
      fclose(input_file);
      fclose(output_file);
      return -1;
    }
    num_lines++;
    i++;
  }

  /* Close input file as we don't need it anymore */
  fclose(input_file);

  /* Empty the queue and print each element to the output file */
  search_queue_print(output_file, queue);
  while (search_queue_isEmpty(queue) != TRUE) {
    search_queue_pop(queue);
  }

  /* Cleanup */
  for (i = 0; i < num_lines; i++) {
    free(line[i]);
  }
  free(line);
  fclose(output_file);
  search_queue_free(queue);

  return 0;
}