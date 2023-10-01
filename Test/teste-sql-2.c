#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../Library/tad.h"
#include "../Library/fila.h"
#include "../Library/leituraArquivo.h"
#include "../Library/sql.h"

void exibeTabela(BancoDado *B) {
    PColuna *C;
    Dado *D;
    int i;
    while(B->tabela != NULL) {
        printf("Nome tab. %s\n", B->tabela->nome);
        C = B->tabela->coluna;
        while(C != NULL) {
            printf("Col.: %s - Tipo = %c - PK: %c - FK: ", C->campo, C->tipo, C->pk);
            if(C->fk != NULL)
                printf("%s\n", C->fk->campo);
            else
                printf("NULL\n");
            D = C->pDados;
            i = 0;
            while(D != NULL) {
                if(C->tipo == 'I')
                printf("%d %d\n", ++i, D->tipo.valorI);
                else if(C->tipo == 'T' || C->tipo == 'D')
                printf("%d %s\n", ++i, D->tipo.valorT);
                else if(C->tipo == 'N')
                printf("%d %.2lf\n", ++i, D->tipo.valorN);
                else if(C->tipo == 'I')
                printf("%d %c\n", ++i, D->tipo.valorC);
                D = D->prox;
            }
            C = C->prox;
        }
        B->tabela =B->tabela->prox;
    }
}

int main(void) {
	BancoDado *B;
	DescFilaString L, C, J;
	char string[10000];
	int i = 0;
	initBancoDado(&B);
	init(&C);
	init(&J);
	init(&L);
		
	leituraArquivo(&J, "texto.txt");
	carregaScript(&B, &J);
	gets(string);
	while(strcmp(string, "a") != 0){
		enqueue(&L, string);
		gets(string);
	}
	criaFila(&L, &C);
	while(!filaVazia(&C)){
		topoFila(C, string);
		if(strcmp(string, "INSERT") == 0)
			comandoInsert(&B, &C);
		//printf("aaa");
	}
	
	
	exibeTabela(B);
	printf("\n\n\n\n\n");
	
	return 0;
}

