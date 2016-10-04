all:
	gcc -Wall -o listadup.o -c listadup.c
	gcc -Wall -o openHash.o -c -D F=3 -D C=1 openHash.c
	gcc -Wall -o hashEncadeada.o -c -D F=1 hashEncadeada.c
	gcc -Wall -o indice.o -c indice.c
	gcc -Wall -o main.out listadup.o hashEncadeada.o indice.o -D TAM=75 main.c

run:
	./main.out