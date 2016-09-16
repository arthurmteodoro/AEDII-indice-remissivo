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

	/*FILE *arq = fopen("testes/texto1.txt", "rt");

	char plv[3000] = "Existe mais de 543 milhoes de dinheiros no mundo";

	while(fgets(plv, 3000, arq) != NULL)
	{

	int inicio = 0;
	int fim = strlen(plv);
	char* plv2;
	
	plv2 = buscaPalavra(&inicio, &fim, plv);
	while(plv2 != NULL)
	{
		printf("%s\n", plv2);
		inicio = fim;
		fim = strlen(plv);
		free(plv2);
		plv2 = buscaPalavra(&inicio, &fim, plv);
	}

	}*/

	FILE* indiceSaida = fopen(argv[3], "wt");

	criaIndice(h, argv[1], argv[2]);

	printaHash(h, indiceSaida);

	fclose(indiceSaida);

	destroiHash(h);

	return 0;
}