union Tipo {
	int valorI;
	float valorN;
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

