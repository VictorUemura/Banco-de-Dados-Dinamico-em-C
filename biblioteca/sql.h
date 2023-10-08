void carregaScript(BancoDado **B, DescFilaString *F) {
	char string[100], stringColuna[100], stringTabela[100];
	DescFilaString fila;
	Tabela *T;
	PColuna *C, *C2;
	init(&fila);
	
	while(!filaVazia(F)) {
		unqueue(&(*F), string);
		if(strcmp("CREATE", string) == 0) {
			unqueue(&(*F), string);
			
			if(strcmp("DATABASE", string) == 0) {
				initBancoDado(&(*B));
				unqueue(&(*F), string);
				novoBancoDado(&(*B), string);
				unqueue(&(*F), string);
			}
			else if(strcmp("TABLE", string) == 0) {
				unqueue(&(*F), string);
				insereTabela(&(*B), string);
				strcpy(stringTabela, string);
				
				do {
					unqueue(&(*F), string);
					if(strcmp(string, "(") == 0)
						enqueue(&fila, string);
					
					else if(strcmp(string, ")") == 0)
						unqueue(&fila, string);
					
					else if(strcmp(string, "INTEGER") == 0)
						insereColunaTabela(&(*B), stringColuna, 'I', 'N', stringTabela);
					
					else if(strcmp(string, "CHARACTER") == 0) {
							unqueue(&(*F), string);
							unqueue(&(*F), string);
							if(strcmp(string, "20") == 0) {
								insereColunaTabela(&(*B), stringColuna, 'T', 'N', stringTabela);
							} else {
								insereColunaTabela(&(*B), stringColuna, 'C', 'N', stringTabela);
							}
							unqueue(&(*F), string);
					}
					
					else if(strcmp(string, "DATE") == 0)
						insereColunaTabela(&(*B), stringColuna, 'D', 'N', stringTabela);
					
					else if(strcmp(string, "NUMERIC") == 0) {
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						insereColunaTabela(&(*B), stringColuna, 'N', 'N', stringTabela);
					}
					
					else if(strcmp(string, "CONSTRAINT") == 0) {
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						if(strcmp(string, "PRIMARY") == 0) {
							unqueue(&(*F), string);
							if(strcmp(string, "KEY") == 0) {
								unqueue(&(*F), string);
								unqueue(&(*F), string);
								buscaTabela(&(*B), stringTabela, &T);
								buscaColuna(T, string, &C);
								C->pk = 'S';
								unqueue(&(*F), string);
							}
						}
					}
					
					else if(strcmp(string, ",") != 0)
						strcpy(stringColuna, string);
				
				} while(filaVazia(F) == 0 && filaVazia(&fila) == 0);
			}
		}
		else if(strcmp(string, "ALTER") == 0) {
			unqueue(&(*F), string);
			if(strcmp(string, "TABLE") == 0) {
				unqueue(&(*F), string);
				buscaTabela(&(*B), string, &T);
				unqueue(&(*F), string);
				if(strcmp(string, "ADD") == 0) {
					unqueue(&(*F), string);
					if(strcmp(string, "CONSTRAINT") == 0) {
						unqueue(&(*F), string);
						unqueue(&(*F), string);
						if(strcmp(string, "FOREIGN") == 0) {
							unqueue(&(*F), string);
								if(strcmp(string, "KEY") == 0) {
								unqueue(&(*F), string);
								unqueue(&(*F), string);
								buscaColuna(T, string, &C);
								unqueue(&(*F), string);
								unqueue(&(*F), string);
								if(strcmp(string, "REFERENCES") == 0) {
									unqueue(&(*F), string);
									buscaTabela(&(*B), string, &T);
									unqueue(&(*F), string);
									unqueue(&(*F), string);
									buscaColuna(T, string, &C2);
									C->fk = C2;
								}
							}
						}
					}
				}
			}
		}
			
	}
}

void comandoSelect(DescFilaString *F, DescFilaString *C, DescFilaString *T) {
	char string[100], stringAntes[100], stringDepois[100];
	int verifica = -1;
	init(&(*C));
	init(&(*T));
	do {
		unqueue(&(*F), string);
		buscaPonto(string, &verifica);
		if(verifica > -1) {
			verifica = -1;
			separaPonto(string, stringAntes, stringDepois);
			enqueue(&(*T), stringAntes);
			enqueue(&(*C), stringDepois);
		} 
		else
			enqueue(&(*C), string);
		topoFilaString(*F, string);
		if(strcmp(string, ",") == 0)
			unqueue(&(*F), string);
	} while(strcmp(string, "FROM") != 0);
}

