/*=======================================================================*/
/*                Trabalho de AED II - Indice remissivo                  */
/* Nome: Arthur Alexsander Martins Teodoro                               */
/* MAtrícula: 0022427         Data: 13/09/2016                           */
/*=======================================================================*/

/*=======================================================================*/
/**/
/*=======================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "openHash.h"
#include "listadup.h"

struct palavra
{
	char plv[33];
	Lista ocorrencias;
};

int funcaoHash(char* palavra)
{
	unsigned int ascii = 0;
	int i;

	for(i = 1; i <= strlen(palavra); i++)
	{
		ascii = ascii + (palavra[i-1] * i);
	}

	return ascii % N;
}

Hash criaHash(void)
{
	int i;
	//srand(time(NULL));
	Hash hash = (Hash) malloc(sizeof(Palavra)*N);
	for(i = 0; i < N; i++)
	{
		hash[i] = NULL;
	}

	return hash;
}

void destroiHash(Hash hash)
{
	if(hash != NULL)
	{
		int i;
		for(i = 0; i < N; i++)
		{
			if(hash[i] != NULL)
			{
				destroiLista(hash[i]->ocorrencias);
				free(hash[i]);
			}
		}

		free(hash);
	}
	return;
}

Palavra insereHash(Hash hash, char* palavra)
{
	int posicao = funcaoHash(palavra);
	int posicoesVerificadas = 1;

	while(hash[posicao] != NULL || posicoesVerificadas == N)
	{
		posicao = (posicao+1)%N;
		posicoesVerificadas++;
	}

	if(posicoesVerificadas == N)
		return NULL;

	hash[posicao] = (Palavra) malloc(sizeof(struct palavra));
	strcpy(hash[posicao]->plv, palavra);
	hash[posicao]->ocorrencias = criaLista();
	return hash[posicao];

}

Palavra buscaHash(Hash hash, char* palavra)
{
	int posicao = funcaoHash(palavra);
	int posicoesVerificadas = 1;
	while(posicoesVerificadas < N)
	{
		if(hash[posicao] != NULL && !strcmp(hash[posicao]->plv,palavra))
		{
			return hash[posicao];
		}
		posicao = (posicao+1)%N;
		posicoesVerificadas++;
	}
	return NULL;
}