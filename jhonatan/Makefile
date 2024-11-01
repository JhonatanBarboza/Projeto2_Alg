# Compila todos os arquivos e gera o executável 'cliente'
all: clean cliente run

conjunto.o: conjunto.c conjunto.h 
	gcc -c conjunto.c -o conjunto.o -std=c99 -Wall

lista.o: lista.c lista.h
	gcc -c lista.c -o lista.o -std=c99 -Wall

arvore.o: arvore.c arvore.h
	gcc -c arvore.c -o arvore.o -std=c99 -Wall

main.o: main.c arvore.h lista.h conjunto.h 
	gcc -c main.c -o main.o -std=c99 -Wall

# Gera o executável 'cliente' a partir dos arquivos objetos
cliente: main.o arvore.o lista.o conjunto.o
	gcc main.o arvore.o lista.o conjunto.o -o cliente -std=c99 -Wall -lm

# Regra para executar o programa 'cliente'
run: cliente
	./cliente

# Remove todos os arquivos objetos e o executável gerado
clean:
	rm -f *.o cliente