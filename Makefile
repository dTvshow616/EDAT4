################################################################################
CC=gcc
CFLAGS=-Wall -ggdb -Werror -Wpedantic
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=
# -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread
EJS = p4_e1 p4_e2 p4_e3
OBJS = p4_e1.o p4_e2.o p4_e3.o
OTROS = bstree.o vertex.o search_queue.o
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

p4_e2: p4_e2.o file_utils.o search_queue.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

p4_e2.o: p4_e2.c file_utils.h search_queue.h 
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

search_queue.o: search_queue.c search_queue.h bstree.h types.h
	$(CC) $(CFLAGS) -c search_queue.c

# ---------------------------- Comandos del make ----------------------------- #

clear:
	rm -rf *.o 

clean:
	rm -f *.o

run:
	@echo ">>>>>>Running p4_e1"
	@echo ""
	./p4_e1 $(DATA)/data_vertex_50K.txt "id:88997 tag:Golf_de_Ibiza" normal
	@echo ""
	./p4_e1 $(DATA)/data_vertex_50K.txt "id:88997 tag:Golf_de_Ibiza" sorted
	@echo ""
	./p4_e1 $(DATA)/data_vertex_50K.txt "id:889907 tag:Golf_de_Ibiza" normal
	@echo ""
	./p4_e1 $(DATA)/data_vertex_50K.txt "id:889907 tag:Golf_de_Ibiza" sorted
	@echo " "

	@echo ">>>>>>Running p4_e2"
	@echo " "
	./p4_e2 $(DATA)/data_string_10.txt $(OUT)/data_string_10.out
	./p4_e2 $(DATA)/data_string_1K.txt $(OUT)/data_string_1K.out
	./p4_e2 $(DATA)/data_string_2K.txt $(OUT)/data_string_2K.out
	@echo " "

	@echo ">>>>>>Running p4_e3"
	@echo " "
	./p4_e3 grades.txt
	@echo " "

runv:
	@echo ">>>>>>Running p4_e1 with valgrind"
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./p4_e1

	@echo " "

	@echo ">>>>>>Running p4_e2 with valgrind"
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./p4_e2

	@echo " "

	@echo ">>>>>>Running p4_e3 with valgrind"
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./p4_e3 grades.txt

	@echo " "
	