void comandoFrom(BancoDado **B, DescFilaString *F, ListaTabela **L) {
	char string[100];
	Tabela *T;
	initListaT(&(*L));
	do {
		unqueue(&(*F), string);
		buscaTabela(&(*B), string, &T);
		if(T != NULL)
			insereListaT(&(*L), &T);
		topoFilaString(*F, string);
		if(strcmp(string, ",") == 0)
			unqueue(&(*F), string);
	} while(strcmp(string, ";") != 0 && strcmp(string, "WHERE") != 0);
}

void criaListaColuna(ListaTabela **L, DescFilaString *C, DescFilaString *T) {
	char string[100], string2[100];
	PColuna *col;
	ListaTabela *caixa;
	topoFilaString(*C, string);
	if(strcmp(string, "*") == 0) {
		unqueue(&(*C), string);
		caixa = (*L);
		while(caixa != NULL) {
			col = caixa->tabela->coluna;
			while(col != NULL) {
				insereListaC(&(caixa->listaColuna), &col);
				col = col->prox;
			}
			caixa = caixa->prox;
		}
	}
	else if(filaVazia(&(*T))) {
		while(!filaVazia(C)) {	
			unqueue(&(*C), string);
			buscaColuna((*L)->tabela, string, &col);
			insereListaC(&((*L)->listaColuna), &col);
		}
	}
	else {
		while(!filaVazia(C)) {
			unqueue(&(*C), string);
			unqueue(&(*T), string2);
			buscaListaT(&(*L), string2, &caixa);
			buscaColuna(caixa->tabela, string, &col);
			insereListaC(&(caixa->listaColuna), &col);
		}
	}
}

// Fun��o que retorna uma fila com linhas em que se encontram aquela condi��o aplicada
// Obs.: A condi��o � enviada como uma string dividida por DescFilaString
// A contagem das linha se inicia por 0
void comandoWhere(ListaTabela **L, DescFilaString *F) {
	int linha = 0, valorI, verifica, valorProxI;
	double valorN, valorProxN;
	char string[100], condicao[100], valorC, valorT[100], stringAntes[100], stringDepois[100], tipo, valorProxT[100], valorProxC;
	ListaColuna *col1, *col2;
	ListaTabela *tab1, *tab2;
	Dado *D;
	unqueue(&(*F), string);
	buscaPonto(string, &verifica);
	if(verifica > -1) {
		verifica = -1;
		separaPonto(string, stringAntes, stringDepois);
		buscaListaT(&(*L), stringAntes, &tab1);
		buscaListaC(&(tab1->listaColuna), stringDepois, &col1);
	}
	// Significa que s� existe uma tabela dentro da lista
	else
		buscaListaC(&((*L)->listaColuna), string, &col1);
	unqueue(&(*F), string);
	strcpy(condicao, string);
	
	unqueue(&(*F), string);
	buscaPonto(string, &verifica);
	// � n�mero ou nome de coluna
	if(verifica > -1) {
		verifica = -1;
		// Coluna tipo = 0
		if((string[0] >= 65 && string[0] <= 90) || (string[0] >= 97 && string[0] <= 122)) {
			separaPonto(string, stringAntes, stringDepois);
			buscaListaT(&(*L), stringAntes, &tab2);
			buscaListaC(&(tab1->listaColuna), stringDepois, &col2);
			tipo = '0';
		}
		// Numero tipo = 1
		else {
			converteNumeroN(string, &valorN);
			tipo = '1';
		}
	}
	else if(col1->coluna->tipo == 'C') {
		// Caracter tipo = 2
		tipo = '2';
		unqueue(&(*F), string);
		valorC = string[0];
		unqueue(&(*F), string);
	}
	else if(col1->coluna->tipo == 'D' || col1->coluna->tipo == 'T') {
		// Texto tipo = 3
		tipo = '3';
		unqueue(&(*F), string);
		strcpy(valorT, string);
		unqueue(&(*F), string);
	}
	else {
		// Inteiro tipo = 4
		tipo = '4';
		converteNumeroI(string, &valorI);
	}
	if(strcmp(condicao, "BETWEEN") == 0) {
		unqueue(&(*F), string);
		unqueue(&(*F), string);
		buscaPonto(string, &verifica);
		if(verifica > -1) {
			verifica = -1;
			converteNumeroN(string, &valorN);
		}
		if(col1->coluna->tipo == 'C') {
			unqueue(&(*F), string);
			valorProxC = string[0];
			unqueue(&(*F), string);
		}
		else if(col1->coluna->tipo == 'D' || col1->coluna->tipo == 'T') {
			unqueue(&(*F), string);
			strcpy(valorProxT, string);
			unqueue(&(*F), string);
		}
		else
			converteNumeroI(string, &valorProxI);
	}
	D = col1->coluna->pDados;
	// Falta criar condi��es
	while(D != NULL) {
		if(strcmp(condicao, "=") == 0) {
			
		}
	}
	
}

