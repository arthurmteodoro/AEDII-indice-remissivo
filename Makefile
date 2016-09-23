all:
	gcc -Wall -o listadup.o -c listadup.c
	gcc -Wall -o openHash.o -c -D F=1 -D C=2 openHash.c
	gcc -Wall -o hashEncadeada.o -c -D F=3 hashEncadeada.c
	gcc -Wall -o indice.o -c indice.c
	gcc -Wall -o main.out listadup.o openHash.o indice.o main.c

run:
	./main.out