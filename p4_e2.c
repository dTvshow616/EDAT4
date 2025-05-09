
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
data_string_10.txt.
Reflexiones sobre el TAD SQ
 ¿Qué diferencias y similitudes hay entre el TAD SQ y el TAD Cola de la práctica
anterior?
 ¿Qué coste (aproximado) tiene la operación de extraer un elemento en el TAD SQ?
¿Sería posible hacer que esta operación fuera 𝒪(1)?*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_utils.h"
#include "search_queue.h"

/*En este ejercicio se implementará un SearchQueue que almacenará los elementos ordenados según una función de comparación que recibirá como puntero
al inicializarse. Para implementarlo se usará como base el TAD BST del ejercicio anterior, que permite mantener los elementos ordenados.
A la hora de extraer elementos siempre se hará según el elemento mínimo de dicho árbol.*/

int main(int argc, char *argv[])
{
  FILE *input_file, *output_file = NULL;
  SearchQueue *queue = NULL;
  P_ele_print print_ele = string_print;
  P_ele_cmp cmp_ele = string_cmp;
  char buffer[512];
  char *line = NULL;
  void *element = NULL;
  int len;

  /* Check command line arguments */
  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  /* Open input file */
  input_file = fopen(argv[1], "r");
  if (!input_file)
  {
    fprintf(stderr, "Error opening input file: %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  /* Open output file */
  output_file = fopen(argv[2], "w");
  if (!output_file)
  {
    fprintf(stderr, "Error opening output file: %s\n", argv[2]);
    fclose(input_file);
    return EXIT_FAILURE;
  }

  /* Initialize search queue */
  queue = search_queue_new(print_ele, cmp_ele);
  if (!queue)
  {
    fprintf(stderr, "Error creating search queue\n");
    fclose(input_file);
    fclose(output_file);
    return EXIT_FAILURE;
  }

  /* Read each line from input file and push to queue */
  while ((len = read_line(input_file, buffer)) > 0)
  {
    line = strdup(buffer); /* Make a copy of the line */
    if (!line)
    {
      fprintf(stderr, "Memory allocation error\n");
      search_queue_free(queue);
      fclose(input_file);
      fclose(output_file);
      return EXIT_FAILURE;
    }
    /* Insert each line into the search queue */
    if (search_queue_push(queue, line) == ERROR)
    {
      fprintf(stderr, "Error inserting line into queue\n");
      free(line);
      search_queue_free(queue);
      fclose(input_file);
      fclose(output_file);
      return EXIT_FAILURE;
    }
  }

  /* Close input file as we don't need it anymore */
  fclose(input_file);

  /* Empty the queue and print each element to the output file */
  while (!search_queue_isEmpty(queue))
  {
    element = search_queue_pop(queue);
    if (element)
    {
      fprintf(output_file, "%s\n", (char *)element);
      free(element); /* Free the line we allocated in file_read_line */
    }
  }

  /* Cleanup */
  fclose(output_file);
  search_queue_free(queue);

  return EXIT_SUCCESS;
}