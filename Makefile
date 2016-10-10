all:
	gcc -Wall -o listadup.o -c listadup.c
	gcc -Wall -o lista.o -c lista.c
	gcc -Wall -o openHash.o -c -D F=2 -D C=2 openHash.c
	gcc -Wall -o hashEncadeada.o -c -D F=2 hashEncadeada.c
	gcc -Wall -o indice.o -c indice.c
	gcc -Wall -o main.out listadup.o openHash.o indice.o -D TAM=75 main.c

run:
	./main.out