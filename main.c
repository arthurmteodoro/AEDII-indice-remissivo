/*=======================================================================*/
/*                Trabalho de AED II - Indice remissivo                  */
/* Nome: Arthur Alexsander Martins Teodoro                               */
/* MAtrícula: 0022427         Data: 13/09/2016                           */
/*=======================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "openHash.h"
#include "indice.h"

int main(int argc, char const *argv[])
{
	/*Verificação de erros*/
	if(argc != 4)
	{
		printf("ERRO - Quantidade de arquivos inválida\n");
		printf("USO: ./main.out <palavraschave> <texto> <saida>\n");
		exit(1);
	}
	FILE* arqTeste1 = fopen(argv[1], "rt");
	FILE* arqTeste2 = fopen(argv[2], "rt");
	if(arqTeste1 == NULL || arqTeste2 == NULL)
	{
		printf("ERRO - arquivos de palavras chave ou texto nao existem\n");
		exit(1);
	}
	fclose(arqTeste1);
	fclose(arqTeste2);

	int quantPalavras = contaPalavrasChave(argv[1]);

	Hash h = criaHash(quantPalavras);

	criaIndice(h, argv[1], argv[2]);

	destroiHash(h);

	return 0;
}