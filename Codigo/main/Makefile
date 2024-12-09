all: compile
	gcc lista.o avl.o conjunto.o main.o -o main -std=c99 -Wall
	rm *.o

compile:
	gcc -c ../bibliotecas/impl/lista.c -o lista.o
	gcc -c ../bibliotecas/impl/AVL.c -o avl.o
	gcc -c ../bibliotecas/impl/conjunto.c -o conjunto.o
	gcc -c main.c -o main.o

run:
	./main

clean:
	rm -f main