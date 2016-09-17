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

struct hash
{
	int tam;
	struct palavra **vetor;
};


/*=======================================================================*/
/*FUNCAO HASH - FUNCAO RESPONSAVEL POR DEFINIR POSICAO                   */
/*IN: PALAVRA   OUT: POSICAO                                             */
/*=======================================================================*/
int funcaoHash(char* palavra, int tam)
{
	unsigned int ascii = 0;
	int i;

	for(i = 1; i <= strlen(palavra); i++)
	{
		ascii = ascii + (palavra[i-1] * i);
	}

	return ascii % tam;
}

/*=======================================================================*/
/*CRIA HASH - FUNCAO DE CRIACAO DA HASH                                  */
/*IN: VOID   OUT: PONTEIRO PARA HASH                                     */
/*=======================================================================*/
Hash criaHash(int tam)
{
	int i;
	Hash hash = (Hash) malloc(sizeof(struct hash));
	hash->tam = tam;
	hash->vetor = (Palavra*) malloc(sizeof(Palavra)*tam);
	for(i = 0; i < tam; i++)
	{
		hash->vetor[i] = NULL;
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
		for(i = 0; i < hash->tam; i++)
		{
			if(hash->vetor[i] != NULL)
			{
				destroiLista(hash->vetor[i]->ocorrencias);
				free(hash->vetor[i]);
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
	int posicao = funcaoHash(palavra, hash->tam);
	int posicoesVerificadas = 1;

	if(buscaHash(hash, palavra) != NULL)
		return NULL;

	while(hash->vetor[posicao] != NULL || posicoesVerificadas == hash->tam)
	{
		posicao = (posicao+1)%hash->tam;
		posicoesVerificadas++;
	}

	if(posicoesVerificadas == hash->tam)
		return NULL;

	hash->vetor[posicao] = (Palavra) malloc(sizeof(struct palavra));
	strcpy(hash->vetor[posicao]->plv, palavra);
	hash->vetor[posicao]->ocorrencias = criaLista();
	return hash->vetor[posicao];

}

/*=======================================================================*/
/*BUSCA HASH - FUNCAO DE BUSCA DA HASH                                   */
/*IN: HASH E PALAVRA A BUSCAR   OUT: PONTEIRO PARA PALAVRA               */
/*=======================================================================*/
Palavra buscaHash(Hash hash, char* palavra)
{
	int posicao = funcaoHash(palavra, hash->tam);
	int posicoesVerificadas = 0;
	while(posicoesVerificadas < hash->tam)
	{
		if(hash->vetor[posicao] != NULL && !strcmp(hash->vetor[posicao]->plv,palavra))
		{
			return hash->vetor[posicao];
		}
		posicao = (posicao+1)%hash->tam;
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
	{
		if(!existeLista(plv->ocorrencias, linha))
			insereLista(plv->ocorrencias, tamanhoLista(plv->ocorrencias), linha);
	}
}

/*=======================================================================*/
/*PRINTA HASH - FUNCAO RESPONSAVEL POR IMPRIMIR HASH                     */
/*IN: HASH   OUT: VOID                                                   */
/*=======================================================================*/
void printaHash(Hash hash, FILE* arquivo)
{

	int i;
	for(i = 0; i < hash->tam; i++)
	{
		if(hash->vetor[i] != NULL)
		{
			fprintf(arquivo, "%s - ", hash->vetor[i]->plv);
			printaLista(hash->vetor[i]->ocorrencias, arquivo);
		}
	}
}