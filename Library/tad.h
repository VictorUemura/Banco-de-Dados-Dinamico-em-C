
typedef struct Dado {
	union {
		int valorI;
		float valorN;
		char valorD[11];
		char valorC;
		char valorT[21];
	};
	struct Dado *prox;
} Dado;

typedef struct PColuna {
	char tipo;
	char *campo;
	char pk;
	Dado *pDados;
	struct PColuna *fk;	
	struct PColuna *prox;
} PColuna;

typedef struct Tabela {
	char *nome;
	PColuna *coluna;
	struct Tabela *ant;
	struct Tabela *prox;
} Tabela;

typedef struct BancoDado {
	char *nome;
	Tabela *tabela;
} BancoDado;

void inicListaDado(Dado **dado){
	(*dado)->prox = NULL;
}

Dado *novoDadoInt(int num){
	Dado *caixa = (Dado*) malloc(sizeof(Dado));;
	caixa->valorI = num;
	caixa->prox = NULL;
	
	return caixa;
}

Dado *novoDadoFloat(float num){
	Dado *caixa = (Dado*) malloc(sizeof(Dado));
	caixa->valorN = num;
	caixa->prox = NULL;
	
	return caixa;
}

Dado *novoDadoIdade(char *id){
	Dado *caixa = (Dado*) malloc(sizeof(Dado));
	strcpy(caixa->valorD, id);
	caixa->prox = NULL;
	
	return caixa;
}

Dado *novoDadoCaractere(char *c){
	Dado *caixa = (Dado*) malloc(sizeof(Dado));
	caixa->valorC = c;
	caixa->prox = NULL;
	
	return caixa;
}

Dado *novoDadoString(char *string){
	Dado *caixa = (Dado*) malloc(sizeof(Dado));
	strcpy(caixa->valorT, string);
	caixa->prox = NULL;
	
	return caixa;
} 

// Insere dados no final da lista de dados
void insereDado(Dado **lista, Dado *novoDado) {
	Dado *inicioAux = *lista;
	if(*lista == NULL)
		*lista = novoDado;
	else {
		while(inicioAux->prox != NULL)
			inicioAux = inicioAux->prox;
		inicioAux->prox = novoDado;
	}
}

void inicListaPColuna(PColuna **coluna){
	*coluna = NULL;
}

PColuna *novoPColuna(char tipo, char *campo, char pk){
	PColuna *caixa = (PColuna*) malloc(sizeof(PColuna));
	caixa->tipo = tipo;
	strcpy(caixa->campo, campo);
	caixa->pk = pk;
	caixa->pDados = NULL;
	caixa->fk = caixa->prox = NULL;
	
	return caixa;
}

void inicTabela(Tabela **tabela){
	(*tabela)->coluna = NULL;
	(*tabela)->ant = (*tabela)->prox = NULL;
}

Tabela *novoTabela(char *nome){
	Tabela *caixa = (Tabela*) malloc(sizeof(Tabela));
	strcpy(caixa->nome, nome);
	caixa->prox = caixa->ant = NULL;
	
	return caixa;
}

void inicBancoDados(BancoDado **banco){
	(*banco)->tabela = NULL;
}

BancoDado *novoBancoDado(char *nome){
	BancoDado *caixa = (BancoDado*) malloc(sizeof(BancoDado));
	caixa->tabela = NULL;
	strcpy(caixa->nome, nome);
	return caixa;
}

void insereColuna(PColuna **listaColuna, char tipo, char *campo, char pk) {
	PColuna *coluna = novaPColuna(tipo, campo, pk), *colunaAux = *listaColuna;
	if(*listaColuna == NULL) {
		*listaColuna = coluna;
	}
	else {
		while(colunaAux->prox != NULL)
			colunaAux = colunaAux->prox;
		colunaAux->prox = coluna;
	}
}

// Insere tabela no final
void insereTabela(Tabela **listaTabela, char *nome) {
	Tabela *novaTabela = novoTabela(nome), *tabelaAux = *listaTabela;
	if(*listaTabela == NULL) {
		*listaTabela = novaTabela;
	} else {
		while(listaTabela->prox != NULL) {
			listaTabela = listaTabela->prox;
		}
		novaTabela->ant = tabelaAux;
		tabelaAux->prox = novaTabela;
	}
}

void insereChaveEstrangeira(Tabela **listaTabela, PColuna *colunaEstrangeira, char *nome) {
	PColuna *colunaAux = (*listaTabela)->coluna; 
	PColuna *novaColuna = novoPColuna(colunaEstrangeira->tipo, colunaEstrangeira->campo, colunaEstrangeira->pk);
	novaColuna->fk = colunaEstrangeira;
	if((*listaTabela)->coluna == NULL)
		(*listaTabela)->coluna = novaColuna;
	else {
		while(colunaAux->prox != NULL) {
			colunaAux = colunaAux->prox;
		}
		colunaAux->prox = novaColuna;
	}
}
