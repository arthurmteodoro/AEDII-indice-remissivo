all:
	gcc -Wall -o listadup.o -c listadup.c
	gcc -Wall -o openHash.o -c openHash.c
	gcc -Wall -o hashEncadeada.o -c hashEncadeada.c
	gcc -Wall -o indice.o -c indice.c
	gcc -Wall -o main.out listadup.o indice.o hashEncadeada.o main.c

run:
	./main.out