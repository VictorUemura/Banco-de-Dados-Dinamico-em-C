
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

Dado *novoDadoInt(int num){
	Dado *caixa = (Dado*) malloc(sizeof(Dado));;
	caixa->valorI = num;
	caixa->prox = NULL;
	
	return Dado;
}

void inicListaDado(Dado **dado){
	(*dado)->prox = NULL;
}

Dado *novoDadoFloat(float num){
	Dado *caixa = (Dado*) malloc(sizeof(Dado));
	caixa->valorN = num;
	caixa->prox = NULL;
	
	return caixa;
}

Dado *novoDadoIdade(char *id){
	Dado *caixa = (Dado*) malloc(sizeof(Dado));
	strcpy(Dado->valorD, id);
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
