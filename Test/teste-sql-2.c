#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "../Library/fila.h"
#include "../Library/tad.h"
#include "../Library/leituraArquivo.h"
#include "../Library/filaI.h"
#include "../Library/listaColuna.h"
#include "../Library/listaTabela.h"
#include "../Library/sql.h"

<<<<<<< Updated upstream
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

=======
>>>>>>> Stashed changes
int main(void) {
	BancoDado *B;
	DescFilaString D;
	char string[100];
<<<<<<< Updated upstream
	
	leituraArquivo(&D, "texto.txt");
	carregaScript(&B, &D);
	printf("Nome do banco: %s\n", B->nome);
	exibeTabela(B);
	
=======

	leituraArquivo(&D, "texto.txt");
	carregaScript(&B, &D);
	printf("Nome do banco: %s\n", B->nome);
	exibeBanco(B);

>>>>>>> Stashed changes
	return 0;
}
