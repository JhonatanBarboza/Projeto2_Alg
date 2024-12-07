all: compile
	gcc avl.o avl-tree-test.o -o avl-tree-test -std=c99 -Wall
	rm *.o

compile:
	gcc -c ../bibliotecas/impl/AVL.c -o avl.o
	gcc -c avl-tree-test.c -o avl-tree-test.o

run:
	./avl-tree-test

clean:
	rm -f avl-tree-test