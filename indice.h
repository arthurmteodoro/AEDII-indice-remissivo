/*=======================================================================*/
/*                Trabalho de AED II - Indice remissivo                  */
/* Nome: Arthur Alexsander Martins Teodoro                               */
/* MAtrícula: 0022427         Data: 13/09/2016                           */
/*=======================================================================*/
#ifndef _INDICEREMISSIVO_
#define _INDICEREMISSIVO_

extern void inserirPalavras(Hash hash, const char* arqPalvrasChave);
extern char* buscaPalavra(int *inicio, int *fim, char* frase);
extern void criaIndice(Hash hash, const char* palavrasChave, const char* texto);
extern void filtragemPalavras(char* palavra);
extern int contaPalavrasChave(const char* arqPalvrasChave);

#endif