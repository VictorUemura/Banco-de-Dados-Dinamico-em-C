typedef struct ListaTabela {
	struct ListaTabela *prox;
	Tabela *tabela;
	ListaColuna *listaColuna;
	DescFilaI descFilaI;
} ListaTabela;

void initListaT(ListaTabela **L) {
	*L = NULL;
}

// Pode ser usada so uma vez porque desfaz a fila de linhas 
void exibeListaTDados(ListaTabela **L) {
	int linha, i = 1;
	Dado *D;
	ListaTabela *T = (*L);
	ListaColuna *A;
	printf("Dados filtrados:\n");
	while(T != NULL) {
		printf("%s\n", T->tabela->nome);
		while(!filaVaziaI(T->descFilaI)) {
			unqueueI(&T->descFilaI, &linha);
			A = T->listaColuna;
			printf("%d\t", i++);
			while(A != NULL) {
				buscaDado(A->coluna, linha, &D);
				if(A->coluna->tipo == 'I')
					printf("%d\t", D->tipo.valorI);
				else if(A->coluna->tipo == 'T' || A->coluna->tipo == 'D')
					printf("%s\t", D->tipo.valorT);
				else if(A->coluna->tipo == 'N')
					printf("%.2lf\t", D->tipo.valorN);
				else if(A->coluna->tipo == 'C')
					printf("%c\t", D->tipo.valorC);
				A = A->prox;
			}
			printf("\n");
		}
		i = 1;
		T = T->prox;
	}
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
	ListaTabela *T = L;
	while(T != NULL) {
		printf("%s\n", T->tabela->nome);
		A = T->listaColuna;
		while(A != NULL) {
			printf("Col.: %s\n", A->coluna->campo);
			A = A->prox;
		}
		printf("Linhas:\n");
		exibeFilaI(T->descFilaI);
		T = T->prox;
	}
}
