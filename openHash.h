/*=======================================================================*/
/*                Trabalho de AED II - Indice remissivo                  */
/* Nome: Arthur Alexsander Martins Teodoro                               */
/* MAtrícula: 0022427         Data: 13/09/2016                           */
/*=======================================================================*/
#ifndef _OPENHASH_
#define _OPENHASH_

#define N 124

typedef struct palavra *Palavra;
typedef struct hash *Hash;

extern Hash criaHash(int tam);
extern void destroiHash(Hash hash);
extern int funcaoHash(char* palavra, int tam);
extern Palavra insereHash(Hash hash, char* palavra);
extern Palavra buscaHash(Hash hash, char* palavra);
extern void insereOcorrencia(Hash hash, char* palavra, int linha);
extern void printaHash(Hash hash, FILE* arquivo);

#endif