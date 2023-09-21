typedef struct ListaPilhaDado{
	PilhaDado *pDado;
	struct ListaPilhaColuna *prox, *ant;
}ListaPilhaDado;

typedef struct DescLista{
	ListaPilhaDado *inicio, *fim;
};

void inicializaLista(DescLista **D){
	return (*D)->inicio == NULL;
}

char listaVazia(ListaPilhaDado *D){
	return D->inicio == NULL;
}

void criaCaixa(pDado dado){
	ListaPilhaDado *caixa;
	caixa = (ListaPilhaDado*)malloc(sizeof(ListaPilhaDado));
	caixa->pDado = dado;
	caixa->prox = caixa->ant = NULL;
	
	return caixa;
}

void insereLista(DescLista **D, pDado dado){
	ListaPilhaDado *caixa;
	caixa = criaCaixa(dado);
	
	if((*D) == NULL)
		(*D) = caixa;
	else{
		(*D)->fim->prox = caixa;
		caixa->ant = (*D)->fim;
		(*D)->fim = caixa;
	}
}

void removeLista(DescLista **D, pDado &dado){
	ListaPilhaDado *aux;
	if(!listaVazia((*D)){
		dado = (*D)->inicio->pDado;
		aux = (*D)->inicio;
		(*D)->inicio = (*D)->inicio->prox;
		
		free(aux);
	}
}
