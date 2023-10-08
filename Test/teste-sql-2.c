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
	DescFilaString L, C, J;
	char string[10000];
	int i = 0;
	initBancoDado(&B);
	init(&C);
	init(&J);
	init(&L);
		
	leituraArquivo(&J, "scriptdboficina.txt");
	carregaScript(&B, &J);
	exibeBanco(B);
	gets(string);
	while(strcmp(string, "a") != 0){
		enqueue(&L, string);
		gets(string);
	}
	criaFila(&L, &C);
	exibeFila(C);
	while(!filaVazia(&C)){
		topoFilaString(C, string);
		if(strcmp(string, "INSERT") == 0)
			comandoInsert(&B, &C);
	}
	exibeBanco(B);
	
	printf("\n\n\n\n\n");
	
	return 0;
}

