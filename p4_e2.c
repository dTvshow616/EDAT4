/*En este ejercicio se implementará un TAD Cola de Búsqueda (SQ, del inglés SearchQueue) que
almacenará los elementos ordenados según una función de comparación que recibirá como
puntero al inicializarse.
Para implementarlo se usará como base el TAD BST del ejercicio anterior, que permite
mantener los elementos ordenados. A la hora de extraer elementos siempre se hará según el
elemento mínimo de dicho árbol.
Ejercicio 2a: Implementación de la cola de búsqueda
Se pide implementar en search_queue.c las primitivas de search_queue.h, usando para ello
el TAD BST, teniendo en cuenta que la estructura de datos para el nuevo TAD SQ será:
struct _SearchQueue {
BSTree *data;
};*/

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

// RECIBE FICH DE ENTRADA Y DE SALIDA