all: compile
	gcc lista.o avl.o conjunto.o testeConj.o -o testeConj -std=c99 -Wall
	rm *.o

compile:
	gcc -c ../bibliotecas/impl/lista.c -o lista.o
	gcc -c ../bibliotecas/impl/AVL.c -o avl.o
	gcc -c ../bibliotecas/impl/conjunto.c -o conjunto.o
	gcc -c testeConj.c -o testeConj.o

run:
	./testeConj

clean:
	rm -f testeConj