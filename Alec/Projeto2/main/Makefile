all: compile
	gcc heapmax.o lista.o conjunto.o main.o -o main -std=c99 -Wall

compile:
	gcc -c ../bibliotecas/impl/heapmax.c -o heapmax.o
	gcc -c ../bibliotecas/impl/lista.c -o lista.o
	gcc -c ../bibliotecas/impl/conjunto.c -o conjunto.o
	gcc -c main.c -o main.o

run:
	./main

clean:
	rm -f main
	rm *.o