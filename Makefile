all:
	gcc -o listadup.o -c listadup.c
	gcc -o openHash.o -c -D F=3 -D C=2 openHash.c
	gcc -o hashEncadeada.o -c -D F=2 hashEncadeada.c
	gcc -o indice.o -c indice.c
	gcc -o main.out listadup.o openHash.o indice.o -D TAM=25 main.c

run:
	./main.out