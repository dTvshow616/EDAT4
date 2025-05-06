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