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
	while(strcmp(string, "a") != 0){
		criaFilaS(string, &L);
		gets(string);
	}

	while(!filaVazia(&L)) {
		unqueue(&L, string);
		if(strcmp(string, "INSERT") == 0)
			INSERT_SQL(&B, &L);
	}
	exibeBanco(B);
	/*	
	strcpy(string, "ordem_servico.id_os, ordem_servico.data_entrada, ordem_servico.id_veiculo, veiculo.modelo, veiculo.dono, os_servico.id_servico, servico.descricao FROM ordem_servico, veiculo, os_servico, servico WHERE ordem_servico.id_veiculo = veiculo.id_veiculo AND ordem_servico.id_os = os_servico.id_os AND os_servico.id_servico = servico.id_servico;");
	criaFilaS(string, &L);
	SELECT_SQL(&B, &L);

	strcpy(string, "veiculo SET marca = 'Vw - Volkswagen' WHERE marca = 'Volkswagen';");
	criaFilaS(string, &L);
	UPDATE_SQL(&B, &L);

	strcpy(string, "FROM veiculo WHERE id_veiculo > 1;");
	criaFilaS(string, &L);
	DELETE_SQL(&B, &L);
	*/
	return 0;
}

