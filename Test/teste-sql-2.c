#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../Library/tad.h"
#include "../Library/fila.h"
#include "../Library/leituraArquivo.h"
#include "../Library/sql.h"

void aaa(DescFilaString *C){
	int i;
	DescFilaString COL,VAR;
	
	init(&COL);
	init(&VAR);
	char aux[100], aux2[100];
	while(!filaVazia(C)){
		unqueue(C, aux);
		if(strcmp("INSERT", aux) == 0){
			unqueue(C, aux);
			while(strcmp("INTO", aux) == 0 || aux[0] == ',' || aux[0] == ')' || aux[0] == '(')
				unqueue(C, aux);
			printf("%s\n", aux);
			unqueue(C, aux);
			while(aux[0] != ')' && !filaVazia(C)){
				unqueue(C, aux);
				while(strcmp("INTO", aux) == 0 || aux[0] == ',' || aux[0] == '(' && !filaVazia(C))
					unqueue(C, aux);
				if(aux[0] != ')')
					enqueue(&COL, aux);
				
			}
			unqueue(C, aux);
			if(strcmp("VALUES", aux) == 0){
				unqueue(C, aux);
				while(aux[0] != ')' && !filaVazia(C)){
					unqueue(C, aux);
					while(aux[0] == ',' || aux[0] == '(' && !filaVazia(C))
						unqueue(C, aux);
					if(aux[0] != ')'){
						if(aux[0] == '\''){
							for(int i = 0, j = 0; i < strlen(aux); i++){
								if(aux[i] != '\''){
									aux2[j] = aux[i];
									j++;
								}
							}
							strcpy(aux, aux2);	
						}
						enqueue(&VAR, aux);
					}
				}
			}
		}
		if(strcmp("DELETE", aux) == 0)
			printf("funciona");
		if(strcmp("UPDATE", aux) == 0)
			printf("funciona");	
	}
	while(!filaVazia(&COL) && !filaVazia(&VAR)){
		unqueue(&COL, aux);
		printf("%s\n", aux);
		unqueue(&VAR, aux2);
		printf("%s\n", aux2);
	}
}

void comandoInsert(DescFilaString *C, BancoDado **B){
	char aux[100], aux2[100];
	DescFilaString V, T;
	init(&V);
	init(&T);
	unqueue(C, aux);
	while(aux[0] != ')' && !filaVazia(C)){
		if(aux[0] != ',' && aux[0] != '(' && aux[0] != ')'){
			enqueue(&T, aux);	
		}
		unqueue(C, aux);
	}
	
	unqueue(C, aux);
	unqueue(C, aux);
	while(aux[0] != ')' && !filaVazia(C)){
		if(aux[0] != ',' && aux[0] != '(' && aux[0] != ')'){
			enqueue(&V, aux);	
		}
		unqueue(C, aux);
	}

	while(!filaVazia(T) && !filaVazia(V)){
		unqueue(&T, aux);
		unqueue(&V, aux2);
	}

}

int main(void) {
	BancoDado *B;
	DescFilaString D, C;
	init(&D);
	init(&C);
	enqueue(&D, " (id_venda, id_venda2, id_venda3)\nVALUES (100, 'ola', 5.3, n);");
	criaFila(&D, &C);
	initBancoDado(&B);
	
	novoBancoDado(&B, "bd_seila");
	insereTabela(&B, "venda");
	
	insereColunaTabela(&B, "id_venda", 'I', 'N', "venda");
	insereColunaTabela(&B, "id_venda2", 'T', 'N', "venda");
	insereColunaTabela(&B, "id_venda3", 'N', 'N', "venda");
	
	
	comandoInsert(&C, &B);	
	return 0;
}

