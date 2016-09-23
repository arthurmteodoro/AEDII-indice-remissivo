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
	srand(time(NULL));
	int i;
	Hash hash = (Hash) malloc(sizeof(struct hash));
	hash->tam = tam;
	hash->colisao = 0;
	hash->vetor = (Palavra*) malloc(sizeof(Palavra)*tam);
	for(i = 0; i < tam; i++)
	{
		hash->vetor[i] = NULL;
	}
	for(i = 0; i < 32; i++)
	{
		vetRand[i] = rand();
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

		free(hash->vetor);
		free(hash);
		hash = NULL;
	}
	return;
}

/*=======================================================================*/
/*INSERE HASH - FUNCAO RESPONSAVEL POR INSERIR PALAVRA                   */
/*IN: HASH E PALAVRA A INSERIR   OUT: PONTEIRO PARA PALAVRA              */
/*=======================================================================*/
Palavra insereHash(Hash hash, char* palavra)
{
	unsigned int posicao;
	if(F == 1)
		posicao = funcaoHash1(palavra, hash->tam);
	else if(F == 2)
		posicao = funcaoHash2(palavra, hash->tam);
	else if(F == 3) 
		posicao = funcaoHash3(palavra, hash->tam);

	int posicoesVerificadas = 0;

	if(buscaHash(hash, palavra) != NULL)
		return NULL;

	while((hash->vetor[posicao] != NULL) && (posicoesVerificadas != hash->tam))
	{
		if(C == 1)
			posicao = (posicao+1)%hash->tam;
		else if(C == 2)
			posicao = (((posicao*posicao)+455)/45)%hash->tam;
		else if(C == 3)
		{
			posicao = (posicao+2)%hash->tam;
		}
		hash->colisao++;
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
	int posicao;
	if(F == 1)
		posicao = funcaoHash1(palavra, hash->tam);
	else if(F == 2)
		posicao = funcaoHash2(palavra, hash->tam);
	else 
		posicao = funcaoHash3(palavra, hash->tam);

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
	return hash->colisao;
}