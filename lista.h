/*=======================================================================*/
/*                Trabalho de AED II - Indice remissivo                  */
/* Nome: Arthur Alexsander Martins Teodoro                               */
/* MAtrícula: 0022427         Data: 13/09/2016                           */
/*=======================================================================*/
#ifndef _LISTAHASH_
#define _LISTAHASH_

#include "listadup.h"

typedef struct palavra *Palavra;
typedef struct lista *Hash;


extern Hash criaHash(int tam);
extern void destroiHash(Hash hash);
extern Palavra insereHash(Hash lista, char* palavra);
extern Palavra buscaHash(Hash lista, char* palavra);
extern void insereOcorrencia(Hash lista, char* palavra, int linha);
extern int tamanhoHash(Hash hash);
extern char* retornaPalavra(Palavra plv);
extern Lista retornaLista(Palavra plv);
extern int colisaoHash(Hash hash);

#endif