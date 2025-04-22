########################################################
CC=gcc
CFLAGS=-Wall -ggdb -Werror -Wpedantic
IFLAGS=-I./
LDFLAGS=-L./
LDLIBS=-lstack -lqueue
# -lm enlaza la biblioteca matematica, -pthread enlaza la biblioteca de hilos
LIBS = -lm -pthread
EJS = p3_e1.o p3_e1 p3_e2a.o p3_e2a p3_e2b.o p3_e2b p3_e3.o p3_e3
OTROS = queue.o list.o delivery.o
######################################################################
# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':' (dependencias)
########################################################################
all: $(EJS) $(OTROS)

# Ejercicio 1
p3_e1: p3_e1.o delivery.o vertex.o list.o libqueue.a
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(LIBS)

p3_e1.o: p3_e1.c delivery.h vertex.h list.h queue.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

# Ejercicio 2
p3_e2a: p3_e2a.o delivery.o vertex.o list.o queue.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

p3_e2a.o: p3_e2a.c delivery.h vertex.h list.h queue.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

p3_e2b: p3_e2b.o graph.o vertex.o queue.o stack.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

p3_e2b.o: p3_e2b.c graph.h vertex.h queue.h stack.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

# Ejercicio 3
p3_e3: p3_e3.o list.o file_utils.o
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS) $(LIBS)

p3_e3.o: p3_e3.c list.h file_utils.h
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

# Archivos necesarios para los ejercicios 
delivery.o: delivery.c delivery.h queue.h types.h
	$(CC) $(CFLAGS) -c delivery.c

file_utils.o: file_utils.c file_utils.h
	$(CC) $(CFLAGS) -c file_utils.c

graph.o: graph.c graph.h vertex.h queue.h
	$(CC) $(CFLAGS) -c graph.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) -c vertex.c

clear:
	rm -rf *.o 

clean:
	rm -f *.o

run:
	@echo ">>>>>>Running p3_e1"
	./p3_e1 requests.txt
	
	@echo " "

	@echo ">>>>>>Running p3_e2a"
	./p3_e2a requests.txt

	@echo " "

	@echo ">>>>>>Running p3_e2b"
	./p3_e2b city_graph.txt 100 700

	@echo " "

	@echo ">>>>>>Running p3_e3"
	./p3_e3 grades.txt 1

runv:
	@echo ">>>>>>Running p3_e1 with valgrind"
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./p3_e1 requests.txt

	@echo " "

	@echo ">>>>>>Running p3_e2a with valgrind"
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./p3_e2a requests.txt

	@echo " "

	@echo ">>>>>>Running p3_e2b with valgrind"
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./p3_e2b city_graph.txt 100 700

	@echo " "


	@echo ">>>>>>Running p3_e3 with valgrind"
	valgrind -s --leak-check=full --track-origins=yes --show-leak-kinds=all ./p3_e3 grades.txt 1
	