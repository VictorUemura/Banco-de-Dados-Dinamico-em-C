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
	ListaTabela *LT;
	DescFilaString F, Col, Tab, S;
	init(&F);
	init(&S);
	init(&Col);
	init(&Tab);
	enqueue(&F, "Tab1");
	enqueue(&F, ",");
	enqueue(&F, "Tab2");
	enqueue(&F, ",");
	enqueue(&F, "Tab3");
	enqueue(&F, ",");
	enqueue(&F, "Tab5");
	enqueue(&F, ";");
		
	// Teste criação de banco de dados
	initBancoDado(&B);
	novoBancoDado(&B, "Teste");
	printf("Nome do banco de dados: %s\n", B->nome);
	
	// Teste criação e inserção de tabela
	insereTabela(&B, "Tab1");
	printf("Nome da tabela: %s\n", B->tabela->nome);
	
	// Teste criação e inserção de coluna
	insereColuna(&B->tabela, "Col1", 'I', 'S');
	insereColuna(&B->tabela, "Col2", 'I', 'N');
	printf("Nome da coluna 1: %s\n", &B->tabela->coluna->campo);
	printf("Nome da coluna 2: %s\n", &B->tabela->coluna->prox->campo);
	
	// Teste inserção de coluna em uma tabela previamente selecionada
	insereColunaTabela(&B, "Col3", 'I', 'N', "Tab1");
	exibeNomeColuna(B->tabela);
	
	// Teste inserção de chave estrangeira em coluna
	insereTabela(&B, "Tab2");
	insereColunaTabela(&B, "Col1", 'I', 'N', "Tab2");
	insereChaveEstrangeira(&B, "Tab1", "Col1", "Tab2", "Col1");
	if(B->tabela->coluna->fk != NULL)
		printf("\nChave estrangeira inserida Tab2 -> Tab1: %s -> %s\n", B->tabela->prox->coluna->campo, B->tabela->coluna->fk->campo);
	if(B->tabela->prox->coluna->fk != NULL)
		printf("Chave estrangeira inserita Tab1 -> Tab2: %s -> %s\n", B->tabela->coluna->prox->prox->campo, B->tabela->prox->coluna->campo);
	
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
	insereDado(&B->tabela->coluna->prox, "23");
	insereDado(&B->tabela->coluna->prox->prox, "24");
	insereDado(&B->tabela->prox->coluna, "22");
	// Teste de busca de coluna
	buscaTabela(&B, "Tab1", &T);
	
	printf("\n\n");
	exibeBanco(B);
	
	// Teste função from
	insereTabela(&B, "Tab3");
	insereTabela(&B, "Tab4");
	insereTabela(&B, "Tab5");
	insereTabela(&B, "Tab6");
	printf("\n\nTeste from\n");
	comandoFrom(&B, &F, &LT);
	exibeListaT(LT);
	
	// Teste separação do select
	printf("\nSeparacao select:\n");
	/*
	enqueue(&S, "Tab1.Col1");
	enqueue(&S, ",");
	enqueue(&S, "Tab1.Col2");
	enqueue(&S, ",");
	enqueue(&S, "Tab2.Col1");
	*/
	enqueue(&S, "*");
	enqueue(&S, "FROM");
	comandoSelect(&S, &Col, &Tab);
	printf("Colunas:\n");
	exibeFila(Col);
	printf("Tabelas:\n");
	exibeFila(Tab);
	
	// Teste salva colunas para a condição do select
	criaListaColuna(&LT, &Col, &Tab);
	exibeListaT(LT);
	
	return 0;
}
