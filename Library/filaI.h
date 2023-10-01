typedef struct Fila {
	int valor;
	struct Fila *prox;
} Fila;

typedef struct DescFilaI {
	Fila *inicio, *fim;
} DescFilaI;

void initI(DescFilaI *F) {
	F->inicio = F->fim = NULL;
}

void novaCaixaI(Fila **C, int valor) {
	*C = (Fila *) malloc(sizeof(Fila));
	(*C)->valor = valor;
	(*C)->prox = NULL;
}

char filaVaziaI(DescFilaI F) {
	return F.inicio == NULL;
}

void enqueueI(DescFilaI *F, int V) {
	Fila *C;
	novaCaixaI(&C, V);
	if(F->inicio == NULL)
		F->inicio = F->fim = C;
	else {
		F->fim->prox = C;
		F->fim = C;
	}
}

void unqueueI(DescFilaI *F, int *V) {
	Fila *C;
	if(!filaVaziaI(*F)) {
		C = F->inicio;
		F->inicio = C->prox;
		if(F->inicio == NULL)
			F->fim = NULL;
		*V = C->valor;
		free(C);
	}
	else
		*V = -1;
}

void exibeFilaI(DescFilaI F) {
	while(F.inicio != NULL) {
		printf("%d\n", F.inicio->valor);
		F.inicio = F.inicio->prox;
	}
}
