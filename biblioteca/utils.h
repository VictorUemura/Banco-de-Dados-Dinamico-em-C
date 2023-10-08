// Busca string dentro da outra e retorna inicio
void verificaString(char *string, char *string2, int *inicio) {
	int j = 0;
	for(int i = 0; i < strlen(string) && j < strlen(string2); i++) {
		if(string[i] == string2[0]) {
				j = 0;
				*inicio = i;
			while(i < strlen(string) && j < strlen(string2) && string[i] == string2[j]) {
				j++;
				i++;
			}
		}
	}
	if(j != strlen(string2))
		*inicio = -1;
}

// Cria fila a partir de string
void criaFilaS(char string[200], DescFilaString *L) {
	char palavra[200], aspas;
	int j, i;
	j = 0;
	i = 0;
	while(i < strlen(string)) {
		j = 0;
		if(string[i] == '\'' || string[i] == '"') {
			aspas = string[i++];
			palavra[j++] = aspas;
			palavra[j] = '\0';
			enqueue(&(*L), palavra);
			j = 0;
			while(i < strlen(string) && string[i] != aspas) {
				palavra[j] = string[i];
				j++; i++;	
			}
			palavra[j] = '\0';
			enqueue(&(*L), palavra);
			j = 0;
			
		}
		if(string[i] != ' ' && string[i] != '(' && string[i] != ')' && string[i] != ',' && string[i] != ';' && string[i] != '\n' && string[i] != '\'' && string[i] != '"') {
				while(i < strlen(string) && string[i] != '(' && string[i] != ')' && string[i] != ',' && string[i] != ';' && string[i] != ' ' && string[i] != '"') {
					palavra[j] = string[i];
					j++; i++;
				}
				palavra[j] = '\0';
				enqueue(&(*L), palavra);
			}
		else if(string[i] == '(' || string[i] == ')' || string[i] == ',' || string[i] == ';' || string[i] == '\'' || string[i] == '"') {
			palavra[j] = string[i];
			j++; i++;
			palavra[j] = '\0';
			enqueue(&(*L), palavra);
		}
		else
			i++;
	}
}

// Cria fila a partir de outra fila
void criaFila(DescFilaString *L, DescFilaString *C) {
	char linha[200], palavra[100];
	int j, i;
	
	while(!filaVazia(L)) {
		unqueue(&(*L), linha);
		criaFilaS(linha, &(*C));
	};
}

// Busca ponto dentro da string
void buscaPonto(char texto[], int *pos) {
	int i = 0;
	while(i < strlen(texto) && texto[i] != '.')
		i++;
	if(i < strlen(texto))
		*pos = i;
	else
		*pos = -1;
		
}

// Envia strings antes e depois do ponto
void separaPonto(char texto[], char antes[], char depois[]) {
	int i, j;
	for(i = 0; i < strlen(texto) && texto[i] != '.'; i++)
		antes[i] = texto[i];
		antes[i++] = '\0';
	for(j = 0; j < strlen(texto); j++)
		depois[j] = texto[i++];
	depois[j] = '\0';
}

// Faz a leitura de um arquivo texto e retorna por parametro uma lista de strings
void leituraArquivo(DescFilaString *C, char *nomeArq){
	DescFilaString L;
	FILE *ptrArq = fopen(nomeArq, "r+");
	char string[100];
	
	if(ptrArq != NULL) {
		init(&L);
		init(&(*C));
		
		fscanf(ptrArq, "%[^\n]\n", &string);
		while(!feof(ptrArq)){
			enqueue(&L, string);
			fscanf(ptrArq, "%[^\n]\n", &string);
		}
		
		enqueue(&L, string);
		criaFila(&L, C);
		fclose(ptrArq);
	} 
}

// Converte numero para inteiro
void converteNumeroI(char *dado, int *I) {
	int valor = 1, i;
	*I = 0;
	for(i = strlen(dado) - 1; i >= 0; i--) {
		*I += (dado[i] - 48) * valor;
		valor *= 10;
	}
}

// Converte numero para double
void converteNumeroN(char *dado, double *N) {
	int i;
	double valor = 0.01;
	*N = 0;
	for(i = strlen(dado) - 1; i >= 0; i--) {
		if(i == (strlen(dado) - 1) - 2)
			i--;
		*N += (dado[i] - 48) * valor;
		valor *= 10;
	}
}
