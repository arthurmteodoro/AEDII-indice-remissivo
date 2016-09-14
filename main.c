/*=======================================================================*/
/*                Trabalho de AED II - Indice remissivo                  */
/* Nome: Arthur Alexsander Martins Teodoro                               */
/* MAtrícula: 0022427         Data: 13/09/2016                           */
/*=======================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openHash.h"

int main(void)
{

	Hash h = criaHash();

	insereHash(h,"roma");
	insereHash(h,"amor");

	destroiHash(h);

	return 0;
}