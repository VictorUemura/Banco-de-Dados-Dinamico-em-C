#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../Library/tad.h"
#include "../Library/fila.h"
#include "../Library/leituraArquivo.h"
#include "../Library/sql.h"

void exibeTabela(BancoDado *B) {
	PColuna *C;
	while(B->tabela != NULL) {
		printf("Nome tab. %s\n", B->tabela->nome);
		C = B->tabela->coluna;
		while(C != NULL) {
			printf("Col.: %s - PK: %c - FK: ", C->campo, C->pk);
			if(C->fk != NULL)
				printf("%s\n", C->fk->campo);
			else
				printf("NULL\n");
			C = C->prox;
		}
		B->tabela =B->tabela->prox;
	}
}

int main(void) {
	BancoDado *B;
	DescFilaString D;
	char string[100];
	
	leituraArquivo(&D, "texto.txt");
	carregaScript(&B, &D);
	printf("Nome do banco: %s\n", B->nome);
	exibeTabela(B);
	
	return 0;
}
