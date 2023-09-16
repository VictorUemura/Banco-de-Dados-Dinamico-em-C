typedef struct FilaString{
	char texto[30];
	struct FilaString *prox;
	
} FilaString;

typedef struct DescFilaString{
	FilaString *inicio, *fim;
} DescFilaString;

void init(DescFilaString **D){ 
	(*D)->inicio = (*D)->fim = NULL;
}

char filaVazia(DescFilaString *D){
	return D->inicio == NULL;
}

pilha *criaCaixa(char texto[30]){
	pilha *caixa = (FilaString*)malloc(sizeof(FilaString));
	strcpy(caixa->texto, texto);
	caixa->prox = NULL;
	
	return caixa;
} 

void enqueue(DescFilaString **D, char texto[30]){
	FilaString *caixa, *aux;
	caixa = criaCaixa(texto);
	if((*D) == NULL)
		(*D).inicio = caixa;
	else{
		(*D)->fim->prox = caixa;
		(*D)->fim = caixa;
	}
	
}

void unqueue(FilaString **f, char *string){
	FilaString *aux;
	strcpy(string, (*D)->inicio->texto);
	aux = (*D)->inicio;
	(*D)->inicio = (*D)->inicio->prox;
	
	
	free(aux);
}
