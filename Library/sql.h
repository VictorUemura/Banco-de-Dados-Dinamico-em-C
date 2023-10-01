/*
#include "../Library/tad.h"
#include "../Library/fila.h"
#include "../Library/leituraArquivo.h"
*/

void carregaScript(BancoDado **B, DescFilaString *F) {
	char string[100], stringColuna[100], stringTabela[100];
	DescFilaString fila;
	Tabela *T;
	PColuna *C, *C2;
	init(&fila);
	
	while(!filaVazia(F)) {
		unqueue(&(*F), string);
		if(strcmp("CREATE", string) == 0) {
			unqueue(&(*F), string);
			
			if(strcmp("DATABASE", string) == 0) {
				initBancoDado(&(*B));
				unqueue(&(*F), string);
				novoBancoDado(&(*B), string);
				unqueue(&(*F), string);
			}
			else if(strcmp("TABLE", string) == 0) {
				unqueue(&(*F), string);
				insereTabela(&(*B), string);
				strcpy(stringTabela, string);
				
				do {
					unqueue(&(*F), string);
					if(strcmp(string, "(") == 0)
						enqueue(&fila, string);
					
					else if(strcmp(string, ")") == 0)
						unqueue(&fila, string);
					
					else if(strcmp(string, "INTEGER") == 0)
						insereColunaTabela(&(*B), stringColuna, 'I', 'N', stringTabela);
					
					else if(strcmp(string, "CHARACTER") == 0) {
							unqueue(&(*F), string);
							unqueue(&(*F), string);
							if(strcmp(string, "20") == 0) {
								insereColunaTabela(&(*B), stringColuna, 'T', 'N', stringTabela);
							} else {
								insereColunaTabela(&(*B), stringColuna, 'C', 'N', stringTabela);
							}
							unqueue(&(*F), string);
					}
					
					else if(strcmp(string, "DATE") == 0)
						insereColunaTabela(&(*B), stringColuna, 'D', 'N', stringTabela);
					
					else if(strcmp(string, "NUMERIC") == 0) {
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						insereColunaTabela(&(*B), stringColuna, 'N', 'N', stringTabela);
					}
					
					else if(strcmp(string, "CONSTRAINT") == 0) {
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						if(strcmp(string, "PRIMARY") == 0) {
							unqueue(&(*F), string);
							if(strcmp(string, "KEY") == 0) {
								unqueue(&(*F), string);
								unqueue(&(*F), string);
								buscaTabela(&(*B), stringTabela, &T);
								buscaColuna(&T, string, &C);
								C->pk = 'S';
								unqueue(&(*F), string);
							}
						}
					}
					
					else if(strcmp(string, ",") != 0)
						strcpy(stringColuna, string);
				
				} while(filaVazia(F) == 0 && filaVazia(&fila) == 0);
			}
		}
		else if(strcmp(string, "ALTER") == 0) {
			unqueue(&(*F), string);
			if(strcmp(string, "TABLE") == 0) {
				unqueue(&(*F), string);
				buscaTabela(&(*B), string, &T);
				unqueue(&(*F), string);
				if(strcmp(string, "ADD") == 0) {
					unqueue(&(*F), string);
					if(strcmp(string, "CONSTRAINT") == 0) {
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						if(strcmp(string, "FOREIGN") == 0) {
							unqueue(&(*F), string);
								if(strcmp(string, "KEY") == 0) {
								unqueue(&(*F), string);
								unqueue(&(*F), string);
								buscaColuna(&T, string, &C);
								unqueue(&(*F), string);
								unqueue(&(*F), string);
								if(strcmp(string, "REFERENCES") == 0) {
									unqueue(&(*F), string);
									buscaTabela(&(*B), string, &T);
									unqueue(&(*F), string);
									unqueue(&(*F), string);
									buscaColuna(&T, string, &C2);
									C->fk = C2;
								}
							}
						}
					}
				}
			}
		}
			
	}
}

void comandoSelect(DescFilaString *F) {
	
}

void comandoInsert(BancoDado **B, DescFilaString *I){
	char string[100],stringTabela[100], stringColuna[100];
	DescFilaString COLUNA, VALORES;
	Tabela *T;
	PColuna *C;
	Dado *D;
	
	init(&COLUNA);
	init(&VALORES);
	
	unqueue(&(*I), string);
	while(!filaVazia(I) && strcmp(string, ";") != 0){
		if(strcmp(string,"INSERT")==0){
			unqueue(&(*I), string);
			if(strcmp(string, "INTO")==0){
				unqueue(&(*I), string);
				strcpy(stringTabela, string);
				unqueue(&(*I), string);
				do{
					if(strcmp(string, "(") == 0)
						unqueue(&(*I), string);
					else if(strcmp(string, ")") == 0)
						unqueue(&(*I), string);
					else if(strcmp(string, ",") == 0)
						unqueue(&(*I), string);
					else{
						enqueue(&COLUNA, string);
						unqueue(&(*I), string);
					}
				}while(strcmp(string, "VALUES") != 0 && !filaVazia(I));
			}
		}
		else if(strcmp(string, "VALUES") == 0){
			unqueue(&(*I), string);
			do{
				if(strcmp(string, "(") == 0)
					unqueue(&(*I), string);
				else if(strcmp(string, ")") == 0)
					unqueue(&(*I), string);
				else if(strcmp(string, ",") == 0)
					unqueue(&(*I), string);
				else if(strcmp(string, "'") == 0)
					unqueue(&(*I), string);
				else{
					if(strcmp(string, ";") != 0){
						enqueue(&VALORES, string);
						unqueue(&(*I), string);
					}
				}					
			
			}while(!filaVazia(I) && strcmp(string, ";") != 0);
		}
		else
			unqueue(&(I), string);
	}
	
	
	buscaTabela(&(*B), stringTabela, &T);
	while(!filaVazia(&COLUNA) || !filaVazia(&VALORES)){
		unqueue(&COLUNA, stringColuna);
		buscaColuna(&T, stringColuna, &C);
		unqueue(&VALORES, string);
		insereDado(&C, string);
		D = C->pDados;
		while(D->prox != NULL)
			D = D->prox;
		C->pAtual =  D;
		if(C->fk != NULL){
			if(C->fk->tipo == 'I'){
				if(C->pAtual->tipo.valorI == C->fk->pAtual->tipo.valorI)
					printf("Tem");
			}
			if(C->fk->tipo == 'C'){
				if(C->pAtual->tipo.valorC == C->fk->pAtual->tipo.valorC)
					printf("Tem");
			}
			if(C->fk->tipo == 'T'){
				if(strcmp(C->pAtual->tipo.valorT, C->fk->pAtual->tipo.valorT) == 0)
					printf("Tem");
			}
			if(C->fk->tipo == 'N'){
				if(C->pAtual->tipo.valorN == C->fk->pAtual->tipo.valorN)
					printf("Tem");
			}
			if(C->fk->tipo == 'D')
				if(strcmp(C->fk->pAtual->tipo.valorD, C->pAtual->tipo.valorD) == 0)
					printf("Tem");
		}
	}
}
