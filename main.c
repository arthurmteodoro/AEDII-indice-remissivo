/*=======================================================================*/
/*                Trabalho de AED II - Indice remissivo                  */
/* Nome: Arthur Alexsander Martins Teodoro                               */
/* MAtrícula: 0022427         Data: 13/09/2016                           */
/*=======================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openHash.h"
#include "indice.h"

int main(int argc, char const *argv[])
{

	Hash h = criaHash();

	/*insereHash(h,"roma");
	insereHash(h,"amor");

	insereOcorrencia(h, "roma", 1);
	insereOcorrencia(h, "roma", 2);
	insereOcorrencia(h, "amor", 3);
	insereOcorrencia(h, "amor", 4);

	FILE* arq = fopen(argv[2], "wt");

	printaHash(h, arq);*/

	//inserirPalavras(h, "testes/palavraschave1.txt");

	//printaHash(h);

	/*char plv[3000] = "Existe mais de 543 milhoes de dinheiros no mundo";
	int inicio = 0;
	int fim = strlen(plv);
	char* plv2;
	
	plv2 = buscaPalavra(&inicio, &fim, plv);
	while(plv2 != NULL)
	{
		printf("%s\n", plv2);
		inicio = fim;
		fim = strlen(plv);
		plv2 = buscaPalavra(&inicio, &fim, plv);
	}

	free(plv2);*/

	criaIndice(h, argv[1], argv[2]);

	destroiHash(h);

	return 0;
}