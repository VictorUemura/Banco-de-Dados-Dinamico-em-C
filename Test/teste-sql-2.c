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
	ListaTabela *LT;
	DescFilaString L, C, J;
	char string[10000];
	int i = 0;
	
	initListaT(&LT);
	initBancoDado(&B);
	init(&C);
	init(&J);
	init(&L);
	leituraArquivo(&J, "scriptdboficina.txt");
	carregaScript(&B, &J);
	gets(string);
	while(strcmp(string, "a") != 0){
		enqueue(&L, string);
		gets(string);
	}
	criaFila(&L, &C);
	while(!filaVazia(&C)){
		topoFilaString(C, string);
		if(strcmp(string, "INSERT") == 0)
			comandoInsert(&B, &C);
	}
	
	strcpy(string, "* FROM ordem_servico, veiculo, os_peca, peca WHERE ordem_servico.id_veiculo = veiculo.id_veiculo AND ordem_servico.id_os = os_peca.id_os AND os_peca.id_peca = peca.id_peca;");
	criaFilaS(string, &L);
	comandoSelect(&L, &C, &J);
	comandoFrom(&B, &L, &LT);
	criaListaColuna(&LT, &C, &J);
	comandoWhere(&LT, &L, 1);
	
	while(!filaVazia(&L)) {
		unqueue(&L, string);
		comandoWhere(&LT, &L, 0);
		printf("fefe");
	}
	
	exibeListaTDados(&LT);
	return 0;
}

