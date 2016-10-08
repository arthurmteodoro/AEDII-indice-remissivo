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
#include <time.h>
#include "listadup.h"
#include "lista.h"

/*=======================================================================*/
/*                         ESTRUTURA CRIADA                              */
/*=======================================================================*/
struct palavra
{
	char plv[33];
	Lista ocorrencias;
	struct palavra *prox;
};

struct no
{
	struct palavra *valor;
	struct no *prox;
	struct no *ant;
};

typedef struct no *No;

struct lista
{
	int tam;
	struct no *inicio;
	struct no *fim;
};

/*=======================================================================*/
/*CRIA HASH - FUNCAO DE CRIACAO DA HASH                                  */
/*IN: VOID   OUT: PONTEIRO PARA HASH                                     */
/*=======================================================================*/
Hash criaHash(int tam)
{
	Hash h = (Hash) malloc(sizeof(struct lista));
	h->inicio = NULL;
	h->fim = NULL;
	h->tam = 0;
	return h;
}

/*=======================================================================*/
/*DESTROI HASH - FUNCAO DE DESTRUICAO DA HASH                            */
/*IN: PONTEIRO PARA HASH   OUT: VOID                                     */
/*=======================================================================*/
void destroiHash(Hash hash)
{
	No retirar = hash->inicio;
	while(retirar != NULL)
	{
		hash->inicio = retirar->prox;
		destroiLista(retirar->valor->ocorrencias);
		free(retirar);
		retirar = hash->inicio;
	}
	hash = NULL;
}

/*=======================================================================*/
/*INSERE HASH - FUNCAO RESPONSAVEL POR INSERIR PALAVRA                   */
/*IN: HASH E PALAVRA A INSERIR   OUT: PONTEIRO PARA PALAVRA              */
/*=======================================================================*/
Palavra insereHash(Hash lista, char* palavra)
{
	No insere = (No) malloc(sizeof(struct no));
	Palavra plv = (Palavra) malloc(sizeof(struct palavra));

	insere->valor = plv;
	strcpy(plv->plv, palavra);
	plv->ocorrencias = criaLista();

	if(lista->inicio == NULL)
	{
		insere->ant = NULL;
		insere->prox = NULL;
		lista->inicio = insere;
		lista->fim = insere;
		return plv;
	}

	insere->prox = lista->inicio;
	lista->inicio->ant = insere;
	insere->ant = NULL;
	lista->inicio = insere;
	lista->tam++;
	return plv;

}

/*=======================================================================*/
/*BUSCA HASH - FUNCAO DE BUSCA DA HASH                                   */
/*IN: HASH E PALAVRA A BUSCAR   OUT: PONTEIRO PARA PALAVRA               */
/*=======================================================================*/
Palavra buscaHash(Hash lista, char* palavra)
{
	No olhar = lista->inicio;
	while(olhar != NULL && strcmp(olhar->valor->plv, palavra))
	{
		olhar = olhar->prox;
	}

	if(olhar == NULL)
		return NULL;

	return olhar->valor;
}

/*=======================================================================*/
/*INSERE OCORRENCIA - FUNCAO RESPONSAVEL POR INSERIR LINHA               */
/*IN: HASH, PALAVRA E LINHA   OUT: VOID                                  */
/*=======================================================================*/
void insereOcorrencia(Hash lista, char* palavra, int linha)
{
	Palavra plv = buscaHash(lista, palavra);
	if(plv != NULL)
	{
		if(!existeLista(plv->ocorrencias, linha))
			insereLista(plv->ocorrencias, tamanhoLista(plv->ocorrencias), linha);
	}
}

/*=======================================================================*/
/*TAMANHO HASH - FUNCAO RESPONSAVEL POR RETORNAR TAMANHO HASH            */
/*IN: HASH   OUT: INT                                                    */
/*=======================================================================*/
int tamanhoHash(Hash hash)
{
	return hash->tam;
}

/*=======================================================================*/
/*RETORNA PALAVRA - FUNCAO QUE RETORNA A STRING DA STRUCT                */
/*IN: PALAVRA   OUT: CHAR*                                               */
/*=======================================================================*/
char* retornaPalavra(Palavra plv)
{
	return plv->plv;
}

/*=======================================================================*/
/*RETORNA LISTA - FUNCAO QUE RETORNA A LISTA DA STRUCT                   */
/*IN: PALAVRA   OUT: LISTA                                               */
/*=======================================================================*/
Lista retornaLista(Palavra plv)
{
	return plv->ocorrencias;
}

/*=======================================================================*/
/*RETORNA COLISAO - FUNCAO QUE RETORNA QUANT DE COLISAO                  */
/*IN: HASH   OUT: INT                                                    */
/*=======================================================================*/
int colisaoHash(Hash hash)
{
	return 0;
}