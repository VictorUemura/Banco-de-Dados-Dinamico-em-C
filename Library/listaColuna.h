typedef struct ListaColuna {
	PColuna *coluna;
	struct ListaColuna *prox;
} ListaColuna;

void initListaC(ListaColuna **L) {
	*L = NULL;
}

void novaCaixaListaC(ListaColuna **L, PColuna **coluna) {
	*L = (ListaColuna *) malloc(sizeof(ListaColuna));
	(*L)->coluna = *coluna;
	(*L)->prox = NULL;
}

void insereListaC(ListaColuna **L, PColuna **coluna) {
	ListaColuna *N, *A;
	novaCaixaListaC(&N, &(*coluna));
	if(*L == NULL)
		*L = N;
	else {
		A = *L;
		while(A->prox != NULL)
			A = A->prox;
		A->prox = N;
	}
}

void limpaListaC(ListaColuna **L) {
	ListaColuna *A;
	while(*L != NULL) {
		A = *L;
		*L = (*L)->prox;
		free(A);
	}
}

void buscaListaC(ListaColuna **L, char string[], ListaColuna **E) {
	ListaColuna *A;
	A = *L;
	while(A != NULL && strcmp(A->coluna->campo, string) != 0)
		A = A->prox;
	if(A != NULL)
		*E = A;
	else
		*E = NULL;
}

void exibeListaC(ListaColuna *L) {
	ListaColuna *A;
	A = L;
	while(A != NULL) {
		printf("%s\n", A->coluna->campo);
		A = A->prox;
	}
}
