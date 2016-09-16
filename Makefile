all:
	gcc -Wall -o listadup.o -c listadup.c
	gcc -Wall -o openHash.o -c openHash.c
	gcc -Wall -o indice.o -c indice.c
	gcc -Wall -o main.out listadup.o openHash.o indice.o main.c

run:
	./main.out