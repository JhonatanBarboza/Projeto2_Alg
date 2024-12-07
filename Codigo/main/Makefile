all: compile
	gcc avl.o testeAVL.o -o testeAVL -std=c99 -Wall
	rm *.o

compile:
	gcc -c ../bibliotecas/impl/AVL.c -o avl.o
	gcc -c testeAVL.c -o testeAVL.o

run:
	./testeAVL

clean:
	rm -f testeAVL