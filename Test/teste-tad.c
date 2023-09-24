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
	int I;
	double N;
	BancoDado *B;
	Tabela *T;
	PColuna *C;
	
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
	
	// Teste conversão numérica
	converteNumeroI("22", &I);
	printf("Numero Convertido: %d\n", I);
	converteNumeroI("134", &I);
	printf("Numero Convertido: %d\n", I);
	converteNumeroI("149", &I);
	printf("Numero Convertido: %d\n", I);
	
	converteNumeroN("22,00", &N);
	printf("Numero Convertido (Double): %.2lf\n", N);
	converteNumeroN("22,05", &N);
	printf("Numero Convertido (Double): %.2lf\n", N);
	converteNumeroN("22,50", &N);
	printf("Numero Convertido (Double): %.2lf\n", N);
	converteNumeroN("344300,55", &N);
	printf("Numero Convertido (Double): %.2lf\n", N);
	
	// Teste inserção de dado
	insereDado(&B->tabela->coluna, "22");
	printf("1 -> dado inserido na primeira coluna: %d\n", B->tabela->coluna->pDados->tipo.valorI);
	
	// Teste de busca de coluna
	buscaTabela(B, "Tab. 1", &T);
	buscaColuna(&T, "Col. 3", &C);
	printf("Coluna %s encontrada.\n", C->campo);
	
	return 0;
}
