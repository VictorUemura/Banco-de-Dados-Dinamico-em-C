
// Implementa��o -> String din�mica
typedef struct Caractere {
	struct Caractere *prox;
	struct Caractere *ant;
	char *C;
} Caractere;

typedef struct String {
	int tam;
	Caractere *inicio;
	Caractere *fim;
} String;

void inicString(String **string) {
	(*string)->inicio = NULL;
	(*string)->fim = NULL;
	(*string)->tam = 0;
}

Caractere *novoCaractere(char carac) {
	Caractere c = (Caractere *) malloc(sizeof(Caractere));
	c->ant = c->prox = NULL;
	c->C = carac;
}

// Adiciona caractere no final da string
void addCaractere(String **string, char carac) {
	Caractere *c = novoCaractere(carac);
	if(*string->inicio == NULL) {
		*string->inicio = *string->fim = c;
	}
	else {
		c->ant = *string->fim;
		*string->fim->prox = c;
		*string->fim = c;
	}
	*string->tam++;
}


