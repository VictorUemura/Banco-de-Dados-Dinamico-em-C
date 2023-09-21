typedef struct PilhaDado{
	Dado dado;
	struct PilhaDado *prox; 
} PilhaDado;

void init(PilhaDado **P){
	(*P) = NULL;
}

char pilhaVazia(PilhaDado *P){
	return (*P)->prox == NULL;
}

void push(PilhaDado **P, Dado D){
	PilhaDado *caixa = (PilhaDado*)malloc(sizeof(PilhaDado));
	caixa->dado = D;
	if((*P) == NULL)
		(*P) = caixa;
	else{
		caixa->prox = (*P);
		(*P) = caixa;
	}
}

void pop(PilhaDado **P, Dado D){
	PilhaDado *aux;
	if(!pilhaVazia((*P))){
		D = (*P)->dado;
		aux = (*P);
		(*P) = (*P)->prox;
	}
	free(aux);
}

