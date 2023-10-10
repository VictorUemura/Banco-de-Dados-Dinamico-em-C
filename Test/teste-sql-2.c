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
	// SELECT
	// O comando e enviado sem o select
	/*
	strcpy(string, "ordem_servico.id_os, ordem_servico.data_entrada, ordem_servico.id_veiculo, veiculo.modelo, veiculo.dono, os_servico.id_servico, servico.descricao FROM ordem_servico, veiculo, os_servico, servico WHERE ordem_servico.id_veiculo = veiculo.id_veiculo AND ordem_servico.id_os = os_servico.id_os AND os_servico.id_servico = servico.id_servico;");
	criaFilaS(string, &L);
	comandoSelect(&L, &C, &J);
	comandoFrom(&B, &L, &LT);
	criaListaColuna(&LT, &C, &J);
	topoFilaString(L, string);
	if(strcmp(";", string) != 0) {
		comandoWhere(&LT, &L, 1);
		topoFilaString(L, string);
		if(strcmp(string, ";") == 0)
				unqueue(&L, string);

		while(!filaVazia(&L)) {
			comandoWhere(&LT, &L, 0);
			topoFilaString(L, string);
			if(strcmp(string, ";") == 0)
				unqueue(&L, string);
		}
	} else {
		comandoWhereGeral(&LT);
		unqueue(&L, string);
	}
	*/
	// UPDATE
	
	strcpy(string, "veiculo SET marca = 'Vw - Volkswagen' WHERE marca = 'Volkswagen';");
	criaFilaS(string, &L);
	comandoFrom(&B, &L, &LT);
	// 1 se for update
	criaListaColuna(&LT, NULL, NULL, 1);
	exibeBanco(B);
	comandoUpdate(&LT, &L);
	exibeBanco(B);
	
	return 0;
}

