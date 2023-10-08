#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <windows.h>
#include "./biblioteca/tadFilaS.h"
#include "./biblioteca/tadFilaI.h"
#include "./biblioteca/utils.h"
#include "./biblioteca/tadBanco.h"
#include "./biblioteca/tadListaColuna.h"
#include "./biblioteca/tadListaTabela.h"
#include "./biblioteca/sql.h"


int main(void) {
	DescFilaString F;
	init(&F);
	char string[100];
	gets(string);
	printf("%s\n", string);
	criaFilaS(string, &F);
	exibeFila(F);
	
	return 0;
}
