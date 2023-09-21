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

FilaString *criaCaixa(char texto[100]){
	FilaString *caixa = (FilaString*)malloc(sizeof(FilaString));
	strcpy(caixa->texto, texto);
	caixa->prox = NULL;
	
	return caixa;
} 

void enqueue(DescFilaString *D, char texto[100]){
	FilaString *caixa, *aux;
	caixa = criaCaixa(texto);
	if(D->inicio == NULL)
		D->inicio = D->fim = caixa;
	else{
		D->fim->prox = caixa;
		D->fim = caixa;
	}
	
}

void unqueue(DescFilaString *D, char string[100]){
	FilaString *aux;
	strcpy(string, D->inicio->texto);
	aux = D->inicio;
	D->inicio = D->inicio->prox;
	
	
	free(aux);
}
