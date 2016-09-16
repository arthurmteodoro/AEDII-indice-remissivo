/*=======================================================================*/
/*                Trabalho de AED II - Indice remissivo                  */
/* Nome: Arthur Alexsander Martins Teodoro                               */
/* MAtrícula: 0022427         Data: 13/09/2016                           */
/*=======================================================================*/

/*=======================================================================*/
/*                        BIBLIOTECAS USADAS                             */
/*=======================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "openHash.h"
#include "listadup.h"

/*=======================================================================*/
/*                         ESTRUTURA CRIADA                              */
/*=======================================================================*/
struct palavra
{
	char plv[33];
	Lista ocorrencias;
};


/*=======================================================================*/
/*FUNCAO HASH - FUNCAO RESPONSAVEL POR DEFINIR POSICAO                   */
/*IN: PALAVRA   OUT: POSICAO                                             */
/*=======================================================================*/
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

/*=======================================================================*/
/*CRIA HASH - FUNCAO DE CRIACAO DA HASH                                  */
/*IN: VOID   OUT: PONTEIRO PARA HASH                                     */
/*=======================================================================*/
Hash criaHash(void)
{
	int i;
	Hash hash = (Hash) malloc(sizeof(Palavra)*N);
	for(i = 0; i < N; i++)
	{
		hash[i] = NULL;
	}

	return hash;
}

/*=======================================================================*/
/*DESTROI HASH - FUNCAO DE DESTRUICAO DA HASH                            */
/*IN: PONTEIRO PARA HASH   OUT: VOID                                     */
/*=======================================================================*/
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

/*=======================================================================*/
/*INSERE HASH - FUNCAO RESPONSAVEL POR INSERIR PALAVRA                   */
/*IN: HASH E PALAVRA A INSERIR   OUT: PONTEIRO PARA PALAVRA              */
/*=======================================================================*/
Palavra insereHash(Hash hash, char* palavra)
{
	int posicao = funcaoHash(palavra);
	int posicoesVerificadas = 1;

	if(buscaHash(hash, palavra) != NULL)
		return NULL;

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

/*=======================================================================*/
/*BUSCA HASH - FUNCAO DE BUSCA DA HASH                                   */
/*IN: HASH E PALAVRA A BUSCAR   OUT: PONTEIRO PARA PALAVRA               */
/*=======================================================================*/
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

/*=======================================================================*/
/*INSERE OCORRENCIA - FUNCAO RESPONSAVEL POR INSERIR LINHA               */
/*IN: HASH, PALAVRA E LINHA   OUT: VOID                                  */
/*=======================================================================*/
void insereOcorrencia(Hash hash, char* palavra, int linha)
{
	Palavra plv = buscaHash(hash, palavra);
	if(plv != NULL)
		insereLista(plv->ocorrencias, tamanhoLista(plv->ocorrencias), linha);
}

/*=======================================================================*/
/*PRINTA HASH - FUNCAO RESPONSAVEL POR IMPRIMIR HASH                     */
/*IN: HASH   OUT: VOID                                                   */
/*=======================================================================*/
void printaHash(Hash hash, FILE* arquivo)
{

	int i;
	for(i = 0; i < N; i++)
	{
		if(hash[i] != NULL)
		{
			fprintf(arquivo, "%s - ", hash[i]->plv);
			printaLista(hash[i]->ocorrencias, arquivo);
		}
	}
}