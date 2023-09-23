#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../Library/tad.h"

void exibeNomeColuna(Tabela *T) {
	PColuna *aux = T->coluna;
	int i = 1;
	printf("\nTabela: %s\n", T->nome);
	while(aux != NULL) {
		printf("Col. %d: %s\n", i++, aux->campo);
		aux = aux->prox;
	}
}

int main(void) {
	BancoDado *B;
	
	// Teste criação de banco de dados
	initBancoDado(&B);
	novoBancoDado(&B, "Teste");
	printf("Nome do banco de dados: %s\n", B->nome);
	
	// Teste criação e inserção de tabela
	insereTabela(&B, "Tab. 1");
	printf("Nome da tabela: %s\n", B->tabela->nome);
	
	// Teste criação e inserção de coluna
	insereColuna(&B->tabela, "Col. 1", 'I', 'S');
	insereColuna(&B->tabela, "Col. 2", 'I', 'N');
	printf("Nome da coluna 1: %s\n", &B->tabela->coluna->campo);
	printf("Nome da coluna 2: %s\n", &B->tabela->coluna->prox->campo);
	
	// Teste inserção de coluna em uma tabela previamente selecionada
	insereColunaTabela(&B, "Col. 3", 'I', 'N', "Tab. 1");
	exibeNomeColuna(B->tabela);
	
	// Teste inserção de chave estrangeira em coluna
	insereTabela(&B, "Tab. 2");
	insereColunaTabela(&B, "Col. 1", 'I', 'N', "Tab. 2");
	insereChaveEstrangeira(&B, "Tab. 1", "Col. 1", "Tab. 2", "Col. 1");
	insereChaveEstrangeira(&B, "Tab. 2", "Col. 1", "Tab. 1", "Col. 3");
	if(B->tabela->coluna->fk != NULL)
		printf("\nChave estrangeira inserida Tab. 2 -> Tab. 1: %s -> %s\n", B->tabela->prox->coluna->campo, B->tabela->coluna->fk->campo);
	if(B->tabela->prox->coluna->fk != NULL)
		printf("Chave estrangeira inserita Tab. 1 -> Tab. 2: %s -> %s\n", B->tabela->coluna->prox->prox->campo, B->tabela->prox->coluna->campo);
	
	return 0;
}
