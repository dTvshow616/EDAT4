################################################################################
CC=gcc
CFLAGS=-Wall -ggdb -Werror -Wpedantic -ansi
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=
# -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread
EJS = p4_e1 p4_e2 p4_e3
OBJS = p4_e1.o p4_e2.o p4_e3.o
OTROS = bstree.o vertex.o
################################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':' (dependencias)
################################################################################
include makefile_ext
################################################################################

all: $(EJS) $(OTROS) $(OBJS)

# ------------------------------- Ejercicio 1 -------------------------------- #

p4_e1: p4_e1.o bstree.o vertex.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(LIBS)

p4_e1.o: p4_e1.c bstree.h vertex.h types.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

# ------------------------------- Ejercicio 2 -------------------------------- #

p4_e2: p4_e2.o file_utils.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

p4_e2.o: p4_e2a.c file_utils.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

# ------------------------------- Ejercicio 3 -------------------------------- #

p4_e3: p4_e3.o file_utils.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(LIBS)

p4_e3.o: p4_e3.c file_utils.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

# ----------------- Archivos necesarios para los ejercicios ------------------ #

file_utils.o: file_utils.c file_utils.h
	$(CC) $(CFLAGS) -c file_utils.c

vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) -c vertex.c

bstree.o: bstree.c bstree.h
	$(CC) $(CFLAGS) -c bstree.c

# ---------------------------- Comandos del make ----------------------------- #

clear:
	rm -rf *.o 

clean:
	rm -f *.o

run:
	@echo ">>>>>>Running p4_e1a"
	./p4_e1 requests.txt
	
	@echo " "

	@echo ">>>>>>Running p4_e1b"
	./p4_e2a requests.txt

	@echo " "

runv:
	@echo ">>>>>>Running p4_e1a with valgrind"
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./p4_e1a

	@echo " "

	@echo ">>>>>>Running p4_e1b with valgrind"
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./p4_e1b

	@echo " "
	