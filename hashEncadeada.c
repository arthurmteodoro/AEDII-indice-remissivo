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
#include "hashEncadeada.h"
#include "listadup.h"

/*=======================================================================*/
/*                         ESTRUTURA CRIADA                              */
/*=======================================================================*/
struct palavra
{
	char plv[33];
	Lista ocorrencias;
	struct palavra *prox;
};

struct hash
{
	int tam;
	int colisao;
	struct palavra **vetor;
};


static int vetRand[32];

/*=======================================================================*/
/*FUNCAO HASH1 - FUNCAO RESPONSAVEL POR DEFINIR POSICAO                   */
/*IN: PALAVRA   OUT: POSICAO                                             */
/*=======================================================================*/
int funcaoHash1(char* palavra, int tam)
{
	unsigned long int ascii = 0;
	int i;

	for(i = 0; i < strlen(palavra); i++)
	{
		ascii = ascii + (palavra[i] * vetRand[i]);
	}

	return ascii % tam;
}

/*=======================================================================*/
/*FUNCAO HASH2 - FUNCAO RESPONSAVEL POR DEFINIR POSICAO                   */
/*IN: PALAVRA   OUT: POSICAO                                             */
/*=======================================================================*/
int funcaoHash2(char* palavra, int tam)
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
/*FUNCAO HASH2 - FUNCAO RESPONSAVEL POR DEFINIR POSICAO                   */
/*IN: PALAVRA   OUT: POSICAO                                             */
/*=======================================================================*/
int funcaoHash3(char* palavra, int tam)
{
	unsigned int ascii = 0;
	int i;

	for(i = 0; i < strlen(palavra); i++)
	{
		ascii = ascii + (palavra[i-1] * i + vetRand[i]);
	}

	return (ascii*ascii+5) % tam;
}

/*=======================================================================*/
/*CRIA HASH - FUNCAO DE CRIACAO DA HASH                                  */
/*IN: VOID   OUT: PONTEIRO PARA HASH                                     */
/*=======================================================================*/
Hash criaHash(int tam)
{
	int i;
	srand(time(NULL));
	Hash hash = (Hash) malloc(sizeof(struct hash));
	hash->tam = tam;
	hash->colisao = 0;
	hash->vetor = (Palavra*) malloc(sizeof(Palavra)*tam);
	for(i = 0; i < tam; i++)
	{
		hash->vetor[i] = NULL;
	}
	if(F != 2)
	{
		for(i = 0; i < 32; i++)
		{
			vetRand[i] = rand();
		}
	}
	return hash;
}

/*=======================================================================*/
/*DESTROI HASH - FUNCAO DE DESTRUICAO DA HASH                            */
/*IN: PONTEIRO PARA HASH   OUT: VOID                                     */
/*=======================================================================*/
void destroiHash(Hash hash)
{
	Palavra excluir;
	int i;
	for(i = 0; i < hash->tam; i++)
	{
		while(hash->vetor[i] != NULL)
		{
			excluir = hash->vetor[i];
			hash->vetor[i] = excluir->prox;
			destroiLista(excluir->ocorrencias);
			free(excluir);
		}
	}
	free(hash->vetor);
	free(hash);
	hash = NULL;
	return;
}

/*=======================================================================*/
/*INSERE HASH - FUNCAO RESPONSAVEL POR INSERIR PALAVRA                   */
/*IN: HASH E PALAVRA A INSERIR   OUT: PONTEIRO PARA PALAVRA              */
/*=======================================================================*/
Palavra insereHash(Hash hash, char* palavra)
{
	int posicao;
	if(F == 1)
		posicao = funcaoHash1(palavra, hash->tam);
	else if(F == 2)
		posicao = funcaoHash2(palavra, hash->tam);
	else if(F == 3) 
		posicao = funcaoHash3(palavra, hash->tam);

	Palavra inserir = (Palavra) malloc(sizeof(struct palavra));

	if(hash->vetor[posicao] != NULL)
		hash->colisao++;

	inserir->prox = hash->vetor[posicao];
	hash->vetor[posicao] = inserir;

	strcpy(inserir->plv, palavra);
	inserir->ocorrencias = criaLista();

	return inserir;
}

/*=======================================================================*/
/*BUSCA HASH - FUNCAO DE BUSCA DA HASH                                   */
/*IN: HASH E PALAVRA A BUSCAR   OUT: PONTEIRO PARA PALAVRA               */
/*=======================================================================*/
Palavra buscaHash(Hash hash, char* palavra)
{
	int posicao;
	if(F == 1)
		posicao = funcaoHash1(palavra, hash->tam);
	else if(F == 2)
		posicao = funcaoHash2(palavra, hash->tam);
	else 
		posicao = funcaoHash3(palavra, hash->tam);

	Palavra olhar = hash->vetor[posicao];

	while(olhar != NULL && strcmp(palavra, olhar->plv))
	{
		olhar = olhar->prox;
	}

	if(olhar == NULL)
	{
		return NULL;
	}

	return olhar;
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

void printaHash(Hash hash)
{
	int i;
	Palavra plv;
	for(i = 0; i < hash->tam; i++)
	{
		if(hash->vetor[i] != NULL)
		{
			plv = hash->vetor[i];
			while(plv != NULL)
			{
				printf("%s\n", plv->plv);
				plv = plv->prox;
			}
		}
	}
}

/*=======================================================================*/
/*RETORNA COLISAO - FUNCAO QUE RETORNA QUANT DE COLISAO                  */
/*IN: HASH   OUT: INT                                                    */
/*=======================================================================*/
int colisaoHash(Hash hash)
{
	return hash->colisao;
}