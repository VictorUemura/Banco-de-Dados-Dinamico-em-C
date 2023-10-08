#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <windows.h>
#include "./library/tadFilaS.h"
#include "./library/tadFilaI.h"
#include "./library/utils.h"
#include "./library/tadBanco.h"
#include "./library/tadListaColuna.h"
#include "./library/tadListaTabela.h"
#include "./library/sql.h"


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
