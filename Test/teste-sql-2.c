#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <windows.h>
#include "../biblioteca/tadFilaS.h"
#include "../biblioteca/tadFilaI.h"
#include "../biblioteca/utils.h"
#include "../biblioteca/tadBanco.h"
#include "../biblioteca/tadListaColuna.h"
#include "../biblioteca/tadListaTabela.h"
#include "../biblioteca/sql.h"

int main(void) {
	BancoDado *B;
	DescFilaString L;
	char string[10000];

	init(&L);
	LOAD_SQL(&B, "scriptdboficina.txt");
	gets(string);
	while(strcmp(string, "end") != 0){
		SQL(&B, string);
		gets(string);
	}

	return 0;
}