void comandoInsert(BancoDado **B, DescFilaString *I){
	char string[100],stringTabela[100], stringColuna[100];
	DescFilaString COLUNA, VALORES;
	Tabela *T;
	PColuna *C;
	Dado *D;
	
	init(&COLUNA);
	init(&VALORES);
	
	unqueue(&(*I), string);
	while(!filaVazia(I) && strcmp(string, ";") != 0){
		if(strcmp(string,"INSERT")==0){
			unqueue(&(*I), string);
			if(strcmp(string, "INTO")==0){
				unqueue(&(*I), string);
				strcpy(stringTabela, string);
				unqueue(&(*I), string);
				do{
					if(strcmp(string, "(") == 0)
						unqueue(&(*I), string);
					else if(strcmp(string, ")") == 0)
						unqueue(&(*I), string);
					else if(strcmp(string, ",") == 0)
						unqueue(&(*I), string);
					else{
						enqueue(&COLUNA, string);
						unqueue(&(*I), string);
					}
				}while(stricmp(string, "VALUES") != 0 && !filaVazia(I));
			}
		}
		else if(stricmp(string, "VALUES") == 0){
			unqueue(&(*I), string);
			do{
				if(strcmp(string, "(") == 0)
					unqueue(&(*I), string);
				else if(strcmp(string, ")") == 0)
					unqueue(&(*I), string);
				else if(strcmp(string, ",") == 0)
					unqueue(&(*I), string);
				else if(strcmp(string, "'") == 0)
					unqueue(&(*I), string);
				else{
					if(strcmp(string, ";") != 0){
						enqueue(&VALORES, string);
						unqueue(&(*I), string);
					}
				}					
			
			}while(!filaVazia(I) && strcmp(string, ";") != 0);
		}
		else
			unqueue(&(*I), string);
	}
	
	
	buscaTabela(&(*B), stringTabela, &T);
	while(!filaVazia(&COLUNA) || !filaVazia(&VALORES)){
		unqueue(&COLUNA, stringColuna);
		buscaColuna(T, stringColuna, &C);
		unqueue(&VALORES, string);
		insereDado(&C, string);
		D = C->pDados;
		while(D->prox != NULL)
			D = D->prox;
		C->pAtual =  D;
		if(C->fk != NULL){
			if(C->fk->tipo == 'I'){
				if(C->pAtual->tipo.valorI == C->fk->pAtual->tipo.valorI)
					printf("Tem");
			}
			if(C->fk->tipo == 'C'){
				if(C->pAtual->tipo.valorC == C->fk->pAtual->tipo.valorC)
					printf("Tem");
			}
			if(C->fk->tipo == 'T'){
				if(strcmp(C->pAtual->tipo.valorT, C->fk->pAtual->tipo.valorT) == 0)
					printf("Tem");
			}
			if(C->fk->tipo == 'N'){
				if(C->pAtual->tipo.valorN == C->fk->pAtual->tipo.valorN)
					printf("Tem");
			}
			if(C->fk->tipo == 'D')
				if(strcmp(C->fk->pAtual->tipo.valorD, C->pAtual->tipo.valorD) == 0)
					printf("Tem");
		}
	}
}
