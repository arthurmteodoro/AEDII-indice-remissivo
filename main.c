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
	/*Fim da verificação de erros*/

	/*Le a quantidade de palavras, cria a hash e o vetor*/
	int quantPalavras = contaPalavrasChave(argv[1]);
	char** vetor = criaVetor(quantPalavras);
	Hash h = criaHash(quantPalavras);

	/*Criação do indice*/
	inserirPalavras(h, argv[1], vetor);

	criaIndice(h, argv[2]);

	geraSaida(h, argv[3], vetor, quantPalavras);
	/*Fim da criação do indice*/

	printf("A quantidade de colisoes foi de %d\n", colisaoHash(h));

	destroiVetor(vetor, quantPalavras);
	destroiHash(h);

	return 0;
}