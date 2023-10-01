typedef struct ListaTabela {
	struct ListaTabela *prox;
	Tabela *tabela;
	ListaColuna *listaColuna;
	DescFilaI descFilaI;
} ListaTabela;

void initListaT(ListaTabela **L) {
	*L = NULL;
}

void novaCaixaListaT(ListaTabela **L, Tabela **tabela) {
	*L = (ListaTabela *) malloc(sizeof(ListaTabela));
	(*L)->tabela = *tabela;
	(*L)->prox = NULL;
	initI(&((*L)->descFilaI));
	initListaC(&((*L)->listaColuna));
}

void insereListaT(ListaTabela **L, Tabela **tabela) {
	ListaTabela *N, *A;
	novaCaixaListaT(&N, &(*tabela));
	if(*L == NULL)
		*L = N;
	else {
		A = *L;
		while(A->prox != NULL)
			A = A->prox;
		A->prox = N;
	}
}

void limpaListaT(ListaTabela **L) {
	ListaTabela *A;
	while(*L != NULL) {
		A = *L;
		*L = (*L)->prox;
		free(A);
	}
}

void buscaListaT(ListaTabela **L, char string[], ListaTabela **E) {
	ListaTabela *A;
	A = *L;
	while(A != NULL && strcmp(A->tabela->nome, string) != 0)
		A = A->prox;
	if(A != NULL)
		*E = A;
	else
		*E = NULL;
}

void exibeListaT(ListaTabela *L) {
	ListaColuna *A;
	while(L != NULL) {
		printf("%s\n", L->tabela->nome);
		A = L->listaColuna;
		while(A != NULL) {
			printf("Col.: %s\n", A->coluna->campo);
			A = A->prox;
		}
		L = L->prox;
	}
}
