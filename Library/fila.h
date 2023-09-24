typedef struct FilaString{
	char texto[100];
	struct FilaString *prox;
	
} FilaString;

typedef struct DescFilaString{
	FilaString *inicio, *fim;
} DescFilaString;

void init(DescFilaString *D){ 
	D->inicio = D->fim = NULL;
}

char filaVazia(DescFilaString *D){
	return D->inicio == NULL;
}

void *criaCaixa(char texto[100], FilaString **C){
	*C = (FilaString*) malloc(sizeof(FilaString));
	strcpy((*C)->texto, texto);
	(*C)->prox = NULL;
} 

void enqueue(DescFilaString *D, char texto[]){
	FilaString *caixa, *aux;
	criaCaixa(texto, &caixa);
	if(D->inicio == NULL)
		D->inicio = D->fim = caixa;
	else{
		D->fim->prox = caixa;
		D->fim = caixa;
	}
}

void unqueue(DescFilaString *D, char string[]){
	FilaString *aux;
	if(!filaVazia(D)) {
		strcpy(string, D->inicio->texto);
		aux = D->inicio;
		D->inicio = aux->prox;
		if(D->inicio == NULL)
			D->fim = NULL;
		free(aux);
	}
	else
		string[0] = '\0';
}

void exibeFila(DescFilaString D) {
	while(D.inicio != NULL) {
		printf("%s\n", D.inicio->texto);
		D.inicio = D.inicio->prox;
	}
}

void topoFila(DescFilaString D, char string[]) {
	if(!filaVazia(&D))
		strcpy(string, D.inicio->texto);
	else
		strcpy(string, "");
}
