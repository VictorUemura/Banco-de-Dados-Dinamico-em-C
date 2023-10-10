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
	char string[10000];

	LOAD_SQL(&B, "scripthospital.txt");
	gets(string);
	while(strcmp(string, "end") != 0){
		SQL(&B, string);
		gets(string);
	}
	return 0;
}

