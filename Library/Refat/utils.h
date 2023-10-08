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
		if(string[i] != ' ' && string[i] != '(' && string[i] != ')' && string[i] != ',' && string[i] != ';' && string[i] != '\n' && string[i] != '\'') {
				while(i < strlen(string) && string[i] != '(' && string[i] != ')' && string[i] != ',' && string[i] != ';' && string[i] != ' ') {
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
		criaFilaS(linha, &(*L));
	}
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

