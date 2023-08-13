
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
