union Tipo {
	int valorI;
	double valorN;
	char valorD[11];
	char valorC;
	char valorT[21];
};

typedef struct Dado {
	union Tipo tipo;
	struct Dado *prox;
} Dado;

typedef struct PColuna {
	char tipo, campo[100], pk;
	Dado *pDados, *pAtual;
	struct PColuna *fk, *prox;
} PColuna;

typedef struct Tabela {
	char nome[100];
	PColuna *coluna;
	struct Tabela *ant, *prox;
} Tabela;

typedef struct BancoDado {
	char nome[100];
	Tabela *tabela;
} BancoDado;

void initBancoDado(BancoDado **B) {
	*B = NULL;
}

void novoBancoDado(BancoDado **B, char *nome) {
	*B = (BancoDado *) malloc(sizeof(BancoDado));
	(*B)->tabela = NULL;
	strcpy((*B)->nome, nome);
}

void novaTabela(Tabela **T, char *nome) {
	*T = (Tabela *) malloc(sizeof(Tabela));
	(*T)->ant = (*T)->prox = NULL;
	(*T)->coluna = NULL;
	strcpy((*T)->nome, nome);
}

void insereTabela(BancoDado **B, char *nome) {
	Tabela *T, *aux;
	novaTabela(&T, nome);
	
	if((*B)->tabela == NULL) {
		(*B)->tabela = T;
	}
	else {
		aux = (*B)->tabela;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = T;
		T->ant = aux;
	}
}

void novaColuna(PColuna **C, char *campo, char tipo, char pk) {
	*C = (PColuna *) malloc(sizeof(PColuna));
	(*C)->pk = pk;
	(*C)->tipo = tipo;
	(*C)->fk = (*C)->prox = NULL;
	(*C)->pDados = (*C)->pAtual = NULL;
	strcpy((*C)->campo, campo);
}

void insereColuna(Tabela **T, char *campo, char tipo, char pk) {
	PColuna *C, *aux;
	novaColuna(&C, campo, tipo, pk);
	
	if((*T)->coluna == NULL)
		(*T)->coluna = C;
	else {
		aux = (*T)->coluna;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = C;
	}
}

// Insere coluna em uma tabela com seu nome indicado por parâmetro
void insereColunaTabela(BancoDado **B, char *campo, char tipo, char pk, char *nomeTabela) {
	Tabela *aux = (*B)->tabela;
	while(aux != NULL && strcmp(aux->nome, nomeTabela) != 0)
		aux = aux->prox;
	if(aux != NULL)
		insereColuna(&aux, campo, tipo, pk);
}

void insereChaveEstrangeira(BancoDado **B, char *nomeTabela, char *nomeColuna, char *nomeTabelaFK, char *nomeColunaFK) {
	Tabela *T = (*B)->tabela;
	PColuna *C1, *C2;
	// Busca tabela estrangeira
	while(T != NULL && strcmp(T->nome, nomeTabelaFK) != 0)
		T = T->prox;
	if(T != NULL) {
		// Busca coluna estrangeira
		C1 = T->coluna;
		while(C1 != NULL && strcmp(C1->campo, nomeColunaFK) != 0)
			C1 = C1->prox;
		if(C1 != NULL) {
			T = (*B)->tabela;
			// Busca tabela para inserção
			while(T != NULL && strcmp(T->nome, nomeTabela) != 0)
				T = T->prox;
			if(T != NULL) {
				C2 = T->coluna;
				// Busca coluna para inserção
				while(C2 != NULL && strcmp(C2->campo, nomeColuna))
					C2 = C2->prox;
				if(C2 != NULL)
					C2->fk = C1;
			}
		}
	}
}

void novoDado(Dado **D) {
	(*D) = (Dado *) malloc(sizeof(Dado));
}

void novoDadoI(Dado **D, int I) {
	novoDado(&(*D));
	(*D)->tipo.valorI = I;
}

void novoDadoT(Dado **D, char *T) {
	novoDado(&(*D));
	strcpy((*D)->tipo.valorD, T);
}

void novoDadoN(Dado **D, float N) {
	novoDado(&(*D));
	(*D)->tipo.valorN = N;
}

void novoDadoC(Dado **D, char C) {
	novoDado(&(*D));
	(*D)->tipo.valorC = C;
}

void converteNumeroI(char *dado, int *I) {
	int valor = 1, i;
	*I = 0;
	for(i = strlen(dado) - 1; i >= 0; i--) {
		*I += (dado[i] - 48) * valor;
		valor *= 10;
	}
}

void converteNumeroN(char *dado, double *N) {
	int i;
	double valor = 0.01;
	*N = 0;
	for(i = strlen(dado) - 1; i >= 0; i--) {
		if(i == (strlen(dado) - 1) - 2)
			i--;
		*N += (dado[i] - 48) * valor;
		valor *= 10;
	}
}

void insereDado(PColuna **C, char *dado) {
	Dado *aux, *D;
	int I;
	double N;
	
	if((*C)->tipo == 'N') {
		converteNumeroN(dado, &N);
		novoDadoN(&D, N);
	}
	else if((*C)->tipo == 'I') {
		converteNumeroI(dado, &I);
		novoDadoI(&D, I);
	}
	else if((*C)->tipo == 'C')
		novoDadoC(&D, dado[0]);
	else if((*C)->tipo == 'D' || (*C)->tipo == 'T')
		novoDadoT(&D, dado);
		
	if((*C)->pDados == NULL)
		(*C)->pDados = D;
	else {
		aux = (*C)->pDados;
		while(aux->prox != NULL)
			aux = aux->prox;
		aux->prox = D;
	}
}

void buscaColuna(Tabela *T, char *nomeC, PColuna **coluna) {
	PColuna *C;
	C = T->coluna;
	while(C != NULL && strcmp(nomeC, C->campo) != 0){
		C = C->prox;
	}
	*coluna = C;
}

void buscaTabela(BancoDado **B, char *nomeT, Tabela **T) {
	Tabela *A;
	A = (*B)->tabela;
	while(A != NULL && strcmp(nomeT, A->nome) != 0)	
		A = A->prox;
	if(A != NULL)
		*T = A;
	else
		*T = NULL;
}

void exibeBanco(BancoDado *B) {
	PColuna *C;
	Tabela *T = B->tabela;
	Dado *D;
	int i;
	while(T != NULL) {
		printf("Nome tab. %s\n", T->nome);
		C = T->coluna;
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
		T = T->prox;
	}
}
