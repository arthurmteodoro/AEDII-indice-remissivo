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

void inserirPalavras(Hash hash, const char* arqPalvrasChave)
{
	FILE* pvlChaves = fopen(arqPalvrasChave, "rt");
	char pvlLida[33];
	int i;

	while(fgets(pvlLida, 33, pvlChaves) != NULL)
	{
		if(strlen(pvlLida) >= 4)
		{
			for(i = 0; (pvlLida[i] >= 'A' && pvlLida[i] <= 'z') || (pvlLida[i] >= '0' && pvlLida[i] <= '9'); i++);
			pvlLida[i] = '\0';
			insereHash(hash, pvlLida);
		}
	}

	fclose(pvlChaves);
}

char* buscaPalavra(int *inicio, int *fim, char* frase)
{
	/*As palavras sao delimitados por letras seguidades de digitos ou nao e ter tamanho de 32 char*/
	int i, j, posicao;
	char *plv = (char*) malloc(sizeof(char)*33);

	/*Busca o primeiro caractere válido*/
	for(i = *inicio; i < *fim && !(frase[i] >= 'A' && frase[i] <= 'z'); i++);

	/*Caso nao encontrar nenhuma palavra*/
	if(*fim == i)
		return NULL;	

	posicao = 0;
	/*Usa o i para procurar caracteres que nao sao pertencentes a palavras*/
	for(j = i; (j-i < 33) && ((frase[j] >= 'A' && frase[j] <= 'z') || (frase[j] >= '0' && frase[j] <= '9')); j++)
	{
		plv[posicao] = frase[j];
		posicao++;
	}

	/*Verifica o tamanho da palavra encontrada*/
	if(j-i < 4)
		return buscaPalavra(&j, &*fim, frase);	

	*inicio = i;
	*fim = j;	

	return plv;
}

void criaIndice(Hash hash, const char* palavrasChave, const char* texto)
{
	int Contlinha = 0;
	int inicioLinha = 0;
	int fimLinha = 0;
	char linha[5000];
	char* palavra;

	inserirPalavras(hash, palavrasChave);
	FILE* arq = fopen(texto, "rt");

	while(fgets(linha, 5000, arq) != NULL)
	{
		Contlinha++;

		inicioLinha = 0;
		fimLinha = strlen(linha);

		palavra = buscaPalavra(&inicioLinha, &fimLinha, linha);
		while(palavra != NULL)
		{
			inicioLinha = fimLinha;
			fimLinha = strlen(linha);

			insereOcorrencia(hash, palavra, Contlinha);	

			free(palavra);
			palavra = buscaPalavra(&inicioLinha, &fimLinha, linha);
		}
	}

	fclose(arq);
}