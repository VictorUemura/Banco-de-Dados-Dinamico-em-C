// Busca uma string dentro de outra
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

void criaFila(DescFilaString *L, DescFilaString *C) {
	char linha[100], palavra[100];
	int j, i;
	
	while(!filaVazia(L)) {
		unqueue(L, linha);
		i = 0;
		while(i < strlen(linha)) {
			j = 0;
			if(linha[i] != ' ' && linha[i] != '(' && linha[i] != ')' && linha[i] != ',' && linha[i] != ';' && linha[i] != '\n' && linha[i] != '\'') {
				while(i < strlen(linha) && linha[i] != '(' && linha[i] != ')' && linha[i] != ',' && linha[i] != ';' && linha[i] != ' ') {
					palavra[j] = linha[i];
					j++;
					i++;
				}
				palavra[j] = '\0';
				enqueue(C, palavra);
			}
			else if(linha[i] == '(' || linha[i] == ')' || linha[i] == ',' || linha[i] == ';' || linha[i] == '\'' || linha[i]) {
				palavra[j] = linha[i];
				j++;
				palavra[j] = '\0';
				enqueue(C, palavra);
				i++;
			}
			else
				i++;
		}
	}
}

void leituraArquivo(DescFilaString *C, char *nomeArq){
	DescFilaString L;
	FILE *ptrArq = fopen(nomeArq, "r+");
	char string[100];
	
	if(ptrArq != NULL) {
		init(&L);
		init(C);
		
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
